#include "Layout.h"
#include <random>
#include <QGLWidget>

Layout::Layout() : width(12), depth(6), height(3)
{
	std::mt19937 mtengine;
	std::uniform_real_distribution<double> distribution(0.0,1.0);

	for (int i = 0; i < 6; ++i) {
		while (true) {
			int type = i;

			float x = width * distribution(mtengine) - width * 0.5;
			float y = depth * distribution(mtengine) - depth * 0.5;
			float z = 0;
			float t = 3.14159265359 * distribution(mtengine);
			/*if (type == 2) {
				float rnd = distribution(mtengine);
				if (rnd >= 0.75) {
					x = width * 0.5;
					t = 3.14159265359 * 0.5f;
				} else if (rnd >= 0.5) {
					x = -width * 0.5;
					t = -3.14159265359 * 0.5f;
				} else if (rnd >= 0.25) {
					y = -depth * 0.5;
					t = 0.0f;
				} else {
					y = depth * 0.5;
					t = 3.14159265359;
				}
				z = 1.2 + (height - 1.2) * distribution(mtengine);
			}*/
			Furniture furniture(type, x, y, z, t);

			bool valid = true;

			// inside check
			{
				if (!within(furniture.footprint())) {
					valid = false;
				}
			}

			// collision check
			if (valid) {
				for (int fid = 0; fid < furnitures.size(); ++fid) {
					Polygon2D output;
					Polygon2D footprint1 = furnitures[fid].footprint();
					Polygon2D footprint2 = furniture.footprint();
					boost::geometry::intersection(footprint1, footprint2, output);
					if (output.size() > 0) {
						valid = false;
						break;
					}

					if (footprint1.contains(footprint2) || footprint2.contains(footprint1)) {
						valid = false;
						break;
					}
				}
			}

			if (valid) {
				addFurniture(furniture);
				break;
			}
		}		
	}
}

void Layout::addFurniture(Furniture furniture)
{
	furnitures.push_back(furniture);
}

Layout Layout::proposeChange(float sigmaX, float sigmaY, float sigmaTheta)
{
	std::mt19937 mtengine;
	std::normal_distribution<double> distributionX(0.0, sigmaX);
	std::normal_distribution<double> distributionY(0.0, sigmaY);
	std::normal_distribution<double> distributionTheta(0.0, sigmaTheta);

	Layout proposedLayout(width, depth, height);

	for (int i = 0; i < furnitures.size(); ++i) {
		float x = furnitures[i].x + distributionX(mtengine);
		float y = furnitures[i].y + distributionY(mtengine);
		float z = 0;
		float theta = furnitures[i].theta + distributionTheta(mtengine);
		proposedLayout.addFurniture(Furniture(0, x, y, z, theta));
	}

	return proposedLayout;
}

/**
 * レイアウトに基づいてfeatureベクトルを生成する。
 */
cv::Mat Layout::feature()
{
	int nDiscretization = 20;
	cv::Mat vec(furnitures.size() * nDiscretization * 3, 1, CV_8U, cv::Scalar(0));

	for (int i = 0; i < furnitures.size(); ++i) {
		int nx = furnitures[i].x / width * nDiscretization;
		int ny = furnitures[i].y / depth * nDiscretization;
		int nt = furnitures[i].theta / 3.141592653592653 * nDiscretization;
		vec.at<unsigned char>(i * nDiscretization * 3 + nx, 0) = 1;
		vec.at<unsigned char>(i * nDiscretization * 3 + nDiscretization + ny, 0) = 1;
		vec.at<unsigned char>(i * nDiscretization * 3 + nDiscretization * 2 + nt, 0) = 1;
	}

	return vec;
}

void Layout::draw(VBORenderManager& rendManager)
{
	rendManager.removeStaticGeometry(QString("layout"));
	rendManager.removeStaticGeometry(QString("furniture"));

	// floor
	std::vector<Vertex> verts;
	verts.push_back(Vertex(-width*0.5, -depth*0.5, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f));	
	verts.push_back(Vertex(width*0.5, -depth*0.5, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, width, 0.0f, 0.0f));	
	verts.push_back(Vertex(width*0.5, depth*0.5, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, width, depth, 0.0f));	
	verts.push_back(Vertex(-width*0.5, depth*0.5, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, depth, 0.0f));	
	rendManager.addStaticGeometry("layout", verts, "../data/textures/floor.jpg", GL_QUADS, 2);// texture && lighting

	// bottom back wall
	verts.clear();
	verts.push_back(Vertex(-width*0.5, depth*0.5, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f));	
	verts.push_back(Vertex(width*0.5, depth*0.5, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, width, 0.0f, 0.0f));	
	verts.push_back(Vertex(width*0.5, depth*0.5, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, width, 1.0f, 0.0f));	
	verts.push_back(Vertex(-width*0.5, depth*0.5, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f));	
	rendManager.addStaticGeometry("layout", verts, "../data/textures/wall2.jpg", GL_QUADS, 2);// texture && lighting

	// upper back wall
	verts.clear();
	verts.push_back(Vertex(-width*0.5, depth*0.5, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f));	
	verts.push_back(Vertex(width*0.5, depth*0.5, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, width, 0.0f, 0.0f));	
	verts.push_back(Vertex(width*0.5, depth*0.5, height, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, width, height-1.0f, 0.0f));	
	verts.push_back(Vertex(-width*0.5, depth*0.5, height, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, height-1.0f, 0.0f));	
	rendManager.addStaticGeometry("layout", verts, "../data/textures/wall1.jpg", GL_QUADS, 2);// texture && lighting

	// bottom right wall
	verts.clear();
	verts.push_back(Vertex(width*0.5, depth*0.5, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f));	
	verts.push_back(Vertex(width*0.5, -depth*0.5, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, width, 0.0f, 0.0f));	
	verts.push_back(Vertex(width*0.5, -depth*0.5, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, width, 1.0f, 0.0f));	
	verts.push_back(Vertex(width*0.5, depth*0.5, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f));	
	rendManager.addStaticGeometry("layout", verts, "../data/textures/wall2.jpg", GL_QUADS, 2);// texture && lighting

	// upper right wall
	verts.clear();
	verts.push_back(Vertex(width*0.5, depth*0.5, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f));	
	verts.push_back(Vertex(width*0.5, -depth*0.5, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, width, 0.0f, 0.0f));	
	verts.push_back(Vertex(width*0.5, -depth*0.5, height, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, width, height-1.0f, 0.0f));	
	verts.push_back(Vertex(width*0.5, depth*0.5, height, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, height-1.0f, 0.0f));	
	rendManager.addStaticGeometry("layout", verts, "../data/textures/wall1.jpg", GL_QUADS, 2);// texture && lighting

	// bottom left wall
	verts.clear();
	verts.push_back(Vertex(-width*0.5, -depth*0.5, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f));	
	verts.push_back(Vertex(-width*0.5, depth*0.5, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, width, 0.0f, 0.0f));	
	verts.push_back(Vertex(-width*0.5, depth*0.5, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, width, 1.0f, 0.0f));	
	verts.push_back(Vertex(-width*0.5, -depth*0.5, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f));	
	rendManager.addStaticGeometry("layout", verts, "../data/textures/wall2.jpg", GL_QUADS, 2);// texture && lighting

	// upper left wall
	verts.clear();
	verts.push_back(Vertex(-width*0.5, -depth*0.5, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f));	
	verts.push_back(Vertex(-width*0.5, depth*0.5, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, width, 0.0f, 0.0f));	
	verts.push_back(Vertex(-width*0.5, depth*0.5, height, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, width, height-1.0f, 0.0f));	
	verts.push_back(Vertex(-width*0.5, -depth*0.5, height, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, height-1.0f, 0.0f));	
	rendManager.addStaticGeometry("layout", verts, "../data/textures/wall1.jpg", GL_QUADS, 2);// texture && lighting

	// bottom front wall
	verts.clear();
	verts.push_back(Vertex(width*0.5, -depth*0.5, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f));	
	verts.push_back(Vertex(-width*0.5, -depth*0.5, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, width, 0.0f, 0.0f));	
	verts.push_back(Vertex(-width*0.5, -depth*0.5, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, width, 1.0f, 0.0f));	
	verts.push_back(Vertex(width*0.5, -depth*0.5, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f));	
	rendManager.addStaticGeometry("layout", verts, "../data/textures/wall2.jpg", GL_QUADS, 2);// texture && lighting

	// upper front wall
	verts.clear();
	verts.push_back(Vertex(width*0.5, -depth*0.5, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f));	
	verts.push_back(Vertex(-width*0.5, -depth*0.5, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, width, 0.0f, 0.0f));	
	verts.push_back(Vertex(-width*0.5, -depth*0.5, height, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, width, height-1.0f, 0.0f));	
	verts.push_back(Vertex(width*0.5, -depth*0.5, height, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, height-1.0f, 0.0f));	
	rendManager.addStaticGeometry("layout", verts, "../data/textures/wall1.jpg", GL_QUADS, 2);// texture && lighting

	for (int i = 0; i < furnitures.size(); ++i) {
		furnitures[i].draw(rendManager);
	}
}

bool Layout::within(Polygon2D line)
{
	for (int i = 0; i < line.size(); ++i) {
		if (line[i].x() < -width * 0.5 || line[i].x() > width * 0.5) return false;
		if (line[i].y() < -depth * 0.5 || line[i].y() > depth * 0.5) return false;
	}

	return true;
}

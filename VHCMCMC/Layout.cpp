﻿#include "common.h"
#include "Layout.h"
#include <QGLWidget>
#include "Util.h"

Layout::Layout() : width(8), depth(5), height(3)
{
	int types[] = {0, 1, 2, 3};

	printf("Layout initilized...\n");
	int hoge = sizeof(types);
	for (int i = 0; i < sizeof(types)/sizeof(types[0]); ++i) {
		while (true) {
			int type = types[i];

			float x = Util::genRand(-width * 0.5, width * 0.5);
			float y = Util::genRand(-depth * 0.5, depth * 0.5);
			float z = 0;
			float t = M_PI / 12.0f * (int)Util::genRand(0, 12);

			if (type == Furniture::TYPE_BOOKSHELF) {
				float rnd = Util::genRand(0, 1);
				if (rnd > 0.75f) {
					y = -depth * 0.5f + 0.21f;
					t = -M_PI;
				} else if (rnd > 0.5f) {
					y = depth * 0.5f - 0.21f;
					t = 0.0f;
				} else if (rnd > 0.25f) {
					x = -width * 0.5f + 0.21f;
					t = M_PI * 0.5f;
				} else {
					x = width * 0.5f - 0.21f;
					t = -M_PI * 0.5f;
				}
			}

			Furniture furniture(type, x, y, z, Util::normalizeAngle(t));

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

void Layout::change()
{
	float sigmaX = width * 0.18f;
	float sigmaY = depth * 0.18f;
	float sigmaTheta = M_PI * 0.18f;

	for (int i = 0; i < furnitures.size(); ++i) {
		while (true) {
			int type = furnitures[i].type;
			float x = Util::genRandNormal(furnitures[i].x, sigmaX * sigmaX);
			float y = Util::genRandNormal(furnitures[i].y, sigmaY * sigmaY);
			float z = 0;
			float t = Util::genRandNormal(furnitures[i].theta, sigmaTheta * sigmaTheta);
			t = Util::normalizeAngle(M_PI * (int)((t + M_PI / 24.0f) * 12.0f / M_PI) / 12.0f);

			if (type == Furniture::TYPE_BOOKSHELF) {
				float rnd = Util::genRand(0, 1);
				if (rnd > 0.75f) {
					y = -depth * 0.5f + 0.21f;
					t = M_PI;
				} else if (rnd > 0.5f) {
					y = depth * 0.5f - 0.21f;
					t = 0.0f;
				} else if (rnd > 0.25f) {
					x = -width * 0.5f + 0.21f;
					t = M_PI * 0.5f;
				} else {
					x = width * 0.5f - 0.21f;
					t = -M_PI * 0.5f;
				}
			}

			Furniture furniture(type, x, y, z, Util::normalizeAngle(t));

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
					if (fid == i) continue;

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
				furnitures[i] = furniture;
				break;
			}
		}
	}
}

/**
 * レイアウトに基づいてfeatureベクトルを生成する。
 */
cv::Mat Layout::feature()
{
	cv::Mat vec(furnitures.size() * 3, 1, CV_32F);

	for (int i = 0; i < furnitures.size(); ++i) {
		vec.at<float>(i * 3, 0) = furnitures[i].x;
		vec.at<float>(i * 3 + 1, 0) = furnitures[i].y;
		vec.at<float>(i * 3 + 2, 0) = furnitures[i].theta;
	}

	return vec;
}

void Layout::draw(VBORenderManager& rendManager)
{
	rendManager.removeStaticGeometry("layout");
	rendManager.removeModels("furniture");

	// floor
	std::vector<Vertex> verts;
	verts.push_back(Vertex(-width*0.5, -depth*0.5, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f));	
	verts.push_back(Vertex(width*0.5, -depth*0.5, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, width, 0.0f, 0.0f));	
	verts.push_back(Vertex(width*0.5, depth*0.5, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, width, depth, 0.0f));	
	verts.push_back(Vertex(-width*0.5, depth*0.5, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, depth, 0.0f));	
	rendManager.addStaticGeometry("layout", verts, "../data/textures/floor.jpg", GL_QUADS, 2);// texture && lighting

	// background cityscape
	verts.clear();
	verts.push_back(Vertex(-width*0.5, depth*0.5+0.1, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f));	
	verts.push_back(Vertex(width*0.5, depth*0.5+0.1, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0, 0.0f, 0.0f));	
	verts.push_back(Vertex(width*0.5, depth*0.5+0.1, height, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0, 1.0f, 0.0f));	
	verts.push_back(Vertex(-width*0.5, depth*0.5+0.1, height, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f));	
	rendManager.addStaticGeometry("layout", verts, "../data/textures/scape2.jpg", GL_QUADS, 2);// texture && lighting

	// bottom back wall
	verts.clear();
	verts.push_back(Vertex(-width*0.5, depth*0.5, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f));	
	verts.push_back(Vertex(width*0.5, depth*0.5, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, width, 0.0f, 0.0f));	
	verts.push_back(Vertex(width*0.5, depth*0.5, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, width, 1.0f, 0.0f));	
	verts.push_back(Vertex(-width*0.5, depth*0.5, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f));	
	rendManager.addStaticGeometry("layout", verts, "../data/textures/wall2.jpg", GL_QUADS, 2);// texture && lighting

	// upper back wall
	verts.clear();
	float step = 0.5f;
	for (float x = -width * 0.5; x < width * 0.5; x += 1.5f) {
		verts.push_back(Vertex(x, depth*0.5, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, x + width * 0.5, 0.0f, 0.0f));	
		verts.push_back(Vertex(x + step, depth*0.5, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, x + step + width * 0.5, 0.0f, 0.0f));	
		verts.push_back(Vertex(x + step, depth*0.5, height-0.8f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, x + step + width * 0.5, height-1.8f, 0.0f));	
		verts.push_back(Vertex(x, depth*0.5, height-0.8, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, x + width * 0.5, height-1.8f, 0.0f));	
	}
	verts.push_back(Vertex(-width*0.5, depth*0.5, height-0.8f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, height-1.8f, 0.0f));	
	verts.push_back(Vertex(width*0.5, depth*0.5, height-0.8f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, width, height-1.8f, 0.0f));	
	verts.push_back(Vertex(width*0.5, depth*0.5, height, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, width, height-1.0f, 0.0f));	
	verts.push_back(Vertex(-width*0.5, depth*0.5, height, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, height-1.0f, 0.0f));	
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

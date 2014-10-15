#include "Layout.h"
#include <random>
#include <QGLWidget>

Layout::Layout() : width(8), depth(8)
{
	std::mt19937 mtengine;
	std::uniform_real_distribution<double> distribution(0.0,1.0);

	for (int i = 0; i < 8; ++i) {
		while (true) {
			int type = i < 3 ? 0 : (i < 5 ? 1 : 2);

			float x = width * distribution(mtengine) - width * 0.5;
			float y = depth * distribution(mtengine) - depth * 0.5;		
			float theta = 3.14159265359 * distribution(mtengine);
			float width = 0;
			float depth = 0;
			float height = 0;
			if (type == 0) {
				width = 2.0;
				depth = 2.0;
				height = 1.3;
			} else if (type == 1) {
				width = 0.4;
				depth = 1.0;
				height = 1.6;
			} else if (type == 2) {
				width = 0.3;
				depth = 0.3;
				height = 1.63;
			}
			Furniture furniture(type, x, y, width, depth, height, theta);

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

	Layout proposedLayout(width, depth);

	for (int i = 0; i < furnitures.size(); ++i) {
		float x = furnitures[i].x + distributionX(mtengine);
		float y = furnitures[i].y + distributionY(mtengine);
		float theta = furnitures[i].theta + distributionTheta(mtengine);
		proposedLayout.addFurniture(Furniture(0, x, y, 0.5, 0.5, 1.3, theta));
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

void Layout::draw()
{
	// draw floor
	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-width / 2, -depth / 2, 0.0f);
	glVertex3f(width / 2, -depth / 2, 0.0f);
	glVertex3f(width / 2, depth / 2, 0.0f);
	glVertex3f(-width / 2, depth / 2, 0.0f);
	glEnd();

	// draw furniture
	for (int i = 0; i < furnitures.size(); ++i) {
		glPushMatrix();
		furnitures[i].draw();
		glPopMatrix();
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

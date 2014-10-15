#pragma once

#include <vector>
#include "Furniture.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "Polygon2D.h"

/**
 * This class represents a interior design of furnitures and fixters.
 */
class Layout
{
public:
	Layout();
	Layout(float width, float depth) : width(width), depth(depth) {}
	void addFurniture(Furniture furniture);
	Layout proposeChange(float sigmaX, float sigmaY, float sigmaTheta);
	cv::Mat feature();
	void draw();
	bool within(Polygon2D line);

public:
	float width;
	float depth;
	std::vector<Furniture> furnitures;
};


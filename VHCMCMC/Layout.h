#pragma once

#include "VBORenderManager.h"
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
	Layout(float width, float depth, float height) : width(width), depth(depth), height(height) {}
	void addFurniture(Furniture furniture);
	void change();
	cv::Mat feature();
	void draw(VBORenderManager& rendManager);
	bool within(Polygon2D line);

public:
	float width;
	float depth;
	float height;
	std::vector<Furniture> furnitures;
	VBORenderManager* rendManager;
};


#pragma once

#include <boost/geometry.hpp>
#include <boost/geometry/geometry.hpp> 
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/linestring.hpp>
#include <boost/geometry/geometries/register/box.hpp>
#include <boost/geometry/geometries/register/ring.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include "Polygon2D.h"
#include "VBORenderManager.h"

/**
 * This class represents a piece of furniture.
 */
class Furniture
{
public:
	static enum { TYPE_DININGTABLE = 0, TYPE_SOFATABLE, TYPE_BOOKSHELF, TYPE_LAMP };

public:
	Furniture(int type, float x, float y, float z, float theta);
	void draw(VBORenderManager& rendManager);
	void drawDiningTableChair(VBORenderManager& rendManager);
	void drawBookShelf(VBORenderManager& rendManager);
	void drawSofa(VBORenderManager& rendManager);
	void drawLamp(VBORenderManager& rendManager);
	void drawPicture(VBORenderManager& rendManager);
	Polygon2D footprint();

public:
	int type;
	float x;
	float y;
	float z;
	float width;
	float depth;
	float height;
	float theta;
	Polygon2D _footprint;
};


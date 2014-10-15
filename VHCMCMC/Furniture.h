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

//typedef boost::geometry::model::d2::point_xy<double> point_type;
//typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double> > polygon;

/**
 * This class represents a piece of furniture.
 */
class Furniture
{
public:
	Furniture(int type, float x, float y, float width, float depth, float height, float theta) : type(type), x(x), y(y), width(width), depth(depth), height(height), theta(theta) {}
	void draw();
	void drawDiningTableChair();
	void drawDiningTable();
	void drawDiningChair();
	void drawBookShelf();
	void drawLamp();
	Polygon2D footprint();
	//polygon footprint();

public:
	int type;
	float x;
	float y;
	float width;
	float depth;
	float height;
	float theta;
};


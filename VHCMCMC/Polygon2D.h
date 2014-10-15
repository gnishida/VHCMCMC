﻿#pragma once

#include "common.h"
#include "BBox.h"
#include <QVector2D>

/**
 * QVector2DをBoostのpointの代替として使用
 */
// BBox.hで定義済みなので、再定義は不要
//BOOST_GEOMETRY_REGISTER_POINT_2D_GET_SET(QVector2D, float, boost::geometry::cs::cartesian, x, y, setX, setY)



class Polygon2D : public std::vector<QVector2D> {
public:
	Polygon2D() {}
	~Polygon2D() {}

	void correct();
	float area() const;
	QVector2D centroid() const;
	bool contains(const QVector2D &pt) const;
	bool contains(const QVector2D &pt);
	bool Polygon2D::contains(const Polygon2D &polygon) const;
	Polygon2D convexHull() const;
	BBox envelope() const;
	void translate(float x, float y);
	void translate(float x, float y, Polygon2D &ret) const;
	void rotate(float angle);
	void rotate(float angle, Polygon2D &ret) const;
	void rotate(float angle, const QVector2D &orig);

	std::vector<Polygon2D> union_(const Polygon2D &polygon);

	std::vector<Polygon2D> tessellate();
	QVector2D getOBB(Polygon2D &obb) const;
	QVector2D getOBB(const QVector2D& dir, Polygon2D& obb) const;

	boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double> > convertToBoostPolygon() const;
};

/**
 * Polygon2DをBoostのringの代替として使用
 */
BOOST_GEOMETRY_REGISTER_RING(Polygon2D)

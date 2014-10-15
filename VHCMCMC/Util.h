#pragma once

#include <QGenericMatrix>
#include "common.h"

class Util {
	static const float MTC_FLOAT_TOL;

protected:
	Util();

public:
	// 3D
	static QVector3D calculateNormal(const QVector3D& p0, const QVector3D& p1, const QVector3D& p2);


	static float pointSegmentDistanceXY(const QVector3D &a, const QVector3D &b, const QVector3D &c, bool segmentOnly = true);

	static bool leftTurn(const QVector2D& a, const QVector2D& b, const QVector2D& c);
	static bool leftTurn(const QVector2D& v1, const QVector2D& v2);

	// angle computatiopn
	static float deg2rad(float deg);
	static float rad2deg(float rad);
	static float normalizeAngle(float angle);
	static float diffAngle(const QVector2D& dir1, const QVector2D& dir2, bool absolute = true);
	static float diffAngle(const QVector3D& dir1, const QVector3D& dir2, bool absolute = true);
	static float diffAngle(float angle1, float angle2, bool absolute = true);
	static float angleThreePoints(const QVector3D& pa, const QVector3D& pb, const QVector3D& pc);
	static QVector2D rotate(const QVector2D &pt, float rad);
	static QVector2D rotate(const QVector2D &pt, float rad, const QVector2D &orig);

	static QVector2D transform(const QVector2D &pt, const QVector2D &sourcePt, float rad, const QVector2D &targetPt);


	// random
	static float genRand();
	static float genRand(float a, float b);
	static float genRandNormal(float mean, float variance);
	static int sampleFromCdf(std::vector<float> &cdf);
};

#include "Util.h"
#include <random>


const float Util::MTC_FLOAT_TOL = 1e-6f;

QVector3D Util::calculateNormal(const QVector3D& p0, const QVector3D& p1, const QVector3D& p2) {
	return QVector3D::normal((p1-p0),(p2-p1));
}

/**
 * Return the sistance from segment ab to point c.
 * If the 
 */
float Util::pointSegmentDistanceXY(const QVector3D &a, const QVector3D &b, const QVector3D &c, bool segmentOnly) {
	float r_numerator = (c.x()-a.x())*(b.x()-a.x()) + (c.y()-a.y())*(b.y()-a.y());
	float r_denomenator = (b.x()-a.x())*(b.x()-a.x()) + (b.y()-a.y())*(b.y()-a.y());

	if (r_denomenator <= 0.0f) {
		return (a - c).length();
	}

	float r = r_numerator / r_denomenator;

	if (segmentOnly && (r < 0 || r > 1)) {
		float dist1 = SQR(c.x() - a.x()) + SQR(c.y() - a.y());
		float dist2 = SQR(c.x() - b.x()) + SQR(c.y() - b.y());
		if (dist1 < dist2) {	
			return sqrt(dist1);
		} else {
			return sqrt(dist2);
		}
	} else {
		return abs((a.y()-c.y())*(b.x()-a.x())-(a.x()-c.x())*(b.y()-a.y())) / sqrt(r_denomenator);
	}
}

bool Util::leftTurn(const QVector2D& a, const QVector2D& b, const QVector2D& c) {
	return leftTurn(b - a, c - b);
}

bool Util::leftTurn(const QVector2D& v1, const QVector2D& v2) {
	if (v1.x() * v2.y() - v1.y() * v2.x() >= 0) return true;
	else return false;
}

float Util::deg2rad(float deg) {
	return M_PI * deg / 180.0f;
}

float Util::rad2deg(float rad) {
	return rad * 180.0f / M_PI;
}

/**
 * 角度を正規化し、[-PI , PI]の範囲にする。
 */
float Util::normalizeAngle(float angle) {
	// まずは、正の値に変換する
	if (angle < 0.0f) {
		angle += ((int)(fabs(angle) / M_PI / 2.0f) + 1) * M_PI * 2;
	}

	// 次に、[0, PI * 2]の範囲にする
	angle -= (int)(angle / M_PI / 2.0f) * M_PI * 2;

	// 最後に、[-PI, PI]の範囲にする
	//if (angle > M_PI) angle = M_PI * 2.0f - angle;
	if (angle > M_PI) angle = angle - M_PI * 2.0f;		// fix this bug on 12/17

	return angle;
}

/**
 * Compute the difference in angle that is normalized in the range of [0, PI].
 * absolute == falseの時は、dir1の角度 - dir2の角度を[-PI, PI]で返却する。
 */
float Util::diffAngle(const QVector2D& dir1, const QVector2D& dir2, bool absolute) {
	float ang1 = atan2f(dir1.y(), dir1.x());
	float ang2 = atan2f(dir2.y(), dir2.x());

	if (absolute) {
		return fabs(normalizeAngle(ang1 - ang2));
	} else {
		return normalizeAngle(ang1 - ang2);
	}
}

float Util::diffAngle(const QVector3D& dir1, const QVector3D& dir2, bool absolute) {
	float ang1 = atan2f(dir1.y(), dir1.x());
	float ang2 = atan2f(dir2.y(), dir2.x());

	if (absolute) {
		return fabs(normalizeAngle(ang1 - ang2));
	} else {
		return normalizeAngle(ang1 - ang2);
	}
}

/**
 * Compute the difference in angle that is normalized in the range of [0, PI].
 */
float Util::diffAngle(float angle1, float angle2, bool absolute) {
	if (absolute) {
		return fabs(normalizeAngle(angle1 - angle2));
	} else {
		return normalizeAngle(angle1 - angle2);
	}
}

/**
 * Angle between 3 points A-B-C
 **/
float Util::angleThreePoints(const QVector3D& pa, const QVector3D& pb, const QVector3D& pc) {
	float a = (pb - pc).length();
	float b = (pa - pc).length();
	float c = (pa - pb).length();
	return acos(0.999f * (a*a + c*c - b*b) / (2.0f*a*c));
}

/**
 * 指定された点を、反時計回りにrad回転させた位置を返却する。
 */
QVector2D Util::rotate(const QVector2D &pt, float rad) {
	QVector2D ret;

	ret.setX(cosf(rad) * pt.x() - sinf(rad) * pt.y());
	ret.setY(sinf(rad) * pt.x() + cosf(rad) * pt.y());

	return ret;
}

/**
 * 指定された点を、反時計回りにrad回転させた位置を返却する。
 */
QVector2D Util::rotate(const QVector2D &pt, float rad, const QVector2D &orig) {
	return rotate(pt - orig, rad) + orig;
}



/**
 * 指定されたptを、座標変換する。
 * 座標変換は、sourcePtで指定された点がtargetPtへ移り、且つ、rad[radian]回転するような変換だ。
 */
QVector2D Util::transform(const QVector2D &pt, const QVector2D &sourcePt, float rad, const QVector2D &targetPt) {
	return rotate(pt - sourcePt, rad) + targetPt;
}


/**
 * Uniform乱数[0, 1)を生成する
 */
float Util::genRand() {
	return rand() / (float(RAND_MAX) + 1);
}

/**
 * 指定された範囲[a, b)のUniform乱数を生成する
 */
float Util::genRand(float a, float b) {
	return genRand() * (b - a) + a;
}

/**
 * Normal distributionを使用して乱数を生成する。
 */
float Util::genRandNormal(float mean, float variance) {
	/*
	static std::default_random_engine generator;

	std::normal_distribution<float> distribution(mean, sqrtf(variance));
	return distribution(generator);
	*/

#if 1
	float m = mean;
	float s = sqrt(variance);

	/* mean m, standard deviation s */
	float x1, x2, w, y1;
	static float y2;
	static int use_last = 0;

	if (use_last) {	/* use value from previous call */
		y1 = y2;
		use_last = 0;
	} else {
		do {
			x1 = 2.0 * genRand(0.0f, 1.0f) - 1.0;
			x2 = 2.0 * genRand(0.0f, 1.0f) - 1.0;
			w = x1 * x1 + x2 * x2;
		} while ( w >= 1.0 );

		w = sqrt( (-2.0 * log( w ) ) / w );
		y1 = x1 * w;
		y2 = x2 * w;
		use_last = 1;
	}

	return m + y1 * s;
#endif
}


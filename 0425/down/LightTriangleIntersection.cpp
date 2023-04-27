#include "include/LightGeometry.h"

namespace Light {
	double triangleIntersection(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Ray& ray, Vector4* point, Vector4* normal) {
		Vector4 p1;
		double dis = planeIntersection(Plane(v0, v1, v2), ray.o, ray.d, &p1, normal);
		if (std::isinf(dis)) return INFINITY;
		double area = Triangle(v0, v1, v2).Area() - Triangle(v0, v1, p1).Area() - Triangle(v1, v2, p1).Area() - Triangle(v2, v0, p1).Area();
		if (point) *point = p1;
		if (!isZero(area)) return INFINITY; // in triangle
		return dis;
	}
}
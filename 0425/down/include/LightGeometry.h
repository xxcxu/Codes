#pragma once
#include "LightMath.h"
#include <algorithm>
#include <sstream>
#include <fstream>
#include <vector>

namespace Light
{
	
	// 平面类型
	struct Plane
	{
	public:
		union 
		{
			struct 
			{
				// 平面表示方法 Ax+By+Cz+D = 0
				union
				{
					struct{double a, b, c;};
					Vector3 n;
				};
				double d;
			};
			struct 
			{
				double x, y, z, w;
			};
			Vector4 v;
		};
		Plane();                                                                    					    //构造平面: x=0
		Plane(Vector3 _n, double _d);                                                  				        //构造平面: dot(n,(x,y,z))+d=0
		Plane(Vector3 _n, Vector3 _v);                                            					        //构造平面: dot(n,v)+d=0
		Plane(Vector4 _v);                                                  							    //构造平面: dot(n,(x,y,z))+d=0
		Plane(double _a, double _b, double _c, double _d);                                              	//构造平面: ax+by+cz+d=0
		Plane(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3);										//构造平面: v1, v2, v3所在平面, 三点共线时返回x=0
		Plane(const Vector4 &v1, Vector4 v2, Vector4 v3);													//构造平面: v1, v2, v3所在平面, v1恒视为坐标, v2,v3为向量时，视为相对于v1偏移的向量
	};
	

	bool isParallel(const Vector4 &v1, const Vector4 &v2);
	//v1,v2恒视为向量, 判断两向量是否相互平行
	//算法: 判断两者叉积三分量的绝对值是否小于eps


	bool isPerpendicular(const Vector4 &v1, const Vector4 &v2);
	//v1,v2恒视为向量, 判断两向量是否相互垂直
	//算法: 判断两者点积的绝对值是否小于eps

	std::ostream& operator<< (std::ostream& os, const Plane &pl);
	//平面变量可以用 C++ 输出流的方式打印出来

	double planeIntersection(const Plane &pl, Vector4 v1, Vector4 v2, Vector4 *point = NULL, Vector4 *normal = NULL);
	/*
	求平面与直线交点
	v1恒视为坐标,
	v2若为坐标, v2将变换为v2-v1向量,
	v2若为向量, 视为v1出发, 以v2为方向发射的射线与平面pl求交
	返回值 ret: 定义为从v1抵达平面需要的v2单位数, 满足v1+ret*v2为交点
	point: 若被使用, 指向对象将被赋值为交点
	normal: 若被使用, 指向对象将被赋值为平面法向量

	当平面与射线平行时, 返回值为INFINITY, 可以用isinf函数判断
	*/

   
	struct Ray
	{
	public:
		Vector4 o;                      //光线原点
		Vector4 d;                      //射线方向
		Ray();
		Ray(Vector4 _o, Vector4 _d);
	};

	struct BoundingBox
	{
		union
		{
			double b[3][2];
			struct
			{
				double x0, x1;
				double y0, y1;
				double z0, z1;
			};
		};
		BoundingBox();
		BoundingBox(Vector3 v0, Vector3 v1);
		BoundingBox(double _x0, double _y0, double _z0, double _x1, double _y1, double _z1);
	};
	/*
	包围盒类用于求教加速，这个 BoundingBox 结构体可以表示各面平行于坐标系平面的包围盒。
	其中 x0, y0, z0 表示三个对应维度的最小值，x1, y1, z1 表示三个对应维度的最大值。
	你可以把它想象成以 (x0, y0, z0) 和 (x1, y1, z1) 为对角顶点的立方体。
	*/

	BoundingBox boundingBoxNone();
	/*
	返回一个空包围盒
	*/

	BoundingBox boundingBoxMerge(const BoundingBox &b1, const BoundingBox& b2);
	/*
	求最小的囊括 b1 和 b2 的包围盒，即边界取极值
	*/


	double boundingBoxIntersection(const BoundingBox &b, const Ray &r);
	/*
	求射线 r 是否与包围盒 b 相交
	返回值表示交点与射线端点 r.o 的距离，必定为非负，若无交点，返回INFINITY
	*/

	struct Triangle
	{
	public:
		union
		{
			Vector4 v[3];
			struct { Vector4 v0, v1, v2; };
		};
		Triangle();
		Triangle(Vector4 _v0, Vector4 _v1, Vector4 _v2);
		Triangle(Vector4 *_v);
		BoundingBox GetBoundingBox() const;
		double Intersection(const Ray &ray, Vector4 *point = NULL, Vector4 *normal = NULL) const; // 三角形与射线求交，需要选手完善 triangleIntersection 函数以实现正常功能
		Vector4 SamplePoint(Random::RAND_ENGINE *eng = NULL) const; // 均匀随机生成三角形中的点
		double Area() const; // 求三角形面积
		Plane plane() const; // 三角形所在的平面
	};

	double triangleIntersection(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Ray& ray, Vector4* point = NULL, Vector4* normal = NULL);
	/*
	三角形与射线求交函数
	v0, v1, v2表示三角形的三个顶点，保证为坐标
	ray.o 表示射线端点，必定为坐标
	ray.d 表示射线方向，必定为向量，模长为 1
	point 指向用于储存交点坐标的对象，若为 NULL，则忽略
	normal 指向用于储存法向量的对象，若为 NULL，则忽略
	返回值：
	返回值表示射线端点到交点的有向距离，交点在射线前进方向上则为正，反之则为负。即交点在射线后方的情况，求交依然成功。
	若射线与三角形平行，返回 INFINITY
	*/

	//球形类
	struct Sphere
	{
	public:
		union
		{
			Vector4 v;
			// 球心 c 半径 r
			struct {Vector3 c; double r;};
		};
		Sphere();
		Sphere(Vector4 _v);
		Sphere(Vector3 _c, double _r);
		BoundingBox GetBoundingBox() const;
		bool Intersection(const Ray &ray, double *d0 = NULL, Vector4 *n0 = NULL, double *d1 = NULL, Vector4 *n1 = NULL) const;
		double Intersection(const Ray& ray, Vector4* normal = NULL) const;
		bool isInside(const Ray &ray) const;
		Vector4 SamplePoint(Random::RAND_ENGINE* eng = NULL) const;
		double Area() const; // 表面积
	};

	struct Index
	{
		union
		{
			int v[3];
			struct { int v0, v1, v2; };
		};
	};

	struct MeshBase
	{
	public:
		int nVert;
		Vector4 *pVert;
		int nInd;
		Index* pInd;
		BoundingBox bbox;
		MeshBase();
		MeshBase(const char* _path);
		void Release();
		void Load(const char* _path);
		void MaintainBoundingBox();
		BoundingBox GetBoundingBox() const;
		virtual double Intersection(const Ray& ray, Vector4* point = NULL, Vector4* normal = NULL) const;
		void Save(const char* _path) const;
		void Translation(Vector4 trans);
		void Zoom(double scalex = 1.0, double scaley = 1.0, double scalez = 1.0);
		void Normalize();
		void Centeralize();
	};
}

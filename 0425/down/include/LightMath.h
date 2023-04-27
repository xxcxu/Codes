#pragma once

#include "LightRandom.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <typeinfo>
#include <string>

namespace Light
{

	const double EPS = 1e-6;
	const double PI = 3.14159265358979323846264338327950288419716939937510;
	const double INV_PI = 1.0 / PI;

	bool isZero(double d); // 判断浮点数是否"等于 0"

	struct Vector3;

	struct Vector4;

	class Matrix33;

	class Matrix34;

	struct Vector3
	{
	public:
		union
		{
			double _[3];
			struct {double x, y, z;};
		};
		Vector3 operator + (const Vector3 &b) const;
		Vector3 operator - (const Vector3 &b) const;
		Vector3 operator - () const;
		Vector3 operator * (const Vector3 &b) const;
		Vector3 operator / (const Vector3 &b) const;
		double sum() const;                                                       	        //各项之和
		double len_sq() const;                                                       	    //模长平方
		double len() const;                                                              	//模长
		Vector3 pow(double index) const;                                                    //次方
		bool iszero() const;																//判断向量是否为 0
	};

	// 构造 Vector3
	Vector3 MakeVector3();
	Vector3 MakeVector3(double *__);
	Vector3 MakeVector3(double _x, double _y, double _z);
	Vector3 MakeVector3(Vector4 v4);

	double dot(const Vector3 &v1, const Vector3 &v2);                                	    //点乘函数

	const Vector3 cross(const Vector3 &v1, const Vector3 &v2);                	            //叉乘函数

	Vector3 operator * (const Vector3 &v, double c);

	Vector3 operator * (double c, const Vector3 &v);

	Vector3 operator / (const Vector3 &v, double c);

	std::ostream& operator<< (std::ostream& os, const Vector3 &v);

	std::istream& operator>> (std::istream& is, Vector3 &v);

	struct Vector4
	{
	public:
		union
		{
			double _[4];
			struct
			{
				union
				{
					struct { double x, y, z; };
					Vector3 v;
				};
				double w;
			};
		};
		Vector4 operator + (const Vector4 &b) const;
		Vector4 operator - (const Vector4 &b) const;
		Vector4 operator - () const;
		Vector4 operator * (const Vector4 &b) const;                                    	            //按位相乘
		Vector4 operator / (const Vector4 &b) const;                                    	            //按位相除
		double sum() const;                                                           	                //分量求和
		double len_sq() const;                                                           	            //模长平方
		double len() const;                                                              	            //模长
		Vector4 pow(double index) const;                                                                //次方
		Vector3 vec3() const;                                                                           //转换成Vector3
		bool iscoord() const;                                                                           //判断是否为坐标, true: 坐标, false: 向量
		bool iszero() const;                                                                            //判断向量是否为 0
	};

	// 构造 Vector4
	Vector4 MakeVector4();
	Vector4 MakeVector4(double *__);
	Vector4 MakeVector4(double _x, double _y, double _z, double _w);
	Vector4 MakeVector4(Vector3 _v, double _w);

	Vector4 operator * (const Vector4 &v, double c);

	Vector4 operator * (double c, const Vector4 &v);

	Vector4 operator / (const Vector4 &v, double c);

	double dot(const Vector4 &v1, const Vector4 &v2);                                	            //点乘函数

	const Vector4 cross(const Vector4 &v1, const Vector4 &v2);                	                    //叉乘函数，按前三位计算，w=0（向量）

	std::ostream& operator<< (std::ostream& os, const Vector4 &v);

	std::istream& operator>> (std::istream& is, Vector4 &v);

	// 3x3 矩阵
	class Matrix33
	{
	public:
		union
		{
			struct
			{
				double
				m00,m01,m02,
				m10,m11,m12,
				m20,m21,m22;
			};
			struct
			{
				Vector3 row0, row1, row2;
			};
			Vector3 row[3];
			double m[3][3];
			double _[9];
		};
		Matrix33();
		Matrix33(
			double _m00, double _m01, double _m02,
			double _m10, double _m11, double _m12,
			double _m20, double _m21, double _m22
			);
		Matrix33(
			Vector3 *_row
			);
		Matrix33(
			const Vector3 &_row0,
			const Vector3 &_row1,
			const Vector3 &_row2
			);
		double det() const;                                              //返回: 行列式
		Matrix33 adj() const;                                    //返回: 伴随矩阵
		Matrix33 t() const;                                      //返回: 转置矩阵
		Matrix33 inv() const;                                    //返回: 逆矩阵

		Matrix33 operator * (const Matrix33 &m2) const;       //矩阵乘法
		Vector3 operator * (const Vector3 &v) const;          //矩阵乘法
	};

	Matrix33 operator / (const Matrix33 mat, const double &c);

	Matrix33 operator * (const Matrix33 mat, const double &c);

	Matrix33 operator * (const double &c, const Matrix33 mat);

	std::ostream& operator<< (std::ostream& os, const Matrix33 &v);

	std::istream& operator>> (std::istream& is, Matrix33 &v);

	// 3x4 矩阵
	class Matrix34
	{
	public:
		union
		{
			struct
			{
				double
				m00,m01,m02,m03,
				m10,m11,m12,m13,
				m20,m21,m22,m23;
			};
			struct
			{
				Vector4 row0, row1, row2;
			};
			Vector4 row[3];
			double m[3][4];
			double _[12];
		};
		Matrix34();
		Matrix34(
			double _m00, double _m01, double _m02, double _m03,
			double _m10, double _m11, double _m12, double _m13,
			double _m20, double _m21, double _m22, double _m23
			);
		Matrix34(
			Vector4 *_row
			);
		Matrix34(
			const Vector4 &_row0,
			const Vector4 &_row1,
			const Vector4 &_row2
			);
		Matrix33 m33() const;                                    //返回: 前三列子矩阵
		Matrix34 inv() const;                                    //返回: 逆矩阵

		Matrix34 operator * (const Matrix34 &m2) const;       //矩阵乘法
		Vector4 operator * (const Vector4 &v) const;          //矩阵乘法
	};
	
	Matrix34 operator / (const Matrix34 mat, const double c);

	Matrix34 operator * (const Matrix34 mat, const double &c);

	Matrix34 operator * (const double &c, const Matrix34 mat);

	std::ostream& operator<< (std::ostream& os, const Matrix34 &v);

	std::istream& operator>> (std::istream& is, Matrix34 &v);

	Vector4 MakePos(double _x, double _y, double _z); // 生成坐标（w=1）
	Vector4 MakeVec(double _x, double _y, double _z); // 生成向量（w=0）

	Matrix34 Matrix34Identical(); // 生成恒等变换的矩阵

	Matrix34 Matrix34Translate(Vector4 o); // 生成平移变换的矩阵

	Matrix34 Matrix34Rotation(double pitch, double yaw, double roll); // 生成旋转变换的矩阵

};
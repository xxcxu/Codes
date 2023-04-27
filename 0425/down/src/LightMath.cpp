#include "LightMath.h"

namespace Light
{
	bool isZero(double d)
	{
		return fabs(d) < EPS;
	}
	
/***********************************           Vec3          ********************************************/
	
	Vector3 MakeVector3()
	{
		Vector3 res;
		res.x = res.y = res.z = 0;
		return res;
	}

	Vector3 MakeVector3(double *__)
	{
		Vector3 res;
		for(int i = 0; i < 3; i++)
			res._[i] = __[i];
		return res;
	}

	Vector3 MakeVector3(double _x, double _y, double _z)
	{
		Vector3 res;
		res.x = _x;
		res.y = _y;
		res.z = _z;
		return res;
	}

	Vector3 MakeVector3(Vector4 v4)
	{
		Vector3 res;
		res.x = v4.x;
		res.y = v4.y;
		res.z = v4.z;
		return res;
	}

	Vector3 Vector3::operator + (const Vector3 &b) const
	{
		return MakeVector3(x + b.x, y + b.y, z + b.z);
	}
	
	Vector3 Vector3::operator - (const Vector3 &b) const
	{
		return MakeVector3(x - b.x, y - b.y, z - b.z);
	}
	
	Vector3 Vector3::operator - () const
	{
		return MakeVector3(-x, -y, -z);
	}
	
	Vector3 Vector3::operator * (const Vector3 &b) const
	{
		return MakeVector3(x * b.x, y * b.y, z * b.z);
	}
	
	
	Vector3 Vector3::operator / (const Vector3 &b) const
	{
		return MakeVector3(x / b.x, y / b.y, z / b.z);
	}

	Vector3 operator * (const Vector3 &v, double c)
	{
		return MakeVector3(v.x*c, v.y*c, v.z*c);
	}

	Vector3 operator * (double c, const Vector3 &v)
	{
		return MakeVector3(v.x*c, v.y*c, v.z*c);
	}

	Vector3 operator / (const Vector3 &v, double c)
	{
		return MakeVector3(v.x/c, v.y/c, v.z/c);
	}

	
	double Vector3::sum() const
	{
		return x + y + z;
	}

	double Vector3::len_sq() const
	{
		return x*x + y*y + z*z;
	}

	double Vector3::len() const
	{
		return sqrt(len_sq());
	}

	Vector3 Vector3::pow(double index) const
	{
		return MakeVector3(::pow(x, index), ::pow(y, index), ::pow(z, index));
	}

	bool Vector3::iszero() const
	{
		return
		std::abs(x) < EPS &&
		std::abs(y) < EPS &&
		std::abs(z) < EPS;
	}
	
	double dot(const Vector3 &v1, const Vector3 &v2)
	{
		return (v1*v2).sum();
	}

	
	const Vector3 cross(const Vector3 &v1, const Vector3 &v2)
	{
		return MakeVector3(
			v1.y*v2.z - v1.z*v2.y,
			v1.z*v2.x - v1.x*v2.z,
			v1.x*v2.y - v1.y*v2.x
			);
	}

	
	std::ostream& operator<< (std::ostream& os, const Vector3 &v)
	{
		os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
		return os;
	}
	
	
	std::istream& operator>> (std::istream& is, Vector3 &v)
	{
		is >> v.x >> v.y >> v.z;
		return is;
	}



/***********************************           Vec4          ********************************************/


	
	Vector4 MakeVector4()
	{
		return {0, 0, 0, 0};
	}

	
	Vector4 MakeVector4(double *__)
	{
		return {__[0], __[1], __[2], __[3]};
	}

	
	Vector4 MakeVector4(double _x, double _y, double _z, double _w)
	{
		return {_x, _y, _z, _w};
	}
	
	Vector4 MakeVector4(Vector3 _v, double _w)
	{
		Vector4 res;
		res.v = _v;
		res.w = _w;
		return res;
	}
	
	Vector4 Vector4::operator + (const Vector4 &b) const
	{
		return MakeVector4(x + b.x, y + b.y, z + b.z, w + b.w);
	}

	Vector4 Vector4::operator - (const Vector4 &b) const
	{
		return MakeVector4(x - b.x, y - b.y, z - b.z, w - b.w);
	}

	Vector4 Vector4::operator - () const
	{
		return MakeVector4(-x, -y, -z, -w);
	}
	
	Vector4 Vector4::operator * (const Vector4 &b) const
	{
		return MakeVector4(x * b.x, y * b.y, z * b.z, w * b.w);
	}
	
	Vector4 Vector4::operator / (const Vector4 &b) const
	{
		return MakeVector4(x / b.x, y / b.y, z / b.z, w / b.w);
	}

	double Vector4::sum() const
	{
		return x + y + z + w;
	}

	double Vector4::len_sq() const
	{
		return x*x + y*y + z*z + w*w;
	}

	double Vector4::len() const
	{
		return sqrt(len_sq());
	}

	Vector4 Vector4::pow(double index) const
	{
		return MakeVector4(::pow(x, index), ::pow(y, index), ::pow(z, index), ::pow(w, index));
	}

	double dot(const Vector4 &v1, const Vector4 &v2)
	{
		return (v1*v2).sum();
	}

	Vector4 operator * (const Vector4 &v, double c)
	{
		return MakeVector4(v.x*c, v.y*c, v.z*c, v.w*c);
	}

	Vector4 operator * (double c, const Vector4 &v)
	{
		return MakeVector4(v.x*c, v.y*c, v.z*c, v.w*c);
	}

	Vector4 operator / (const Vector4 &v, double c)
	{
		c = 1.0/c;
		return MakeVector4(v.x*c, v.y*c, v.z*c, v.w*c);
	}
	
	Vector3 Vector4::vec3() const
	{
		return MakeVector3(x, y, z);
	}

	bool Vector4::iscoord() const
	{
		return w > 0.5;
	}

	bool Vector4::iszero() const
	{
		return
		std::abs(x) < EPS &&
		std::abs(y) < EPS &&
		std::abs(z) < EPS &&
		std::abs(w) < EPS;
	}
	
	const Vector4 cross(const Vector4 &v1, const Vector4 &v2)
	{
		return MakeVector4(
			v1.y*v2.z - v1.z*v2.y,
			v1.z*v2.x - v1.x*v2.z,
			v1.x*v2.y - v1.y*v2.x,
			0);
	}

	
	std::ostream& operator<< (std::ostream& os, const Vector4 &v)
	{
		os << '(' << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ')';
		return os;
	}
	
	
	std::istream& operator>> (std::istream& is, Vector4 &v)
	{
		is >> v.x >> v.y >> v.z >> v.w;
		return is;
	}

/***********************************         Matrix33        ********************************************/

	
	Matrix33::Matrix33()
	{
		m00 = m01 = m02 =
		m10 = m11 = m12 =
		m20 = m21 = m22 =
		0;
	}
	
	
	Matrix33::Matrix33(
			double _m00, double _m01, double _m02,
			double _m10, double _m11, double _m12,
			double _m20, double _m21, double _m22
			)
	{
		m00 = _m00, m01 = _m01, m02 = _m02,
		m10 = _m10, m11 = _m11, m12 = _m12,
		m20 = _m20, m21 = _m21, m22 = _m22;
	}

	
	Matrix33::Matrix33(
			Vector3 *_row
			)
	{
		row[0] = _row[0],
		row[1] = _row[1],
		row[2] = _row[2];
	}

	
	Matrix33::Matrix33(
			const Vector3 &_row0,
			const Vector3 &_row1,
			const Vector3 &_row2
			)
	{
		row0 = _row0,
		row1 = _row1,
		row2 = _row2;
	}

	
	double Matrix33::det() const
	{
		return
		m00*m11*m22 +
		m01*m12*m20 +
		m02*m10*m21 -
		m02*m11*m20 -
		m01*m10*m22 -
		m00*m12*m21;
	}
	
	
	Matrix33 Matrix33::adj() const
	{
		return
		Matrix33(
			m11*m22 - m12*m21, m12*m20 - m10*m22, m10*m21 - m11*m20,
			m02*m21 - m01*m22, m00*m22 - m02*m20, m01*m20 - m00*m21,
			m01*m12 - m02*m11, m02*m10 - m00*m12, m00*m11 - m01*m10
		);
	}

	
	Matrix33 Matrix33::t() const
	{
		return
		Matrix33(
			m00, m10, m20,
			m01, m11, m21,
			m02, m12, m22
		);
	}
	
	
	Matrix33 Matrix33::inv() const
	{
		return
		Matrix33(
			m11*m22 - m12*m21, m02*m21 - m01*m22, m01*m12 - m02*m11,
			m12*m20 - m10*m22, m00*m22 - m02*m20, m02*m10 - m00*m12,
			m10*m21 - m11*m20, m01*m20 - m00*m21, m00*m11 - m01*m10
		)/det();
	}

	
	
	Matrix33 Matrix33::operator * (const Matrix33 &m2) const
	{
		Vector3
		col0 = MakeVector3(m2.m00, m2.m10, m2.m20),
		col1 = MakeVector3(m2.m01, m2.m11, m2.m21),
		col2 = MakeVector3(m2.m02, m2.m12, m2.m22);
		return Matrix33(
			dot(row0, col0), dot(row0, col1), dot(row0, col2),
			dot(row1, col0), dot(row1, col1), dot(row1, col2),
			dot(row2, col0), dot(row2, col1), dot(row2, col2)
		);
	}
	
	
	Vector3 Matrix33::operator * (const Vector3 &v) const
	{
		return MakeVector3(dot(row0, v), dot(row1, v), dot(row2, v));
	}

	Matrix33 operator * (const Matrix33 mat, const double &c)
	{
		return Matrix33(
			mat.m00*c, mat.m01*c, mat.m02*c,
			mat.m10*c, mat.m11*c, mat.m12*c,
			mat.m20*c, mat.m21*c, mat.m22*c
		);
	}

	Matrix33 operator * (const double &c, const Matrix33 mat)
	{
		return Matrix33(
			mat.m00*c, mat.m01*c, mat.m02*c,
			mat.m10*c, mat.m11*c, mat.m12*c,
			mat.m20*c, mat.m21*c, mat.m22*c
		);
	}

	Matrix33 operator / (const Matrix33 mat, const double &c)
	{
		return mat*(1/c);
	}


	
/***********************************         Matrix34        ********************************************/

	
	Matrix34::Matrix34()
	{
		m00 = m01 = m02 = m03 =
		m10 = m11 = m12 = m13 =
		m20 = m21 = m22 = m23 =
		0;
	}
	
	
	Matrix34::Matrix34(
			double _m00, double _m01, double _m02, double _m03,
			double _m10, double _m11, double _m12, double _m13,
			double _m20, double _m21, double _m22, double _m23
			)
	{
		m00 = _m00, m01 = _m01, m02 = _m02, m03 = _m03,
		m10 = _m10, m11 = _m11, m12 = _m12, m13 = _m13,
		m20 = _m20, m21 = _m21, m22 = _m22, m23 = _m23;
	}

	
	Matrix34::Matrix34(
			Vector4 *_row
			)
	{
		row[0] = _row[0],
		row[1] = _row[1],
		row[2] = _row[2];
	}

	
	Matrix34::Matrix34(
			const Vector4 &_row0,
			const Vector4 &_row1,
			const Vector4 &_row2
			)
	{
		row0 = _row0,
		row1 = _row1,
		row2 = _row2;
	}

	
	
	Matrix33 Matrix34::m33() const
	{
		return
		Matrix33(
			m00, m01, m02,
			m10, m11, m12,
			m20, m21, m22
		);
	}
	
	
	Matrix34 Matrix34::inv() const
	{
		Matrix33 invm = m33().inv();
		Vector3 invv = -(invm*MakeVector3(m03, m13, m23));
		return
		Matrix34(
			invm.m00, invm.m01, invm.m02, invv.x,
			invm.m10, invm.m11, invm.m12, invv.y,
			invm.m20, invm.m21, invm.m22, invv.z
		);
	}

	Matrix34 Matrix34::operator * (const Matrix34 &m2) const
	{
		Vector4
		col0 = MakeVector4(m2.m00, m2.m10, m2.m20, 0),
		col1 = MakeVector4(m2.m01, m2.m11, m2.m21, 0),
		col2 = MakeVector4(m2.m02, m2.m12, m2.m22, 0),
		col3 = MakeVector4(m2.m03, m2.m13, m2.m23, 1);
		return Matrix34(
			dot(row0, col0), dot(row0, col1), dot(row0, col2), dot(row0, col3),
			dot(row1, col0), dot(row1, col1), dot(row1, col2), dot(row1, col3),
			dot(row2, col0), dot(row2, col1), dot(row2, col2), dot(row2, col3)
		);
	}
	
	Vector4 Matrix34::operator * (const Vector4 &v) const
	{
		return MakeVector4(dot(row0, v), dot(row1, v), dot(row2, v), v.w);
	}

	Matrix34 operator * (const Matrix34 mat, const double &c)
	{
		return Matrix34(
			mat.m00*c, mat.m01*c, mat.m02*c, mat.m03*c,
			mat.m10*c, mat.m11*c, mat.m12*c, mat.m13*c,
			mat.m20*c, mat.m21*c, mat.m22*c, mat.m23*c
		);
	}

	Matrix34 operator * (const double &c, const Matrix34 mat)
	{
		return Matrix34(
			mat.m00*c, mat.m01*c, mat.m02*c, mat.m03*c,
			mat.m10*c, mat.m11*c, mat.m12*c, mat.m13*c,
			mat.m20*c, mat.m21*c, mat.m22*c, mat.m23*c
		);
	}

	Matrix34 operator / (const Matrix34 mat, const double &c)
	{
		return mat*(1/c);
	}
	
	Vector4 MakePos(double _x, double _y, double _z)
	{
		return MakeVector4(_x, _y, _z, 1);
	}

	Vector4 MakeVec(double _x, double _y, double _z)
	{
		return MakeVector4(_x, _y, _z, 0);
	}

	Matrix34 Matrix34Identical()
	{
		return Matrix34(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0
		);
	}

	Matrix34 Matrix34Translate(Vector4 o)
	{
		return Matrix34(
			1, 0, 0, o.x,
			0, 1, 0, o.y,
			0, 0, 1, o.z
		);
	}

	Matrix34 Matrix34Rotation(double pitch, double yaw, double roll)
	{
		return Matrix34(
			cos(yaw), 0, sin(yaw), 0,
			0, 1, 0, 0,
			-sin(yaw), 0, cos(yaw), 0
		)*
		Matrix34(
			1, 0, 0, 0,
			0, cos(pitch), sin(pitch), 0,
			0, -sin(pitch), cos(pitch), 0
		)*
		Matrix34(
			cos(roll), sin(roll), 0, 0,
			-sin(roll), cos(roll), 0, 0,
			0, 0, 1, 0
		);
	}

	
	std::ostream& operator<< (std::ostream& os, const Matrix33 &mat)
	{
		auto blanks = [](int l) -> std::string { std::string ret = ""; for(int i = 0; i < l; i++) ret += ' '; return ret; };
		std::string sm[3][3];
		int sml[3] = {};
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				sm[i][j] = std::to_string(mat.m[i][j]),
				sml[j] = std::max(sml[j], (int)sm[i][j].length());
		os << std::endl;
		for(int i = 0; i < 3; i++)
		{
			os << '|';
			for(int j = 0; j < 3; j++)
				os << blanks(sml[j] - sm[i][j].length()) << sm[i][j] << (j == 2 ? '|' : ' ');
			os << std::endl;
		}
		return os;
	}

	
	std::istream& operator>> (std::istream& is, Matrix33 &mat)
	{
		is >> mat.m00 >> mat.m01 >> mat.m02;
		is >> mat.m10 >> mat.m11 >> mat.m12;
		is >> mat.m20 >> mat.m21 >> mat.m22;
		return is;
	}
	
	std::ostream& operator<< (std::ostream& os, const Matrix34 &mat)
	{
		auto blanks = [](int l) -> std::string { std::string ret = ""; for(int i = 0; i < l; i++) ret += ' '; return ret; };
		std::string sm[3][4];
		int sml[4] = {};
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 4; j++)
				sm[i][j] = std::to_string(mat.m[i][j]),
				sml[j] = std::max(sml[j], (int)sm[i][j].length());
		for(int i = 0; i < 3; i++)
		{
			os << std::endl;
			os << '|';
			for(int j = 0; j < 4; j++)
				os << blanks(sml[j] - sm[i][j].length()) << sm[i][j] << (j == 3 ? '|' : ' ');
		}
		return os;
	}

	
	std::istream& operator>> (std::istream& is, Matrix34 &mat)
	{
		is >> mat.m00 >> mat.m01 >> mat.m02 >> mat.m03;
		is >> mat.m10 >> mat.m11 >> mat.m12 >> mat.m13;
		is >> mat.m20 >> mat.m21 >> mat.m22 >> mat.m23;
		return is;
	}
};
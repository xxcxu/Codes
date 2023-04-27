#include "LightGeometry.h"

namespace Light
{




/***********************************           Plane         ********************************************/



	Plane::Plane()
	{
		n = MakeVector3(1, 0, 0);
		d = 0;
	}


	Plane::Plane(Vector3 _n, double _d):Plane()
	{
		double len = sqrt(_n.len_sq());
		if (len > 0.0)
		{
			n = _n / len;
			d = _d / len;
		}
	}


	Plane::Plane(Vector3 _n, Vector3 _v):Plane(_n, -dot(_v, _n)){}


	Plane::Plane(Vector4 _v):Plane(_v.x, _v.y, _v.z, _v.w){}


	Plane::Plane(double _a, double _b, double _c, double _d):Plane(MakeVector3(_a, _b, _c), _d){}


	Plane::Plane(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3)
	{
		Vector3
		x = v2 - v1,
		y = v3 - v1,
		_n = cross(x, y);
		*this = Plane(_n, -dot(v1, _n));
	}


	Plane::Plane(const Vector4 &v1, Vector4 v2, Vector4 v3)
	{
		if(v2.iscoord())v2 = v2 - v1;
		if(v3.iscoord())v3 = v3 - v1;
		Vector4 _n = cross(v2, v3);
		_n.w = -dot(v1, _n);
		*this = Plane(_n);
	}


	std::ostream& operator<< (std::ostream& os, const Plane &pl)
	{
		os << '<' << pl.a << "x+" << pl.b << "y+" << pl.c << "z+" << pl.d << "=0>";
		return os;
	}


	bool isParallel(const Vector4 &v1, const Vector4 &v2)
	{
		return cross(v1, v2).iszero();
	}
	//v1,v2恒视为向量, 判断两向量是否相互平行
	//算法: 判断两者叉积三分量的绝对值是否小于eps


	bool isPerpendicular(const Vector4 &v1, const Vector4 &v2)
	{
		double d = dot(v1, v2);
		if (d < 0) d = -d;
		return d < EPS;
	}
	//v1,v2恒视为向量, 判断两向量是否相互垂直
	//算法: 判断两者点积的绝对值是否小于eps


	const char * type(const double &t)
	{
		return typeid(double).name();
	}




	double planeIntersection(const Plane &pl, Vector4 v1, Vector4 v2, Vector4 *point, Vector4 *normal)
	{
		v1.w = 1;
		if (v2.iscoord()) v2 = v2 - v1;
		if (isPerpendicular(pl.v, v2)) return INFINITY;
		double _d = - (dot(pl.v, v1) / dot(pl.v, v2));
		if (point)
			*point = v1 + _d*v2;
		if (normal)
			normal->v = pl.n,
			normal->w = 0.0;
		return _d;
	}

	Ray::Ray()
	{
		o = d = Vector4();
	}

	Ray::Ray(Vector4 _o, Vector4 _d)
	{
		_o.w = 1.0;
		if (_d.iscoord()) _d = _d - _o;
		o = _o;
		d = _d;
	}

	BoundingBox::BoundingBox() { x0 = x1 = y0 = y1 = z0 = z1 = 0; }
	BoundingBox::BoundingBox(Vector3 v0, Vector3 v1)
	{
		x0 = v0.x;
		y0 = v0.y;
		z0 = v0.z;
		x1 = v1.x;
		y1 = v1.y;
		z1 = v1.z;
	}
	BoundingBox::BoundingBox(double _x0, double _y0, double _z0, double _x1, double _y1, double _z1)
	{
		x0 = _x0;
		y0 = _y0;
		z0 = _z0;
		x1 = _x1;
		y1 = _y1;
		z1 = _z1;
	}

	BoundingBox boundingBoxNone()
	{
		return BoundingBox(INFINITY, INFINITY, INFINITY, -INFINITY, -INFINITY, -INFINITY);
	}

	BoundingBox boundingBoxMerge(const BoundingBox &b1, const BoundingBox& b2)
	{
		return BoundingBox(
			std::min(b1.x0, b2.x0),
			std::min(b1.y0, b2.y0),
			std::min(b1.z0, b2.z0),
			std::max(b1.x1, b2.x1),
			std::max(b1.y1, b2.y1),
			std::max(b1.z1, b2.z1)
		);
	}

	double boundingBoxIntersection(const BoundingBox &b, const Ray &r)
	{
		double dx, dy, dz, res = INFINITY, d;
		/*                   test_x                 */
		if (r.o.x < b.x0) dx = b.x0 - r.o.x;
		else if (r.o.x > b.x1) dx = b.x1 - r.o.x;
		else dx = 0.0;
		if (dx && !isZero(r.d.x))
		{
			d = dx / r.d.x;
			double _y = r.o.y + r.d.y*d, _z = r.o.z + r.d.z*d;
			if ( d > 0 && b.y0 <= _y && _y <= b.y1 && b.z0 <= _z && _z <= b.z1)
					res = std::min(res, d);
		}
		/*                   test_y                 */
		if (r.o.y < b.y0) dy = b.y0 - r.o.y;
		else if (r.o.y > b.y1) dy = b.y1 - r.o.y;
		else dy = 0.0;
		if (dy && !isZero(r.d.y))
		{
			d = dy / r.d.y;
			double _x = r.o.x + r.d.x*d, _z = r.o.z + r.d.z*d;
			if ( d > 0 && b.x0 <= _x && _x <= b.x1 && b.z0 <= _z && _z <= b.z1)
					res = std::min(res, d);
		}
		/*                   test_z                 */
		if (r.o.z < b.z0) dz = b.z0 - r.o.z;
		else if (r.o.z > b.z1) dz = b.z1 - r.o.z;
		else dz = 0.0;
		if (dz && !isZero(r.d.z))
		{
			d = dz / r.d.z;
			double _x = r.o.x + r.d.x*d, _y = r.o.y + r.d.y*d;
			if ( d > 0 && b.x0 <= _x && _x <= b.x1 && b.y0 <= _y && _y <= b.y1)
					res = std::min(res, d);
		}

		if(!dx && !dy && !dz) return 0.0;
		return res;
	}

	Triangle::Triangle()
	{
		v0 = v1 = v2 = Vector4();
	}

	Triangle::Triangle(Vector4 _v0, Vector4 _v1, Vector4 _v2)
	{
		v0 = _v0;
		v1 = _v1;
		v2 = _v2;
		v0.w = 1;
		if (!v1.iscoord()) v1 = v1 + v0;
		if (!v2.iscoord()) v2 = v2 + v0;
	}
	
	Triangle::Triangle(Vector4 *_v)
	{
		v0 = _v[0];
		v1 = _v[1];
		v2 = _v[2];
		if (!v1.iscoord()) v1 = v1 + v0;
		if (!v2.iscoord()) v2 = v2 + v0;
	}
	
	BoundingBox Triangle::GetBoundingBox() const
	{
		return BoundingBox(
			std::min(std::min(v0.x, v1.x), v2.x),
			std::min(std::min(v0.y, v1.y), v2.y),
			std::min(std::min(v0.z, v1.z), v2.z),
			std::max(std::max(v0.x, v1.x), v2.x),
			std::max(std::max(v0.y, v1.y), v2.y),
			std::max(std::max(v0.z, v1.z), v2.z)
		);
	}

	double Triangle::Intersection(const Ray &ray, Vector4 *point, Vector4 *normal) const
	{
		return triangleIntersection(v0, v1, v2, ray, point, normal);
	}

	Vector4 Triangle::SamplePoint(Random::RAND_ENGINE *eng) const
	{
		double u, v;
		if (eng)
			u = Random::randDouble(*eng),
			v = Random::randDouble(*eng);
		else
			u = Random::randDouble(),
			v = Random::randDouble();
		if (u + v > 1) u = 1 - u, v = 1 - v;
		return (v0 * (1 - u - v)) + (v1 * u) + (v2 * v);
	}

	double Triangle::Area() const
	{
		return cross(v2 - v0, v1 - v0).len() * 0.5;
	}

	Plane Triangle::plane() const
	{
		return Plane(v0, v1, v2);
	}

	Sphere::Sphere()
	{
		v = MakeVector4(0, 0, 0, 0);
	}
	Sphere::Sphere(Vector4 _v)
	{
		v = _v;
	}
	Sphere::Sphere(Vector3 _c, double _r)
	{
		c = _c;
		r = _r;
	}

	BoundingBox Sphere::GetBoundingBox() const
	{
		return BoundingBox(
			c.x - r, c.y - r, c.z - r,
			c.x + r, c.y + r, c.z + r
		);
	}

	bool Sphere::Intersection(const Ray& ray, double* d0, Vector4* n0, double* d1, Vector4* n1) const
	{
		Vector4 diff = MakeVector4(c - ray.o.v, 0);
		double dist, mid_d = dot(ray.d, diff);
		dist = r * r - (diff.len_sq() - mid_d * mid_d);
		if (dist < 0.0) return false;
		dist = sqrt(dist);
		if (d0)*d0 = mid_d - dist;
		if (n0)*n0 = (ray.d * (mid_d - dist) - diff) / r;
		if (d1)*d1 = mid_d + dist;
		if (n1)*n1 = (ray.d * (mid_d + dist) - diff) / r;
		return true;
	}

	double Sphere::Intersection(const Ray& ray, Vector4* normal) const
	{
		double d0, d1;
		Vector4 n0, n1;
		if (!Intersection(ray, &d0, &n0, &d1, &n1))return INFINITY;
		if (d0 >= EPS)
		{
			if (normal)*normal = n0;
			return d0;
		}
		if (d1 >= EPS)
		{
			if (normal)*normal = n1;
			return d1;
		}
		return INFINITY;
	}

	bool Sphere::isInside(const Ray& ray) const
	{
		double d_sq = (ray.o.v - c).len_sq();
		if (d_sq > r * r * (1 + EPS) * (1 + EPS)) return false;
		else if (d_sq < r * r * (1 - EPS) * (1 - EPS)) return true;
		return dot(ray.d.v, c - ray.o.v) > 0;
	}

	Vector4 Sphere::SamplePoint(Random::RAND_ENGINE* eng) const
	{
		double h = Random::randDouble(eng, -1.0, 1.0), theta = Random::randDouble(eng, -PI, PI);
		double radius = sqrt(1 - h * h);
		return MakeVector4(c, 1) + MakeVector4(radius * cos(theta), h, radius * sin(theta), 0) * r;
	}

	double Sphere::Area() const
	{
		return 4 * PI * r * r;
	}
	MeshBase::MeshBase()
	{
		nVert = 0;
		nInd = 0;
		pVert = NULL;
		pInd = NULL;
	}

	MeshBase::MeshBase(const char* _path)
	{
		nVert = 0;
		nInd = 0;
		pVert = NULL;
		pInd = NULL;
		Load(_path);
	}

	void MeshBase::Release()
	{
		nVert = 0;
		if (pVert) delete[] pVert, pVert = NULL;
		nInd = 0;
		if (pInd) delete[] pInd, pInd = NULL;
	}

	void MeshBase::Load(const char* _path)
	{
		Release();
		nVert = nInd = 0;
		printf("Loading Mesh:\"%s\"\n", _path);
		std::ifstream fin(_path);
		char line[1024];
		while (fin.getline(line, sizeof(line)))
		{
			std::stringstream ss(line);
			std::string type;
			std::string str;
			ss >> type;
			if (type == "v") nVert++;
			else if (type == "f")
			{
				while (ss >> str)nInd++;
				nInd -= 2;
			}
		}
		fin.close();
		fin.open(_path);
		pVert = new Vector4[nVert + 1ll];
		pInd = new Index[nInd];
		printf("nVert:%d nInd:%d\n", nVert, nInd);
		int cVert = 0, cInd = 0;
		while (fin.getline(line, sizeof(line)))
		{
			std::stringstream ss(line);
			std::string type;
			ss >> type;
			if (type == "v")
			{
				double x, y, z;
				ss >> x >> y >> z;
				cVert++;
				if (cVert <= nVert)
					pVert[cVert] = MakePos(x, y, -z);
			}
			else if (type == "f")
			{
				auto take_vindex = [=](std::string s) -> int {
					int ret = 0, t = 1;
					for (char c : s)
					{
						if (c == '-')t = -t;
						else if (!isdigit(c))break;
						else ret = ret * 10 + c - '0';
					}
					if (t == -1)ret = nVert + 1 - ret;
					return ret;
				};
				std::string index;
				int first_index;
				std::vector<int> vindex;
				ss >> index;
				first_index = take_vindex(index);
				while (ss >> index)vindex.push_back(take_vindex(index));
				for (int i = 1; i < vindex.size(); i++)
					pInd[cInd].v0 = first_index,
					pInd[cInd].v1 = vindex[i - 1],
					pInd[cInd++].v2 = vindex[i];
			}
		}
		MaintainBoundingBox();
	}

	void MeshBase::MaintainBoundingBox()
	{
		if (nVert)
			bbox = BoundingBox(pVert[1].vec3(), pVert[1].vec3());
		for (int i = 2; i <= nVert; i++)
			bbox = boundingBoxMerge(bbox, BoundingBox(pVert[i].vec3(), pVert[i].vec3()));
	}

	BoundingBox MeshBase::GetBoundingBox() const
	{
		return bbox;
	}

	double MeshBase::Intersection(const Ray& ray, Vector4* point, Vector4* normal) const
	{
		double d = INFINITY;
		Vector4 pnt = MakeVector4(), norm = MakeVector4();
		Vector4 retpnt = MakeVector4(), retnorm = MakeVector4();
		for (int i = 0; i < nInd; i++)
		{
			double pred = triangleIntersection(pVert[pInd[i].v0], pVert[pInd[i].v1], pVert[pInd[i].v2], ray, &pnt, &norm);
			if (pred<d && pred>EPS)
				retpnt = pnt,
				retnorm = norm,
				d = pred;
		}
		if (std::isinf(d))return d;
		if (point)*point = retpnt;
		if (normal)*normal = retnorm;
		return d;
	}

	void MeshBase::Save(const char* _path) const
	{
		std::ofstream fout(_path);
		for (int i = 1; i <= nVert; i++)
			fout << "v " << pVert[i].x << ' ' << pVert[i].y << ' ' << pVert[i].z << '\n';
		for (int i = 0; i < nInd; i++)
			fout << "f " << pInd[i].v0 << " " << pInd[i].v1 << " " << pInd[i].v2 << '\n';
		fout.close();
	}

	void MeshBase::Translation(Vector4 trans)
	{
		trans.w = 0;
		for (int i = 1; i <= nVert; i++)
			pVert[i] = pVert[i] + trans;
		MaintainBoundingBox();
	}

	void MeshBase::Zoom(double scalex, double scaley, double scalez)
	{
		for (int i = 1; i <= nVert; i++)
			pVert[i] = MakePos(pVert[i].x * scalex, pVert[i].y * scaley, pVert[i].z * scalez);
		MaintainBoundingBox();
	}

	void MeshBase::Normalize()
	{
		double scale = 1.0 / std::max(bbox.x1 - bbox.x0, std::max(bbox.y1 - bbox.y0, bbox.z1 - bbox.z0));
		if (!std::isinf(scale) && !std::isnan(scale))
			Zoom(scale, scale, scale);
		Centeralize();
	}

	void MeshBase::Centeralize()
	{
		Translation(MakeVector4(bbox.x0 + bbox.x1, bbox.y0 + bbox.y1, bbox.z0 + bbox.z1, 0.0) * -0.5);
	}
}
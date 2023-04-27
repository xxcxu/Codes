#include "LightMeshAccelerate.h"

namespace Light
{
	void Initialize(int nVert, Vector4 *pVert, int nInd, Index* pInd);

	void MeshAccelerate::Initialize()
	{
		Light::Initialize(nVert, pVert, nInd, pInd);
	}

	double MeshAccelerate::Intersection(const Ray& ray, Vector4* point, Vector4* normal) const
	{
		double d = Intersection(ray, normal);
		if (point) *point = ray.o + ray.d*d;
		return d;
	}

	int nVert;
	Vector4 *pVert;
	int nInd;
	Index* pInd;

	void Initialize(int nVert, Vector4 *pVert, int nInd, Index* pInd)
	{
		Light::nVert = nVert;
		Light::pVert = pVert;
		Light::nInd = nInd;
		Light::pInd = pInd;
	}

	double Intersection(const Ray& ray, Vector4* normal)
	{
		double d = INFINITY;
		for(int i = 0; i < nInd; i++)
		{
			Vector4 norm;
			double pd = triangleIntersection(
				pVert[pInd[i].v0],
				pVert[pInd[i].v1],
				pVert[pInd[i].v2],
				ray,
				NULL,
				&norm
			);
			if (pd < d && pd > EPS)
			{
				d = pd;
				if (normal) *normal = norm;
			}
		}
		return d;
	}
}
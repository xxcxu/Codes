#include "LightModel.h"

namespace Light
{
	Surface DiffuseSurface(Vector3 color)
	{
		Surface surf;
		surf.color = color;
		surf.type = SURFACE_TYPE_DIFFUSE;
		return surf;
	}

	Surface SpecularSurface(Vector3 color)
	{
		Surface surf;
		surf.color = color;
		surf.type = SURFACE_TYPE_SPECULAR;
		return surf;
	}

    ModelPack::ModelPack()
	{
		bbox = BoundingBox();
		models.clear();
	}

    void ModelPack::PushModel(Model * pModel)
	{
		if (models.empty())
			bbox = pModel->GetBoundingBox();
		else
			bbox = boundingBoxMerge(bbox, pModel->GetBoundingBox());
		models.push_back(pModel);
	}

    BoundingBox ModelPack::GetBoundingBox() const
	{
		return bbox;
	}

    double ModelPack::GetIntersection(const Ray &ray, Vector4 *norm, Surface *surface) const
	{
		double d = INFINITY;
		Vector4 _norm, *_pnorm = norm ? &_norm : 0;
		Surface _surface, *_psurface = surface ? &_surface : 0;
		for (const Model* model : models)
		{
			double _d = model->GetIntersection(ray, _pnorm, _psurface);
			if (_d < d && _d > EPS)
			{
				d = _d;
				if (norm) *norm = _norm;
				if (surface) *surface = _surface;
			}
		}
		return d;
	}

    ModelTriangle::ModelTriangle()
	{
		triangle = Triangle();
		surface = Surface();
	}

    ModelTriangle::ModelTriangle(Triangle _triangle, Surface _surface)
	{
		triangle = _triangle;
		surface = _surface;
	}

    BoundingBox ModelTriangle::GetBoundingBox() const
	{
		return triangle.GetBoundingBox();
	}

    double ModelTriangle::GetIntersection(const Ray &ray, Vector4 *norm, Surface *surface) const
	{
		double d = triangle.Intersection(ray, 0, norm);
		if (std::isinf(d) || d < EPS) return INFINITY;
		if (surface) *surface = this->surface;
		return d;
	}

	ModelSphere::ModelSphere()
	{
		sphere = Sphere();
		surface = Surface();
	}

	ModelSphere::ModelSphere(Sphere _sphere, Surface _surface)
	{
		sphere = _sphere;
		surface = _surface;
	}

	BoundingBox ModelSphere::GetBoundingBox() const
	{
		return sphere.GetBoundingBox();
	}
	double ModelSphere::GetIntersection(const Ray &ray, Vector4 *norm, Surface *surface) const
	{
		double d0, d1;
		Vector4 n0, n1;
		if (!sphere.Intersection(ray, &d0, &n0, &d1, &n1))return INFINITY;
		if (d0 >= EPS)
		{
			if (surface) *surface = this->surface;
			if (norm) *norm = n0;
			return d0;
		}
		if (d1 >= EPS)
		{
			Surface retsurf = this->surface;
			if (surface) *surface = retsurf;
			if (norm) *norm = n1;
			return d1;
		}
		return INFINITY;
	}

	ModelMesh::ModelMesh()
	{
		pMesh = NULL;
		surface = Surface();
	}

	ModelMesh::ModelMesh(MeshBase* _pMesh, Surface _surface)
	{
		pMesh = _pMesh;
		surface = _surface;
	}

	BoundingBox ModelMesh::GetBoundingBox() const
	{
		return pMesh->GetBoundingBox();
	}

	double ModelMesh::GetIntersection(const Ray &ray, Vector4 *norm, Surface *surface) const
	{
		double d = pMesh->Intersection(ray, NULL, norm);
		if (std::isinf(d) || d < EPS) return INFINITY;
		if (surface) *surface = this->surface;
		return d;
	}
}

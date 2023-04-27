#pragma once
#include "LightGeometry.h"
#include <vector>

namespace Light
{

	const int SURFACE_TYPE_DIFFUSE = 0;
	const int SURFACE_TYPE_SPECULAR = 1;

	struct Surface
	{
		int type;
		Vector3 color;
	};

	Surface DiffuseSurface(Vector3 color);
	Surface SpecularSurface(Vector3 color);

	class Model
	{
	public:
		virtual BoundingBox GetBoundingBox() const = 0;
		virtual double GetIntersection(const Ray &ray, Vector4 *norm = 0, Surface *surface = 0) const = 0;
	};

	class ModelPack: public Model
	{
		BoundingBox bbox;
		std::vector<const Model*> models;
	public:
		ModelPack();
		void PushModel(Model * pModel);
		virtual BoundingBox GetBoundingBox() const;
		virtual double GetIntersection(const Ray &ray, Vector4 *norm = 0, Surface *surface = 0) const;
	};

	class ModelTriangle: public Model
	{
		Triangle triangle;
		Surface surface;
	public:
		ModelTriangle();
		ModelTriangle(Triangle _triangle, Surface _surface);
		virtual BoundingBox GetBoundingBox() const;
		virtual double GetIntersection(const Ray &ray, Vector4 *norm = 0, Surface *surface = 0) const;
	};

	class ModelSphere : public Model
	{
		Sphere sphere;
		Surface surface;
	public:
		ModelSphere();
		ModelSphere(Sphere _sphere, Surface _surface);
		virtual BoundingBox GetBoundingBox() const;
		virtual double GetIntersection(const Ray &ray, Vector4 *norm = 0, Surface *surface = 0) const;
	};

	class ModelMesh : public Model
	{
		MeshBase* pMesh;
		Surface surface;
	public:
		ModelMesh();
		ModelMesh(MeshBase* _pMesh, Surface _surface);
		virtual BoundingBox GetBoundingBox() const;
		virtual double GetIntersection(const Ray& ray, Vector4* norm = 0, Surface* surface = 0) const;
	};

}
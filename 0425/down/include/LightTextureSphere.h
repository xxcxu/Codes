#pragma once
#include "LightModel.h"
#include "LightImage.h"

namespace Light
{
    class ModelSphereTexture: public Model
    {
        Image * texture;
        Sphere sph;
    public:
        ModelSphereTexture();
        ModelSphereTexture(Sphere _sphere, Image * _ptexture);
        virtual BoundingBox GetBoundingBox() const;
		virtual double GetIntersection(const Ray &ray, Vector4 *norm = 0, Surface *surface = 0) const;
        Color GetColor(Vector4 direction) const;
    };
}
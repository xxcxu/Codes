#include "include/LightTextureSphere.h"

namespace Light
{
    ModelSphereTexture::ModelSphereTexture()
    {
        texture = NULL;
        sph = Sphere();
    }

    ModelSphereTexture::ModelSphereTexture(Sphere _sphere, Image * _ptexture)
    {
        sph = _sphere;
        texture = _ptexture;
    }

    BoundingBox ModelSphereTexture::GetBoundingBox() const
    {
        return sph.GetBoundingBox();
    }

    double ModelSphereTexture::GetIntersection(const Ray &ray, Vector4 *norm, Surface *surface) const
    {
        double d = sph.Intersection(ray, norm);
        if (std::isinf(d)) return INFINITY;
        if (surface)
        {
            Vector4 pnt = ray.o + ray.d * d;
            Color c = GetColor((pnt - MakeVector4(sph.c, 1)) / sph.r);
            *surface = DiffuseSurface(MakeVector3(c.r / 255.0, c.g / 255.0, c.b / 255.0));
        }
        return d;
    }

    Color ModelSphereTexture::GetColor(Vector4 direction) const
    {
        /*
         * 你需要填写这个函数
         * 根据球心到交点的方向direction返回对应贴图上的像素值
         * z轴负方向是贴图中经纬度为 0 的位置
         * y轴正方向是北极点
         * x轴正方向是东经90度线与赤道的交点
        */
        return Color();
    }
}
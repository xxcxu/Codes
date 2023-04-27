#include "include/LightRayTrace.h"

namespace Light
{
    class SceneRayTrace: public Scene
    {
    public:
        Model * pModel;
        Source * pSource;
        int nSource;
        Vector3 vAmbient;
        SceneRayTrace() : Scene() { pModel = NULL; pSource = NULL; nSource = 0; vAmbient = MakeVector3(); }
        SceneRayTrace(Camera * _pcamara, Film * _pfilm, Model * _pmodel, Source * _psource, int nsource, Vector3 ambient) : Scene(_pcamara, _pfilm)
        {
            pModel = _pmodel;
            pSource = _psource;
            nSource = nsource;
            vAmbient = ambient;
        }
        Vector3 RayTrace(const Ray & ray);
        virtual Vector3 SampleRay(const Ray & ray, Random::RAND_ENGINE *eng = 0);
    };

    Scene* GetRayTraceScene(Camera * _pcamara, Film * _pfilm, Model * _pmodel, Source * _psource, int nsource, Vector3 ambient)
    {
        return new SceneRayTrace(_pcamara, _pfilm, _pmodel, _psource, nsource, ambient);
    }

    Vector4 SpecularReflectRay(Vector4 vIn, Vector4 vNorm);
    
    Vector3 SingleSourceContribution(Vector4 vPoint, Vector4 vNorm, Model * pModel, const Source &source);

    Vector3 SceneRayTrace::RayTrace(const Ray & ray)
    {
        Vector3 res = MakeVector3(); //本次采样返回的亮度
		double d;                    //用于记录光线起点和与场景交点的距离
		Vector4 vIn = -ray.d;        //入射方向
		Vector4 vNorm;               //交点表面法向量
		Vector4 vPoint;              //交点坐标
		Surface surface;             //记录得到的表面信息
		d = pModel->GetIntersection(ray, &vNorm, &surface); //调用场景模型类的求交函数
		if (!std::isinf(d)) // 求交函数返回 INFINITY，则求交失败
		{
            if (dot(vNorm, vIn) < 0) vNorm = -vNorm; //保证法向量与入射方向夹角不超过 90 度
			vPoint = ray.o + d*ray.d;                //求解交点位置
			if (surface.type == SURFACE_TYPE_DIFFUSE) //交点表面是漫反射的情况
			{
                res = vAmbient;                       //计算环境光亮度
                for (int i = 0; i < nSource; i++)     //枚举所有光源
                {
                    res = res + SingleSourceContribution(vPoint, vNorm, pModel, pSource[i]);
                    // 调用你需要完成的函数，计算当前光源对表面交点的亮度贡献
                }
			}
            else if(surface.type == SURFACE_TYPE_SPECULAR) //交点表面是镜面反射的情况
            {
                Ray reflect_ray;                                    //生成出射光
                reflect_ray.o = vPoint;                             //出射光的起点即是表面交点
                reflect_ray.d = SpecularReflectRay(vIn, vNorm);     //出射光方向由你的函数实现计算，需要满足反射定律
                res = RayTrace(reflect_ray);                        //沿出射光继续采样
            }
            
            res = res * surface.color;                              //计算反光率
		}
		return res;                   // 返回采样结果
    }

    Vector3 SceneRayTrace::SampleRay(const Ray & ray, Random::RAND_ENGINE *eng)
    {
        return RayTrace(ray);
    }

    
    Vector3 SingleSourceContribution(Vector4 vPoint, Vector4 vNorm, Model * pModel, const Source &source)
    {
        /*
        vPoint: 表示表面交点，必定为坐标
        vNorm: 表示表面法向量，必定为向量
        pModel: 模型类指针，用于计算光线遮挡
        source: 当前计算的光源信息

        返回值: 返回光源 source 对表面点 vPoint 的亮度贡献

        温馨提示：
        1. 光源可能和模型表面重叠，为了避免碰撞检测误差，建议碰撞检测光线的阻挡距离大于光源和表面点距离的 1-eps 倍的时候即算光照未被阻挡
        2. 表面背向光源时，光源不提供亮度贡献

        你需要完成这个函数以通过 cornellbox
        */
       
       return MakeVector3();
    }

    Vector4 SpecularReflectRay(Vector4 vIn, Vector4 vNorm)
    {
        /*
        vIn: 表示入射光方向，必定为向量
        vNorm: 表示表面法向量方向，必定为向量，保证和入射光方向夹角小于等于 90 度

        返回值: 你需要返回镜面反射条件下的出射方向，必须为向量，且模长必须为 1

        你需要完成这个函数以通过 balls
        */
        return MakeVector4();
    }
}
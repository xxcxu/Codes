#include "include/LightRayTrace.h"

using namespace Light;

CameraNormal cam;

ModelTriangle model_tri[6];
ModelSphere model_sph[30];
ModelPack model_pack;

Film film(1024, 1024, 4);

Source source[2];
Scene * scene;

int main()
{
    cam.SetCoordinateSystem(Matrix34CameraLookAt(MakePos(10.0, 5.0, 10.0), MakePos(0.0, 1.0, 0.0)));
    cam.SetVisualField(0.8, 0.8);
    double reflect_index = 0.8;
    model_tri[0] = ModelTriangle(Triangle(MakePos(-100, 0, -100), MakePos(-100, 0, 100), MakePos(100, 0, 100)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0)*reflect_index));
    model_tri[1] = ModelTriangle(Triangle(MakePos(-100, 0, -100), MakePos(100, 0, -100), MakePos(100, 0, 100)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0)*reflect_index));
    
    model_tri[2] = ModelTriangle(Triangle(MakePos(-1.0, 2.0, 0.0), MakePos(-2.0, 0.0, 1.0), MakePos(0.0, 0.0, 1.0)), SpecularSurface(MakeVector3(1.0, 1.0, 1.0)*reflect_index));
    model_tri[3] = ModelTriangle(Triangle(MakePos(-1.0, 2.0, 0.0), MakePos(0.0, 0.0, -1.0), MakePos(0.0, 0.0, 1.0)), SpecularSurface(MakeVector3(1.0, 1.0, 1.0)*reflect_index));
    model_tri[4] = ModelTriangle(Triangle(MakePos(-1.0, 2.0, 0.0), MakePos(0.0, 0.0, -1.0), MakePos(-2.0, 0.0, -1.0)), SpecularSurface(MakeVector3(1.0, 1.0, 1.0)*reflect_index));
    model_tri[5] = ModelTriangle(Triangle(MakePos(-1.0, 2.0, 0.0), MakePos(-2.0, 0.0, 1.0), MakePos(-2.0, 0.0, -1.0)), SpecularSurface(MakeVector3(1.0, 1.0, 1.0)*reflect_index));

    model_sph[0] = ModelSphere(Sphere(MakeVector3(0.0, 0.0, 0.0), 3000.0), DiffuseSurface(MakeVector3(0.8, 0.8, 1.0)*reflect_index));
    model_sph[1] = ModelSphere(Sphere(MakeVector3(0.0, 2.0, 0.0), 2.0), DiffuseSurface(MakeVector3(0.2001, 0.5, 0.18)));
    model_sph[2] = ModelSphere(Sphere(MakeVector3(2, 1.6, 3), 1.6), DiffuseSurface(MakeVector3(1.0, 0.5, 1.0)*reflect_index));
    model_sph[3] = ModelSphere(Sphere(MakeVector3(-4, 1.0, 3), 1.0), SpecularSurface(MakeVector3(1.0, 1.0, 1.0)*reflect_index));
    model_sph[4] = ModelSphere(Sphere(MakeVector3(3.5, 1.4, -2.5), 1.4), SpecularSurface(MakeVector3(1.0, 1.0, 1.0)*reflect_index));
    model_sph[5] = ModelSphere(Sphere(MakeVector3(-1.5, 1.2, -4.5), 1.2), DiffuseSurface(MakeVector3(0.5, 1.0, 1.0)*reflect_index));
    model_sph[6] = ModelSphere(Sphere(MakeVector3(-5.5, 3.0, -1.5), 3.0), SpecularSurface(MakeVector3(1.0, 1.0, 1.0)*reflect_index));
    model_sph[7] = ModelSphere(Sphere(MakeVector3(-3.5, 2.5, -12.5), 2.5), DiffuseSurface(MakeVector3(1.0, 1.0, 0.5)*reflect_index));
    for (int i = 0; i < 2; i++)
        model_pack.PushModel(model_tri + i);
    for (int i = 0; i < 8; i++)
        model_pack.PushModel(model_sph + i);

    source[0] = Source({MakePos(0.0, 600.0, 1500.0), MakeVector3(1.0, 1.0, 1.0) * 10000000.0});

    scene = GetRayTraceScene(&cam, &film, &model_pack, source, 1, MakeVector3(0.3, 0.3, 0.3));
    scene->Render("Balls", 16, 0, false, 1);
    delete scene;
}
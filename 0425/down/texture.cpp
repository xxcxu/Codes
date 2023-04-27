#include "include/LightRayTrace.h"
#include "include/LightTextureSphere.h"

using namespace Light;

class CamaraOutInside: public Camera
{
public:
    CamaraOutInside() {};
	Ray GenerateRay(double left, double top, double right, double bottom, Random::RAND_ENGINE *eng = NULL) const
    {
        double
        x = Random::randDouble(eng, left, right),
        y = Random::randDouble(eng, top, bottom);
        x += 116.33333333333333333333 / 360.0;
        Ray ret;
        double _x, _y, _z;
        _y = cos(y * PI);
        _x = -sin(x * 2 * PI);
        _z = cos(x * 2 * PI);
        _x = _x * sqrt(1.0 - _y*_y);
        _z = _z * sqrt(1.0 - _y*_y);
        ret.o = MakeVector4(MakeVector3(_x, _y, _z) * 7000, 1);
        ret.d = -MakeVec(_x, _y, _z);
        return ret;
    }
};


CameraNormal cam_normal;

CamaraOutInside cam;

ModelSphereTexture model_sph;

Film film(2500, 1250, 2);
Film film_normal(1024, 1024, 2);

Source source;
Scene * scene, * scene_normal;

int main()
{
    cam_normal.SetCoordinateSystem(Matrix34CameraLookAt(MakeVector4(MakeVector3(6000, 3000, 2000)*5.0, 1), MakePos(0, 0, 0)));
    cam_normal.SetVisualField(0.6, 0.6);
    Image earth_texture;
    earth_texture.LoadBitmapFromFile("earth.bmp");
    double reflect_index = 0.8;
    model_sph = ModelSphereTexture(Sphere(MakeVector3(0, 0, 0), 6371), &earth_texture);

    Vector3 source_pos;
    double pitch = (-23.5 + 90.0) / 180.0 * PI, yaw = 0.166666666666666666666 * 2.0 * PI;
    source_pos = MakeVector3(sin(pitch)*sin(yaw), cos(pitch), sin(pitch)*cos(yaw)) * 149597870.0;
    source = Source({MakeVector4(source_pos, 1.0), MakeVector3(1.0, 1.0, 1.0) * 5.0 * 149597870.0 * 149597870.0});

    scene = GetRayTraceScene(&cam, &film, &model_sph, &source, 1, MakeVector3(0.3, 0.3, 0.3));
    scene->Render("Earth", 4, 0, false, 1);
    scene_normal = GetRayTraceScene(&cam_normal, &film_normal, &model_sph, &source, 1, MakeVector3(0.3, 0.3, 0.3));
    scene_normal->Render("Earth3D", 16, 0, false, 1);
    delete scene;
    delete scene_normal;

}
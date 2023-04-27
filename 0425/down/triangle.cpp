#include "include/LightScene.h"
using namespace std;
using namespace Light;

class DepthMapScene : public Scene
{
public:
    Triangle * pTri;
    int nTri;
    DepthMapScene():Scene() { pTri = NULL; nTri = 0; }
    DepthMapScene(Camera * _pcamara, Film * _pfilm, Triangle * _ptriangle, int _ntriangle) : Scene( _pcamara, _pfilm )
    {
        pTri = _ptriangle;
        nTri = _ntriangle;
    }
	virtual Vector3 SampleRay(const Ray & ray, Random::RAND_ENGINE *eng = 0)
    {
        double d = INFINITY;
        for (int i = 0; i < nTri; i++)
            d = min(d, pTri[i].Intersection(ray));
        return MakeVector3(1.0, 1.0, 1.0) * max(min((500.0 / (1.0 + d)), 1.0), 0.0);
    }
};

CameraNormal cam;

Triangle triangle[32];

Film film(512, 512);

Scene * scene;

int main()
{
	cam.SetCoordinateSystem(Matrix34CameraLookAt(MakePos(-278, 273, -800), MakeVec(0, 0, 1)));

	double reflect_index = 0.8;
	triangle[0] = Triangle(MakePos(-549.6, 0.0, 559.2), MakePos(-0.0, 0.0, 0.0), MakePos(-552.8, 0.0, 0.0));
	triangle[1] = Triangle(MakePos(-549.6, 0.0, 559.2), MakePos(-0.0, 0.0, 0.0), MakePos(-0.0, 0.0, 559.2));
	triangle[2] = Triangle(MakePos(-556.0, 548.8, 0.0), MakePos(-0.0, 548.8, 559.2), MakePos(-556.0, 548.8, 559.2));
	triangle[3] = Triangle(MakePos(-556.0, 548.8, 0.0), MakePos(-0.0, 548.8, 559.2), MakePos(-0.0, 548.8, 0.0));
	triangle[4] = Triangle(MakePos(-549.6, 0.0, 559.2), MakePos(-0.0, 548.8, 559.2), MakePos(-0.0, 0.0, 559.2));
	triangle[5] = Triangle(MakePos(-549.6, 0.0, 559.2), MakePos(-0.0, 548.8, 559.2), MakePos(-556.0, 548.8, 559.2));
	triangle[6] = Triangle(MakePos(-0.0, 0.0, 559.2), MakePos(-0.0, 0.0, 0.0), MakePos(-0.0, 548.8, 0.0));
	triangle[7] = Triangle(MakePos(-0.0, 0.0, 559.2), MakePos(-0.0, 548.8, 559.2), MakePos(-0.0, 548.8, 0.0));
	triangle[8] = Triangle(MakePos(-552.8, 0.0, 0.0), MakePos(-549.6, 0.0, 559.2), MakePos(-556.0, 548.8, 559.2));
	triangle[9] = Triangle(MakePos(-552.8, 0.0, 0.0), MakePos(-556.0, 548.8, 0.0), MakePos(-556.0, 548.8, 559.2));

	triangle[10] = Triangle(MakePos(-130.0, 165.0, 65.0), MakePos(-82.0, 165.0, 225.0), MakePos(-240.0, 165.0, 272.0));
	triangle[11] = Triangle(MakePos(-130.0, 165.0, 65.0), MakePos(-290.0, 165.0, 114.0), MakePos(-240.0, 165.0, 272.0));
	triangle[12] = Triangle(MakePos(-290.0, 0.0, 114.0), MakePos(-290.0, 165.0, 114.0), MakePos(-240.0, 165.0, 272.0));
	triangle[13] = Triangle(MakePos(-290.0, 0.0, 114.0), MakePos(-240.0, 0.0, 272.0), MakePos(-240.0, 165.0, 272.0));
	triangle[14] = Triangle(MakePos(-130.0, 0.0, 65.0), MakePos(-130.0, 165.0, 65.0), MakePos(-290.0, 165.0, 114.0));
	triangle[15] = Triangle(MakePos(-130.0, 0.0, 65.0), MakePos(-290.0, 0.0, 114.0), MakePos(-290.0, 165.0, 114.0));
	triangle[16] = Triangle(MakePos(-82.0, 0.0, 225.0), MakePos(-82.0, 165.0, 225.0), MakePos(-130.0, 165.0, 65.0));
	triangle[17] = Triangle(MakePos(-82.0, 0.0, 225.0), MakePos(-130.0, 0.0, 65.0), MakePos(-130.0, 165.0, 65.0));
	triangle[18] = Triangle(MakePos(-240.0, 0.0, 272.0), MakePos(-240.0, 165.0, 272.0), MakePos(-82.0, 165.0, 225.0));
	triangle[19] = Triangle(MakePos(-240.0, 0.0, 272.0), MakePos(-82.0, 0.0, 225.0), MakePos(-82.0, 165.0, 225.0));

	triangle[20] = Triangle(MakePos(-423.0, 330.0, 247.0), MakePos(-265.0, 330.0, 296.0), MakePos(-314.0, 330.0, 456.0));
	triangle[21] = Triangle(MakePos(-423.0, 330.0, 247.0), MakePos(-472.0, 330.0, 406.0), MakePos(-314.0, 330.0, 456.0));
	triangle[22] = Triangle(MakePos(-423.0, 0.0, 247.0), MakePos(-423.0, 330.0, 247.0), MakePos(-472.0, 330.0, 406.0));
	triangle[23] = Triangle(MakePos(-423.0, 0.0, 247.0), MakePos(-472.0, 0.0, 406.0), MakePos(-472.0, 330.0, 406.0));
	triangle[24] = Triangle(MakePos(-472.0, 0.0, 406.0), MakePos(-472.0, 330.0, 406.0), MakePos(-314.0, 330.0, 456.0));
	triangle[25] = Triangle(MakePos(-472.0, 0.0, 406.0), MakePos(-314.0, 0.0, 456.0), MakePos(-314.0, 330.0, 456.0));
	triangle[26] = Triangle(MakePos(-314.0, 0.0, 456.0), MakePos(-314.0, 330.0, 456.0), MakePos(-265.0, 330.0, 296.0));
	triangle[27] = Triangle(MakePos(-314.0, 0.0, 456.0), MakePos(-265.0, 0.0, 296.0), MakePos(-265.0, 330.0, 296.0));
	triangle[28] = Triangle(MakePos(-265.0, 0.0, 296.0), MakePos(-265.0, 330.0, 296.0), MakePos(-423.0, 330.0, 247.0));
	triangle[29] = Triangle(MakePos(-265.0, 0.0, 296.0), MakePos(-423.0, 0.0, 247.0), MakePos(-423.0, 330.0, 247.0));

	cam.SetVisualField(0.68, 0.68);
    scene = new DepthMapScene(&cam, &film, triangle, 30);
    scene->Render("DepthMap", 4, 0, false, 1);
    delete scene;
}
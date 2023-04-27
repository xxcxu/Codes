#include "include/LightRayTrace.h"
#include <iomanip>
#include <random>

#include <ctime>

using namespace std;
using namespace Light;

CameraNormal cam;

ModelPack model_pack;
ModelTriangle model_tri[32];

Source sources[25];

Film film(256, 256, 8);

Scene* scene;

void CornellBox()
{
	cam.SetCoordinateSystem(Matrix34CameraLookAt(MakePos(-278, 273, -800), MakeVec(0, 0, 1)));

	double reflect_index = 0.8;
	model_tri[0] = ModelTriangle(Triangle(MakePos(-549.6, 0.0, 559.2), MakePos(-0.0, 0.0, 0.0), MakePos(-552.8, 0.0, 0.0)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[1] = ModelTriangle(Triangle(MakePos(-549.6, 0.0, 559.2), MakePos(-0.0, 0.0, 0.0), MakePos(-0.0, 0.0, 559.2)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[2] = ModelTriangle(Triangle(MakePos(-556.0, 548.8, 0.0), MakePos(-0.0, 548.8, 559.2), MakePos(-556.0, 548.8, 559.2)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[3] = ModelTriangle(Triangle(MakePos(-556.0, 548.8, 0.0), MakePos(-0.0, 548.8, 559.2), MakePos(-0.0, 548.8, 0.0)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[4] = ModelTriangle(Triangle(MakePos(-549.6, 0.0, 559.2), MakePos(-0.0, 548.8, 559.2), MakePos(-0.0, 0.0, 559.2)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[5] = ModelTriangle(Triangle(MakePos(-549.6, 0.0, 559.2), MakePos(-0.0, 548.8, 559.2), MakePos(-556.0, 548.8, 559.2)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[6] = ModelTriangle(Triangle(MakePos(-0.0, 0.0, 559.2), MakePos(-0.0, 0.0, 0.0), MakePos(-0.0, 548.8, 0.0)), DiffuseSurface(MakeVector3(0.3, 1.0, 0.3) * reflect_index));
	model_tri[7] = ModelTriangle(Triangle(MakePos(-0.0, 0.0, 559.2), MakePos(-0.0, 548.8, 559.2), MakePos(-0.0, 548.8, 0.0)), DiffuseSurface(MakeVector3(0.3, 1.0, 0.3) * reflect_index));
	model_tri[8] = ModelTriangle(Triangle(MakePos(-552.8, 0.0, 0.0), MakePos(-549.6, 0.0, 559.2), MakePos(-556.0, 548.8, 559.2)), DiffuseSurface(MakeVector3(1.0, 0.3, 0.3) * reflect_index));
	model_tri[9] = ModelTriangle(Triangle(MakePos(-552.8, 0.0, 0.0), MakePos(-556.0, 548.8, 0.0), MakePos(-556.0, 548.8, 559.2)), DiffuseSurface(MakeVector3(1.0, 0.3, 0.3) * reflect_index));

	model_tri[10] = ModelTriangle(Triangle(MakePos(-130.0, 165.0, 65.0), MakePos(-82.0, 165.0, 225.0), MakePos(-240.0, 165.0, 272.0)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[11] = ModelTriangle(Triangle(MakePos(-130.0, 165.0, 65.0), MakePos(-290.0, 165.0, 114.0), MakePos(-240.0, 165.0, 272.0)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[12] = ModelTriangle(Triangle(MakePos(-290.0, 0.0, 114.0), MakePos(-290.0, 165.0, 114.0), MakePos(-240.0, 165.0, 272.0)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[13] = ModelTriangle(Triangle(MakePos(-290.0, 0.0, 114.0), MakePos(-240.0, 0.0, 272.0), MakePos(-240.0, 165.0, 272.0)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[14] = ModelTriangle(Triangle(MakePos(-130.0, 0.0, 65.0), MakePos(-130.0, 165.0, 65.0), MakePos(-290.0, 165.0, 114.0)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[15] = ModelTriangle(Triangle(MakePos(-130.0, 0.0, 65.0), MakePos(-290.0, 0.0, 114.0), MakePos(-290.0, 165.0, 114.0)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[16] = ModelTriangle(Triangle(MakePos(-82.0, 0.0, 225.0), MakePos(-82.0, 165.0, 225.0), MakePos(-130.0, 165.0, 65.0)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[17] = ModelTriangle(Triangle(MakePos(-82.0, 0.0, 225.0), MakePos(-130.0, 0.0, 65.0), MakePos(-130.0, 165.0, 65.0)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[18] = ModelTriangle(Triangle(MakePos(-240.0, 0.0, 272.0), MakePos(-240.0, 165.0, 272.0), MakePos(-82.0, 165.0, 225.0)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[19] = ModelTriangle(Triangle(MakePos(-240.0, 0.0, 272.0), MakePos(-82.0, 0.0, 225.0), MakePos(-82.0, 165.0, 225.0)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));

	model_tri[20] = ModelTriangle(Triangle(MakePos(-423.0, 330.0, 247.0), MakePos(-265.0, 330.0, 296.0), MakePos(-314.0, 330.0, 456.0)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[21] = ModelTriangle(Triangle(MakePos(-423.0, 330.0, 247.0), MakePos(-472.0, 330.0, 406.0), MakePos(-314.0, 330.0, 456.0)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[22] = ModelTriangle(Triangle(MakePos(-423.0, 0.0, 247.0), MakePos(-423.0, 330.0, 247.0), MakePos(-472.0, 330.0, 406.0)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[23] = ModelTriangle(Triangle(MakePos(-423.0, 0.0, 247.0), MakePos(-472.0, 0.0, 406.0), MakePos(-472.0, 330.0, 406.0)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[24] = ModelTriangle(Triangle(MakePos(-472.0, 0.0, 406.0), MakePos(-472.0, 330.0, 406.0), MakePos(-314.0, 330.0, 456.0)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[25] = ModelTriangle(Triangle(MakePos(-472.0, 0.0, 406.0), MakePos(-314.0, 0.0, 456.0), MakePos(-314.0, 330.0, 456.0)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[26] = ModelTriangle(Triangle(MakePos(-314.0, 0.0, 456.0), MakePos(-314.0, 330.0, 456.0), MakePos(-265.0, 330.0, 296.0)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[27] = ModelTriangle(Triangle(MakePos(-314.0, 0.0, 456.0), MakePos(-265.0, 0.0, 296.0), MakePos(-265.0, 330.0, 296.0)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[28] = ModelTriangle(Triangle(MakePos(-265.0, 0.0, 296.0), MakePos(-265.0, 330.0, 296.0), MakePos(-423.0, 330.0, 247.0)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[29] = ModelTriangle(Triangle(MakePos(-265.0, 0.0, 296.0), MakePos(-423.0, 0.0, 247.0), MakePos(-423.0, 330.0, 247.0)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));

	//for (int i = 0; i < 2; i++)
	//	model_pack.PushModel(&model_tri[i]);
	for (int i = 0; i < 30; i++)
		model_pack.PushModel(&model_tri[i]);

    for (int x = 0; x < 5; x++)
        for (int y = 0; y < 5; y++)
	        sources[y*5 + x] = Source({MakePos(-343.0 + (-214.0 + 343.0) * (x * 0.25), 548.8, 227.0 + (332.0 - 227.0) * (y * 0.25)), MakeVector3(1.0, 1.0, 1.0) * 20 * (1.0 / 25.0) * (343 - 213) * (332 - 227)});

	cam.SetVisualField(0.68, 0.68);
    scene = GetRayTraceScene(&cam, &film, &model_pack, sources, 25, MakeVector3(0.2, 0.2, 0.2));
	scene->Render("CornellBox", 64, 0, true, 1);
    delete scene;
}

int main(int argc, char** argv)
{
	CornellBox();
	return 0;
}
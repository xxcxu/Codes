#include "include/LightPathTrace.h"
#include "LightMeshAccelerate.h"
#include <iomanip>
#include <random>

#include <ctime>

using namespace std;
using namespace Light;

CameraNormal cam;

ModelPack model_pack;
ModelTriangle model_tri[2];
MeshAccelerate mesh;
ModelMesh model_mesh;

Source source[2];

Film film(256, 256);

Scene* scene;


void Bunny()
{
	cam.SetCoordinateSystem(Matrix34CameraLookAt(MakePos(3.0, 2.0, -4.0), MakePos(0.0, 1.0, 0.0)));
	cam.SetVisualField(0.8, 0.8);

	double reflect_index = 0.8;
	model_tri[0] = ModelTriangle(Triangle(MakePos(-2, 0.0, 2), MakePos(2, 0.0, 2), MakePos(2, 0.0, -2)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));
	model_tri[1] = ModelTriangle(Triangle(MakePos(-2, 0.0, 2), MakePos(-2, 0.0, -2), MakePos(2, 0.0, -2)), DiffuseSurface(MakeVector3(1.0, 1.0, 1.0) * reflect_index));

#ifdef _WIN32
	mesh.Load("mesh\\bunny.obj");
#else
	mesh.Load("mesh/bunny.obj");
#endif
	mesh.Normalize();
	mesh.Zoom(2.0, 2.0, 2.0);
	mesh.Translation(MakeVec(0, -mesh.bbox.y0, 0));
	mesh.Initialize();

	model_mesh = ModelMesh(&mesh, DiffuseSurface(MakeVector3(0.3, 0.3, 0.3) * reflect_index));

	model_pack.PushModel(&model_tri[0]);
	model_pack.PushModel(&model_tri[1]);
	model_pack.PushModel(&model_mesh);

	source[0] = Source({Triangle(MakePos(-2.0, 6.0, -2.0), MakePos(2.0, 6.0, 2.0), MakePos(-2.0, 6.0, 2.0)), MakeVector3(1.0, 1.0, 1.0) * 10});
	source[1] = Source({Triangle(MakePos(-2.0, 6.0, -2.0), MakePos(2.0, 6.0, -2.0), MakePos(2.0, 6.0, 2.0)), MakeVector3(1.0, 1.0, 1.0) * 10});
	
    scene = GetPathTraceScene(&cam, &film, &model_pack, source, 2);
	scene->Render("Bunny", 200, 0, true);
    delete scene;
}

int main(int argc, char** argv)
{
	Bunny();
	return 0;
}
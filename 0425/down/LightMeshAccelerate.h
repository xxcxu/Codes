#include "include/LightGeometry.h"

namespace Light
{
	struct MeshAccelerate : public MeshBase
	{
	public:
		MeshAccelerate() : MeshBase() { };
		MeshAccelerate(const char* _path) : MeshAccelerate() { Load(_path); };
		void Initialize();
		virtual double Intersection(const Ray& ray, Vector4* point = NULL, Vector4* normal = NULL) const;
	};
}
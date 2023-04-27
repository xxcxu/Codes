#include "include/LightImage.h"

using namespace Light;

int main()
{
	Image img;
	img.LoadFromFile("bitmap.in");
	img.SaveBitmapToFile("bitmap.bmp");
}
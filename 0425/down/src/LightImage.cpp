#include"LightImage.h"

namespace Light
{
	Color::Color()
	{
		r = g = b = 0;
	}

	Color::Color(BYTE _r, BYTE _g, BYTE _b)
	{
		r = _r;
		g = _g;
		b = _b;
	}

	Image::Image()
	{
		width = height = 0;
		pixels = NULL;
	}

	Image::Image(UINT width, UINT height)
	{
		this->width = width;
		this->height = height;
		pixels = new Color[width*height]();
	}

	Image::~Image()
	{
		if(pixels)
			delete[] pixels,
			pixels=NULL;
	}

	void Image::Resize(UINT width, UINT height)
	{
		Color * newBuffer = new Color[width*height]();
		if (pixels)
		{
			for (UINT x = 0; x < std::min(width, this->width); x++)
				for (UINT y = 0; y < std::min(height,this->height); y++)
					newBuffer[y*width + x] = pixels[y*this->width + x];
			delete[] pixels;
		}
		pixels = newBuffer;
		this->width = width;
		this->height = height;
	}

	UINT Image::GetWidth() const { return width; }

	UINT Image::GetHeight() const { return height; }

	Color* Image::GetColorPtr() const { return pixels; };

	Color& Image::operator () (UINT x, UINT y)
	{
		assert(x < width);
		assert(y < height);
		return pixels[y*width + x];
	}

	Color Image::GetColor(UINT x, UINT y) const
	{
		if(x >= width || y >= height || !pixels) return Color(0, 0, 0);
		else return pixels[y*width + x];
	}

	void Image::SetColor(UINT x, UINT y, Color color)
	{
		if(x >= width || y >= height || !pixels) return;
		pixels[y*width + x] = color;
	}

	void Image::Clear(Color bkgroundColor)
	{
		for(UINT p = 0; p < width*height; p++)
			pixels[p] = bkgroundColor;
	}

	
	int Image::SaveToFile(const char * _path) const
	{
		FILE * pFile;
		pFile = fopen(_path, "w");
		if (!pFile)
			return 1,fprintf(stderr, "ERROR: Failed to open file ‘%s’\n", _path);
		fprintf(pFile, "%u %u\n", width, height);
		for (UINT p = 0; p < width*height; p++)
			fprintf(pFile, "%u %u %u\n", pixels[p].r, pixels[p].g, pixels[p].b);
		fclose(pFile);
		return 0;
	}

	int Image::LoadFromFile(const char * _path)
	{
		FILE * pFile;
		pFile = fopen(_path, "r");
		if (!pFile)
			return 1, fprintf(stderr, "ERROR: Failed to open file ‘%s’\n", _path);
		return LoadFromFp(pFile);
	}

	int Image::LoadFromFp(FILE *pFile)
	{
		UINT w,h;
		if(fscanf(pFile, "%u%u", &w, &h) != 2)
			return 1, fprintf(stderr, "ERROR: Incorrect format\n"), fclose(pFile);
		Resize(w,h);
		UINT r,g,b;
		for (UINT p = 0; p < width*height; p++)
			if (fscanf(pFile, "%u%u%u", &r, &g, &b) != 3)
				return 1, fprintf(stderr, "ERROR: Incorrect format\n"), fclose(pFile);
			else
				pixels[p] = Color(r, g, b);
		fclose(pFile);
		return 0;
	}

	int Image::LoadBitmapFromFile(const char* _path)
	{
		printf("Loading bitmap: '%s'\n", _path);
		FILE* pFile;
		pFile = fopen(_path, "rb");
		if (!pFile)
		{
			fprintf(stderr, "ERROR: Failed to open file '%s'\n", _path);
			return 1;
		}
		BITMAPFILEHEADER fileheader = {};
		BITMAPINFOHEADER infoheader = {};
		int res;
		res = fread(&fileheader, sizeof(fileheader), 1, pFile);
		res = fread(&infoheader, sizeof(infoheader), 1, pFile);
		bool wrong_format = false;
		if (fileheader.bfType != 0x4d42) wrong_format = true;
		if (fileheader.bfReserved1 != 0)wrong_format = true;
		if (fileheader.bfReserved2 != 0)wrong_format = true;
		if (fileheader.bfOffBits != 0x36)wrong_format = true;
		if (infoheader.biSize != 0x28)wrong_format = true;
		if (infoheader.biPlanes != 1)wrong_format = true;
		if (infoheader.biBitCount != 0x18)wrong_format = true;
		if (wrong_format)
		{
			fprintf(stderr, "ERROR: Wrong format!!!\n");
			return 1;
		}
		UINT rw = infoheader.biWidth, rh = infoheader.biHeight;
		Resize(rw, rh);
		UINT widthBytes = ((rw * 3 + 3) / 4) * 4;
		for (int y = rh - 1; y >= 0; y--)
		{
			res = fread(pixels + y * width, sizeof(Color), width, pFile);
			for (int i = 0; i < widthBytes - 3 * width; i++)
				fgetc(pFile);
		}
		fclose(pFile);
		return 0;
	}
}
#pragma once
#include<iostream>
#include<cstring>
#include<cstdio>
#include<assert.h>

typedef unsigned int UINT;
typedef unsigned char BYTE;

namespace Light
{
#pragma pack (1)
	struct Color
	{
		BYTE b,g,r;
		Color();
		Color(BYTE _r,BYTE _g,BYTE _b);
	};
#pragma pack ()
	class Image
	{
		UINT width, height;
		Color *pixels;
	public:
		Image();
		Image(UINT width,UINT height);
		~Image();
		void Resize(UINT width,UINT height);
		UINT GetWidth() const;
		UINT GetHeight() const;
		Color& operator () (UINT x,UINT y); //危险操作，谨慎使用
		Color GetColor(UINT x,UINT y) const;
		void SetColor(UINT x,UINT y,Color color);
		int SaveToFile(const char * _path) const;
		int LoadFromFile(const char * _path);
		int LoadFromFp(FILE *pFile);
		void SaveBitmapToFile(const char * _path) const;
		int LoadBitmapFromFile(const char* _path);
		Color* GetColorPtr() const;
		void Clear(Color bkgroundColor = Color(0, 0, 0));
	};


#ifndef _WINDOWS_
#pragma pack (1)
	struct BITMAPFILEHEADER {
		unsigned short    bfType;
		unsigned int   bfSize;
		unsigned short    bfReserved1;
		unsigned short    bfReserved2;
		unsigned int   bfOffBits;
	};

	struct BITMAPINFOHEADER {
		unsigned int      biSize;
		int       biWidth;
		int       biHeight;
		unsigned short       biPlanes;
		unsigned short       biBitCount;
		unsigned int      biCompression;
		unsigned int      biSizeImage;
		int       biXPelsPerMeter;
		int       biYPelsPerMeter;
		unsigned int      biClrUsed;
		unsigned int      biClrImportant;
	};
#pragma pack ()
#endif

};
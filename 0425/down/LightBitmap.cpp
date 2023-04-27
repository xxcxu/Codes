#include "LightImage.h"

namespace Light
{
	void Image::SaveBitmapToFile(const char *_path) const
	{
		//请在这里实现你的Bitmap输出
		int lineByte = (width * 3 + 3) / 4 * 4;
		FILE* fp = fopen(_path, "wb");
		if (!fp) return;

		// 位图信息头
		BITMAPFILEHEADER FileHeader;
		FileHeader.bfType = 0x4d42;
		FileHeader.bfSize = (unsigned long long)54 + lineByte * height;
		FileHeader.bfReserved1 = 0;
		FileHeader.bfReserved2 = 0;
		FileHeader.bfOffBits = 0x36;

		// 位图信息头
		BITMAPINFOHEADER InfoHeader;
		InfoHeader.biSize = 0x28;
		InfoHeader.biWidth = width;
		InfoHeader.biHeight = height;
		InfoHeader.biPlanes = 1;
		InfoHeader.biBitCount = 0x18;
		InfoHeader.biCompression = 0;
		InfoHeader.biSizeImage = 0;
		InfoHeader.biXPelsPerMeter = 0;
		InfoHeader.biYPelsPerMeter = 0;
		InfoHeader.biClrUsed = 0;
		InfoHeader.biClrImportant = 0;

		fwrite(&FileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
		fwrite(&InfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

		BYTE blank = 0;
		for (int i = height - 1; i >= 0; --i) {
			UINT b = width * 3;
			fwrite(pixels + i * width, sizeof(Color), width, fp);
			while (b != lineByte) fwrite(&blank, sizeof(BYTE), 1, fp), ++ b;
		}
		return;
	}
}
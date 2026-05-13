#pragma once
#ifndef MAPLOADER_H
#define MAPLOADER_H
#include "stb_image.h"
class texTure
{
public:
	unsigned int textureID;
	texTure(const char* mapPath);
	void loadTexture(bool isRGBA, bool flipVertically, bool generateMipmaps);


};

#endif // !MAPLOADER_H

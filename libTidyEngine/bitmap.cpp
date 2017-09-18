#include "bitmap.hpp"
#include "stb_image.h"

namespace TE {
Bitmap::~Bitmap()
{
	if (Data != nullptr)
		stbi_image_free(Data);
}
}
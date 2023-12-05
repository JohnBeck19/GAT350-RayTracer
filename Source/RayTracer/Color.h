#pragma once
#include <glm/glm.hpp>
#include <algorithm>

using color3_t = glm::vec3;
using color4_t = glm::vec4;
using rgba_t = uint32_t;

inline color4_t RGBAToColor(const rgba_t& rgba)
{
	uint8_t red = (rgba >> 24) & 0xFF;
	uint8_t green = (rgba >> 16) & 0xFF;
	uint8_t blue = (rgba >> 8) & 0xFF;
	uint8_t alpha = (rgba) & 0xFF;
	return color4_t(red/255.0f, green/255.0f, blue/255.0f, alpha/255.0f);

}

inline rgba_t ColorToRGBA(const color4_t& color)
{
	return ((rgba_t)(glm::clamp(color.a, 0.0f, 1.0f) * 255.0f)) | ((rgba_t)(glm::clamp(color.b, 0.0f, 1.0f) * 255.0f) << 8)
		| ((rgba_t)(glm::clamp(color.g, 0.0f, 1.0f) * 255.0f) << 16) | ((rgba_t)(glm::clamp(color.r, 0.0f, 1.0f) * 255.0f) << 24);
}

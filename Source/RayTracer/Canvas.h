#pragma once
#include "Color.h"
#include "glm/glm.hpp"
#include <vector>
class Canvas
{
public:
    Canvas(int width, int height, const class Renderer& renderer);
    ~Canvas();

    void Update();

    void Clear(const color4_t& color);
    void DrawPoint(const glm::ivec2& point, const color4_t& color);

    glm::vec2 GetSize() const { return m_size; }

    friend class Renderer;

private:
    class SDL_Texture* m_texture = nullptr;
    std::vector<rgba_t> m_buffer;
    glm::ivec2 m_size{0};
};
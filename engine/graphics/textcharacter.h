#pragma once

#include "image.h"
#include "mesh.h"
#include "rectangle.h"

#include <glm/glm.hpp>

#include <vector>

namespace pong
{

class TextCharacter : public Rectangle
{
public:
    TextCharacter(const Image& image, const glm::vec3& offset,
                  float width, float height);

    glm::vec3 mOffset { 0.0f };
};

} // namespace pong

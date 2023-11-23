#pragma once

#include "mesh.h"
#include "rectangle.h"

#include <glm/glm.hpp>

#include <vector>

namespace pong
{

class TextCharacter : public Rectangle
{
public:
    TextCharacter(const std::vector<unsigned char>& data, float width, float height, const glm::vec3& offset, int textureWidth, int textureHeight);

    void Draw(const glm::vec3& position) const override;

private:
    glm::vec3 mOffset { 0.0f };
};

} // namespace pong

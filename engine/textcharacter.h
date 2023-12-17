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
    TextCharacter(const std::vector<unsigned char>& data,
                  float width, float height, const glm::vec3& offset,
                  int textureWidthPixels, int textureHeightPixels);
    TextCharacter(const TextCharacter&) = delete;
    TextCharacter& operator=(const TextCharacter&) = delete;
    TextCharacter(TextCharacter&&) = default;
    TextCharacter& operator=(TextCharacter&&) = default;
    ~TextCharacter() = default;

    glm::vec3 GetOffset() const;
    void SetOffset(const glm::vec3& offset);

    void Draw(const glm::vec3& position) const override;

private:
    glm::vec3 mOffset { 0.0f };
};

} // namespace pong

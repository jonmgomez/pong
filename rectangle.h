#pragma once

#include "indexbuffer.h"
#include "mesh.h"

#include <glm/glm.hpp>

#include <array>
#include <memory>

class Rectangle : public Mesh
{
private:
    float mWidth { 0.0f };
    float mHeight { 0.0f };

public:
    Rectangle(const glm::vec3& position, float width, float height);
    Rectangle(float width, float height);

    void DrawObject() const;

    glm::vec3 mPosition { glm::vec3(0.0f) };
};

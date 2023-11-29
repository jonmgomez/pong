#pragma once

#include "mesh.h"

#include <glm/glm.hpp>

namespace pong
{

class UIElement
{
public:
    virtual void Render(const glm::vec3 position) const;

private:
    Mesh mMesh {};
};

} // namespace pong

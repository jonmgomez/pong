#pragma once

#include "component.h"

#include <glm/glm.hpp>

namespace pong
{

class Transform : public Component<Transform>
{
public:
    Transform() = default;
    Transform(glm::vec3 position) { mPosition = position; }

    glm::vec3 mPosition { 0.0f };

    friend class ComponentDeserializer;
};

} // namespace pong

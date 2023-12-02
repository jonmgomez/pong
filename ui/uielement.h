#pragma once

#include "colliderbox.h"
#include "mesh.h"

#include <glm/glm.hpp>

#include <functional>

namespace pong
{

enum class UIElementType
{
    Button,
    Text
};

class UIElement
{
public:
    virtual ~UIElement() = default;
    virtual void Render() const = 0;
    virtual UIElementType GetType() const = 0;

    int GetOrderLayer() const;
    void SetOrderLayer(int orderLayer);
    glm::vec3 GetPosition() const;
    virtual void SetPosition(const glm::vec3& position);

protected:
    glm::vec3 mPosition { 0.0f };

private:
    int mOrderLayer { 0 };
};

} // namespace pong

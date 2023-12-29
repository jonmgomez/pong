#pragma once

#include "colliderbox.h"
#include "graphic.h"
#include "rectangle.h"

#include <glm/glm.hpp>

#include <functional>

namespace pong
{

// Uses to build complex meshes using multiple meshes, with offsets from origin
struct MeshComponent
{
public:
    Rectangle mGraphic { 0.0f, 0.0f };
    glm::vec3 mOffset { 0.0f };
    glm::vec3 mPosition { 0.0f };

    MeshComponent() = default;
    MeshComponent(float width, float height, const glm::vec3& offset) :
        mGraphic{width, height},
        mOffset{offset},
        mPosition(mOffset)
    {
    }
};

class UIElement
{
public:
    virtual ~UIElement() = default;
    virtual std::vector<OffsetGraphic> GetRenderables() = 0;
    virtual BaseComponent* GetBaseComponent() = 0;

    int GetOrderLayer() const;
    void SetOrderLayer(int orderLayer);

private:
    int mOrderLayer { 0 };
};

} // namespace pong

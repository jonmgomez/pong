#pragma once

#include "colliderbox.h"
#include "rectangle.h"
#include "processeventvisitor.h"

#include <glm/glm.hpp>

#include <functional>

namespace pong
{

// Uses to build complex meshes using multiple meshes, with offsets from origin
struct MeshComponent
{
public:
    Rectangle mMesh { 0.0f, 0.0f };
    glm::vec3 mOffset { 0.0f };
    glm::vec3 mPosition { 0.0f };

    MeshComponent() = default;
    MeshComponent(float width, float height, const glm::vec3& offset) :
        mMesh{width, height},
        mOffset{offset},
        mPosition(mOffset)
    {
    }
};

class UIElement
{
public:
    virtual ~UIElement() = default;
    virtual void Render() const = 0;
    virtual void Accept(ProcessEventVisitor& visitor) = 0;

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

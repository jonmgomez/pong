#pragma once

#include "colliderbox.h"
#include "mesh.h"

#include <glm/glm.hpp>

#include <functional>

namespace pong
{

enum class UIEventType
{
    Pressed,
    Release,
    Hover,
    Unhover,
    EVENTS_COUNT
};

using ListenerCallbacks = std::vector<std::function<void()>>;

class UIElement
{
public:
    UIElement() = default;

    template<typename MeshType, typename... Args>
    void UseMesh(Args&&... args)
    {
        mMesh = MeshType(std::forward<Args>(args)...);
    }

    virtual void Render() const;

    void AddListener(UIEventType event, std::function<void()> callback);
    void OnEvent(UIEventType event);

    int GetOrderLayer() const;
    void SetOrderLayer(int orderLayer);
    glm::vec3 GetPosition() const;
    void SetPosition(const glm::vec3& position);
    ColliderBox* GetColliderBox() const;
    void SetColliderBox(float width, float height);
    bool IsPressed() const;
    bool IsHovered() const;

private:
    int mOrderLayer { 0 };
    glm::vec3 mPosition { 0.0f };
    Mesh mMesh {};
    std::unique_ptr<ColliderBox> mColliderBox { nullptr };
    std::array<ListenerCallbacks, static_cast<int>(UIEventType::EVENTS_COUNT)> mListeners {};
    bool mPressed { false };
    bool mHovered { false };
};

} // namespace pong

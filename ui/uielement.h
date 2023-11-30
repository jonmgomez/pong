#pragma once

#include "colliderbox.h"
#include "mesh.h"

#include <glm/glm.hpp>

#include <functional>

namespace pong
{

enum class UIEventType
{
    Click,
    Release,
    Hover,
    Unhover,
    EVENTS_COUNT
};

using ListenerVector = std::vector<std::function<void()>>;

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

private:
    int mOrderLayer { 0 };
    glm::vec3 mPosition { 0.0f };
    Mesh mMesh {};
    ColliderBox* mColliderBox { nullptr };
    std::array<ListenerVector, static_cast<int>(UIEventType::EVENTS_COUNT)> mListeners {};
};

} // namespace pong

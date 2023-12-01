#pragma once

#include "colliderbox.h"
#include "rectangle.h"
#include "uielement.h"

#include <glm/glm.hpp>

#include <array>
#include <functional>
#include <vector>

namespace pong
{

using ListenerCallbacks = std::vector<std::function<void()>>;

class Button : public UIElement
{
public:
    Button(float width, float height);

    void Render() const override;
    UIElementType GetType() const override;

    void AddListener(UIEventType event, std::function<void()> callback);
    void OnEvent(UIEventType event);

    void SetPosition(const glm::vec3& position) override;
    void Resize(float width, float height);
    ColliderBox* GetColliderBox();
    bool IsPressed() const;
    bool IsHovered() const;

private:
    Rectangle mRectangle { 0.0f, 0.0f };
    ColliderBox mColliderBox { 0.0f, 0.0f };
    std::array<ListenerCallbacks, static_cast<int>(UIEventType::EVENTS_COUNT)> mListeners {};
    bool mPressed { false };
    bool mHovered { false };
};

} // namespace pong

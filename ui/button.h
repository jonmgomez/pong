#pragma once

#include "component.h"
#include "rectangle.h"
#include "uielement.h"

#include <glm/glm.hpp>

#include <array>
#include <functional>
#include <vector>

namespace pong
{

enum class ButtonEvent
{
    Pressed,
    Release,
    Hover,
    Unhover,
    EVENTS_COUNT
};

using ListenerCallbacks = std::vector<std::function<void()>>;

class Button : public UIElement, public Component<Button>
{
public:
    Button(float width, float height);

    void Render() const override;
    void Accept(ProcessEventVisitor& uiElement) override;

    void AddListener(ButtonEvent event, std::function<void()> callback);
    void OnEvent(ButtonEvent event);

    void SetPosition(const glm::vec3& position) override;
    float GetWidth() const;
    float GetHeight() const;
    void Resize(float width, float height);
    RectangleBounds GetBounds() const;
    bool WasPressed() const;
    bool WasHovered() const;

private:
    Rectangle mRectangle { 0.0f, 0.0f };
    RectangleBounds mBounds {};
    std::array<ListenerCallbacks, static_cast<int>(ButtonEvent::EVENTS_COUNT)> mListeners {};
    bool mPressed { false };
    bool mHovered { false };
};

} // namespace pong

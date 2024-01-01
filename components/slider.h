#pragma once

#include "component.h"
#include "rectangle.h"
#include "uicomponent.h"

#include <array>
#include <functional>
#include <vector>

namespace pong
{

class Slider : public UIComponent, public Component<Slider>
{
public:
    Slider() = default;
    Slider(float width, float height, float min, float max, float step, float startValue);
    ~Slider() = default;

    void SetVariables(float min, float max, float step, float startValue);
    void Resize(float width, float height);

    std::vector<OffsetGraphic> GetRenderables() override;
    BaseComponent* GetBaseComponent() override;

    void OnMouseDown(const glm::vec3& mousePosition);
    void OnMouseReleased();
    void AddValueChangeListener(std::function<void(float)> listener);

    bool WasPressed() const;
    RectangleBounds GetBounds() const;
    float GetValue() const;
    void SetValue(float value);

private:
    void CalculateStart();

    // Represents the slider background, the slider handle, and the slider fill
    std::array<OffsetRectangle, 4> mBorders {};
    OffsetRectangle mFill {};
    OffsetRectangle mHandle {};
    RectangleBounds mBounds {};
    std::vector<std::function<void(float)>> mValueChangeListeners {};
    float mWidth { 0.0f };
    float mHeight { 0.0f };
    float mMin { 0.0f };
    float mMax { 0.0f };
    float mStep { 0.0f };
    float mValue { 0.0f };
    bool mWasPressed { false };
};

} // namespace pong

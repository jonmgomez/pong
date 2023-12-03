#pragma once

#include "colliderbox.h"
#include "rectangle.h"
#include "uielement.h"

#include <array>
#include <functional>
#include <vector>

namespace pong
{

struct SliderMesh
{
    Rectangle mMesh { 0.0f, 0.0f };
    glm::vec3 mOffset { 0.0f };
    glm::vec3 mPosition { 0.0f };
};

class Slider : public UIElement
{
public:
    Slider(float width, float height, float min, float max, float step, float startValue);
    ~Slider() = default;

    void Render() const override;
    UIElementType GetType() const override;
    void SetPosition(const glm::vec3& position) override;

    void OnMouseHeld(glm::vec3 mousePosition);
    void OnMouseReleased();
    void AddValueChangeListener(std::function<void(float)> listener);

    bool WasPressed() const;
    ColliderBox* GetColliderBox();
    float GetValue() const;

private:
    // Represents the slider background, the slider handle, and the slider fill
    std::array<SliderMesh, 6> mSliderMeshes {};
    ColliderBox mHandleColliderBox { 0.0f, 0.0f };
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

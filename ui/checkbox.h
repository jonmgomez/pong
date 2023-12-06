#pragma once

#include "colliderbox.h"
#include "rectangle.h"
#include "slider.h"
#include "uielement.h"

namespace pong
{

class CheckBox : public UIElement
{
public:
    CheckBox(float width, float height, bool defaultValue);

    UIElementType GetType() const override;
    void Render() const override;
    void SetPosition(const glm::vec3& position) override;

    void OnClick();
    void AddValueChangeListener(std::function<void(bool)> callback);

    void SetValue(bool value);
    bool GetValue() const;
    ColliderBox* GetColliderBox();

private:
    std::array<MeshComponent, 4> mLines {};
    Rectangle mFill { 0.0f, 0.0f };
    ColliderBox mColliderBox { 0.0f, 0.0f };
    std::vector<std::function<void(bool)>> mValueChangeListeners {};
    bool mValue { true };
};

} // namespace pong

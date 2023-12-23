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

    void Render() const override;
    void Accept(ProcessEventVisitor& visitor) override;
    void SetPosition(const glm::vec3& position) override;

    void OnClick();
    void AddValueChangeListener(std::function<void(bool)> callback);

    void SetValue(bool value);
    bool GetValue() const;
    RectangleBounds GetBounds() const;

private:
    std::array<MeshComponent, 4> mLines {};
    Rectangle mFill { 0.0f, 0.0f };
    RectangleBounds mBounds {};
    std::vector<std::function<void(bool)>> mValueChangeListeners {};
    bool mValue { true };
};

} // namespace pong

#pragma once

#include "component.h"
#include "graphic.h"
#include "rectangle.h"
#include "slider.h"
#include "uielement.h"

namespace pong
{

class CheckBox : public UIElement, public Component<CheckBox>
{
public:
    CheckBox(float width, float height, bool defaultValue);

    std::vector<OffsetGraphic> GetRenderables() override;
    void Accept(ProcessEventVisitor& visitor) override;

    void OnClick();
    void AddValueChangeListener(std::function<void(bool)> callback);

    void SetValue(bool value);
    bool GetValue() const;
    RectangleBounds GetBounds() const;

private:
    std::array<OffsetRectangle, 4> mLines {};
    OffsetRectangle mFill {};
    RectangleBounds mBounds {};
    std::vector<std::function<void(bool)>> mValueChangeListeners {};
    bool mValue { true };
};

} // namespace pong

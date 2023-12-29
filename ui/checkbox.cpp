#include "checkbox.h"

namespace pong
{

constexpr float BORDER_THICKNESS = 10.0f;
constexpr float BORDER_GAP = 10.0f;
constexpr float BORDER_TOTAL = (BORDER_THICKNESS + BORDER_GAP) * 2.0f;
constexpr float BORDER_ONE_SIDE = BORDER_TOTAL / 2.0f;

CheckBox::CheckBox(float width, float height, bool defaultValue) :
    mLines {
        OffsetRectangle { Rectangle(width,            BORDER_THICKNESS), glm::vec3(0.0f, height / 2.0f - BORDER_THICKNESS / 2.0f, 0.0f) },
        OffsetRectangle { Rectangle(width,            BORDER_THICKNESS), glm::vec3(0.0f, height / -2.0f + BORDER_THICKNESS / 2.0f, 0.0f) },
        OffsetRectangle { Rectangle(BORDER_THICKNESS, height          ), glm::vec3(width / -2.0f + BORDER_THICKNESS / 2.0f, 0.0f, 0.0f) },
        OffsetRectangle { Rectangle(BORDER_THICKNESS, height          ), glm::vec3(width / 2.0f - BORDER_THICKNESS / 2.0f, 0.0f, 0.0f) }
    },
    mFill { Rectangle(width - (BORDER_THICKNESS + BORDER_GAP) * 2.0f, height - (BORDER_THICKNESS + BORDER_GAP) * 2.0f), glm::vec3(0.0f)},
    mBounds{width, height},
    mValue{defaultValue}
{
    mFill.mRectangle.SetEnabled(mValue);
}

std::vector<OffsetGraphic> CheckBox::GetRenderables()
{
    std::vector<OffsetGraphic> renderables = {};
    constexpr int totalRenderables = 5;
    renderables.reserve(totalRenderables);
    renderables.emplace_back(mFill.mRectangle, mFill.mOffset);
    for (const auto& line : mLines)
    {
        renderables.emplace_back(line.mRectangle, line.mOffset);
    }

    return renderables;
}

BaseComponent* CheckBox::GetBaseComponent()
{
    return this;
}

void CheckBox::Accept(ProcessEventVisitor& visitor)
{
    visitor.Visit(*this);
}

void CheckBox::OnClick()
{
    SetValue(!mValue);
}

void CheckBox::AddValueChangeListener(std::function<void(bool)> callback)
{
    mValueChangeListeners.push_back(callback);
}

void CheckBox::SetValue(bool value)
{
    mValue = value;
    mFill.mRectangle.SetEnabled(mValue);

    for (const auto& callback : mValueChangeListeners)
    {
        callback(mValue);
    }
}

bool CheckBox::GetValue() const
{
    return mValue;
}

RectangleBounds CheckBox::GetBounds() const
{
    return mBounds;
}

} // namespace pong

#include "checkbox.h"

namespace pong
{

constexpr float BORDER_THICKNESS = 10.0f;
constexpr float BORDER_GAP = 10.0f;

CheckBox::CheckBox(float width, float height, bool defaultValue) :
    mLines {
        MeshComponent { width,            BORDER_THICKNESS, glm::vec3(0.0f, height / 2.0f - BORDER_THICKNESS / 2.0f, 0.0f) },
        MeshComponent { width,            BORDER_THICKNESS, glm::vec3(0.0f, height / -2.0f + BORDER_THICKNESS / 2.0f, 0.0f) },
        MeshComponent { BORDER_THICKNESS, height,           glm::vec3(width / -2.0f + BORDER_THICKNESS / 2.0f, 0.0f, 0.0f) },
        MeshComponent { BORDER_THICKNESS, height,           glm::vec3(width / 2.0f - BORDER_THICKNESS / 2.0f, 0.0f, 0.0f) }
    },
    mFill { width - (BORDER_THICKNESS + BORDER_GAP) * 2.0f, height - (BORDER_THICKNESS + BORDER_GAP) * 2.0f},
    mColliderBox{width, height},
    mValue{defaultValue}
{
    mFill.SetEnabled(mValue);
}

void CheckBox::Render() const
{
    for (const auto& line : mLines)
    {
        line.mMesh.Draw(line.mPosition);
    }

    if (mValue)
    {
        mFill.Draw(mPosition);
    }
}

void CheckBox::Accept(ProcessEventVisitor& visitor)
{
    visitor.VisitCheckBox(*this);
}

void CheckBox::SetPosition(const glm::vec3& position)
{
    mPosition = position;

    for (auto& line : mLines)
    {
        line.mPosition = mPosition + line.mOffset;
    }

    mColliderBox.OnPositionUpdate(mPosition);
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
    mFill.SetEnabled(mValue);

    for (const auto& callback : mValueChangeListeners)
    {
        callback(mValue);
    }
}

bool CheckBox::GetValue() const
{
    return mValue;
}

ColliderBox* CheckBox::GetColliderBox()
{
    return &mColliderBox;
}

} // namespace pong

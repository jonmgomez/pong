#include "slider.h"

#include <algorithm>

namespace pong
{

constexpr float BORDER_THICKNESS = 10;
constexpr float BORDER_GAP = 10;
constexpr float HANDLE_WIDTH_PERCENT = 0.9f;
constexpr float HANDLE_HEIGHT_PERCENT = 1.25f;

Slider::Slider(float width, float height, float min, float max, float step, float startValue) :
    mWidth(width),
    mHeight(height),
    mMin(min),
    mMax(max),
    mStep(step),
    mValue(std::clamp(startValue, min, max))
{
    ASSERT(min < max && step > 0.0f);
    const float verticalBorderXPos = width / 2.0f - BORDER_THICKNESS / 2.0f;
    const float horizontalBorderYPos = height / 2.0f - BORDER_THICKNESS / 2.0f;
    const float fillHeight = height - (BORDER_GAP + BORDER_THICKNESS) * 2.0f;
    const float fillWidth = width * (mValue - mMin) / (mMax - mMin) - (BORDER_GAP + BORDER_THICKNESS);
    const float startXPos = BORDER_GAP + BORDER_THICKNESS;
    const float endXPos = width + BORDER_GAP + BORDER_THICKNESS;
    const float fillXPos = fillWidth / -2.0f - (1.0f - mValue / (mMax - mMin) - 0.5f) * (endXPos - startXPos);
    const float handleWidth = height * HANDLE_WIDTH_PERCENT;
    const float handleHeight = height * HANDLE_HEIGHT_PERCENT;
    const float handleXPos = fillWidth - width / 2.0f;

    mBorderMeshes[0] = { Rectangle(BORDER_THICKNESS, height),   glm::vec3(-verticalBorderXPos, 0.0f, 0.0f),   glm::vec3(-verticalBorderXPos, 0.0f, 0.0f)   };
    mBorderMeshes[1] = { Rectangle(BORDER_THICKNESS, height),   glm::vec3(verticalBorderXPos, 0.0f, 0.0f),    glm::vec3(verticalBorderXPos, 0.0f, 0.0f)    };
    mBorderMeshes[2] = { Rectangle(width, BORDER_THICKNESS),    glm::vec3(0.0f, -horizontalBorderYPos, 0.0f), glm::vec3(0.0f, -horizontalBorderYPos, 0.0f) };
    mBorderMeshes[3] = { Rectangle(width, BORDER_THICKNESS),    glm::vec3(0.0f, horizontalBorderYPos, 0.0f),  glm::vec3(0.0f, horizontalBorderYPos, 0.0f)  };

    mFillMesh   = { Rectangle(fillWidth, fillHeight),     glm::vec3(fillXPos, 0.0f, 0.0f),   glm::vec3(fillXPos, 0.0f, 0.0f)   };
    mHandleMesh = { Rectangle(handleWidth, handleHeight), glm::vec3(handleXPos, 0.0f, 0.0f), glm::vec3(handleXPos, 0.0f, 0.0f) };

    mColliderBox = ColliderBox(width, height);
}

void Slider::Render() const
{
    for (const auto& sliderMesh : mBorderMeshes)
    {
        sliderMesh.mMesh.Draw(sliderMesh.mPosition);
    }

    mFillMesh.mMesh.Draw(mFillMesh.mPosition);
    mHandleMesh.mMesh.Draw(mHandleMesh.mPosition);
}

UIElementType Slider::GetType() const
{
    return UIElementType::Slider;
}

void Slider::SetPosition(const glm::vec3& position)
{
    mPosition = position;
    for (auto& sliderMesh : mBorderMeshes)
    {
        sliderMesh.mPosition = mPosition + sliderMesh.mOffset;
    }

    mFillMesh.mPosition = mPosition + mFillMesh.mOffset;
    mHandleMesh.mPosition = mPosition + mHandleMesh.mOffset;
    mColliderBox.OnPositionUpdate(mPosition);
}

void Slider::OnMouseHeld(const glm::vec3& mousePosition)
{
    mWasPressed = true;

    const int steps = static_cast<int>((mMax - mMin) / mStep) + 1;
    const float percentPerStep = 1.0f / (steps - 1);

    const float halfFillWidth = (mWidth - (BORDER_GAP + BORDER_THICKNESS) * 2.0f) / 2.0f;
    const float minX = mPosition.x - halfFillWidth;
    const float maxX = mPosition.x + halfFillWidth;

    const float currentMouseX = std::clamp(mousePosition.x, minX, maxX) - minX;
    const float percentIn = currentMouseX / (maxX - minX);
    const int stepsIn = static_cast<int>(std::roundf(percentIn / percentPerStep));

    float stepPercent = percentPerStep * stepsIn;
    mValue = stepPercent * (mMax - mMin) + mMin;

    const float newFillWidth = stepPercent * (maxX - minX);
    const float newFillOffset = newFillWidth / -2.0f - (1.0f - stepPercent - 0.5f) * (maxX - minX);
    mFillMesh.mOffset.x = newFillOffset;
    mFillMesh.mPosition.x = mPosition.x + mFillMesh.mOffset.x;
    mFillMesh.mMesh.Resize(newFillWidth, mFillMesh.mMesh.GetHeight());

    const float newHandleXOffset = (stepPercent - 0.5f) * (maxX - minX);
    mHandleMesh.mOffset.x = newHandleXOffset;
    mHandleMesh.mPosition.x = mPosition.x + mHandleMesh.mOffset.x;

    for (const auto& listener : mValueChangeListeners)
    {
        listener(mValue);
    }
}

void Slider::OnMouseReleased()
{
    mWasPressed = false;
}

void Slider::AddValueChangeListener(std::function<void(float)> listener)
{
    mValueChangeListeners.push_back(listener);
}

bool Slider::WasPressed() const
{
    return mWasPressed;
}

ColliderBox* Slider::GetColliderBox()
{
    return &mColliderBox;
}

float Slider::GetValue() const
{
    return mValue;
}

} // namespace pong

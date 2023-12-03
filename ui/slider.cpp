#include "slider.h"

#include <algorithm>

namespace pong
{

Slider::Slider(float width, float height, float min, float max, float step, float startValue) :
    mWidth(width),
    mHeight(height),
    mMin(min),
    mMax(max),
    mStep(step),
    mValue(std::clamp(startValue, min, max))
{
    ASSERT(min < max && step > 0.0f);
    const float borderThickness = height * 0.05f;
    const float verticalBorderXPos = width / 2.0f - borderThickness / 2.0f;
    const float horizontalBorderYPos = height / 2.0f - borderThickness / 2.0f;
    const float fillHeight = height * 0.75f;
    const float fillWidth = width * (mValue - mMin) / (mMax - mMin) * 0.9f;
    const float fillXPos = fillWidth / -2.0f;
    const float handleWidth = height * 1.1f;
    const float handleHeight = handleWidth;
    const float handleXPos = fillWidth - width / 2.0f;

    mSliderMeshes[0] = { Rectangle(borderThickness, height),   glm::vec3(-verticalBorderXPos, 0.0f, 0.0f),   glm::vec3(-verticalBorderXPos, 0.0f, 0.0f)   }; // Border
    mSliderMeshes[1] = { Rectangle(borderThickness, height),   glm::vec3(verticalBorderXPos, 0.0f, 0.0f),    glm::vec3(verticalBorderXPos, 0.0f, 0.0f)    }; // Border
    mSliderMeshes[2] = { Rectangle(width, borderThickness),    glm::vec3(0.0f, -horizontalBorderYPos, 0.0f), glm::vec3(0.0f, -horizontalBorderYPos, 0.0f) }; // Border
    mSliderMeshes[3] = { Rectangle(width, borderThickness),    glm::vec3(0.0f, horizontalBorderYPos, 0.0f),  glm::vec3(0.0f, horizontalBorderYPos, 0.0f)  }; // Border
    mSliderMeshes[4] = { Rectangle(fillWidth, fillHeight),     glm::vec3(fillXPos, 0.0f, 0.0f),              glm::vec3(0.0f) }; // Fill
    mSliderMeshes[5] = { Rectangle(handleWidth, handleHeight), glm::vec3(handleXPos, 0.0f, 0.0f),            glm::vec3(0.0f) }; // Handle

    mHandleColliderBox = ColliderBox(width, height);
}

void Slider::Render() const
{
    for (const auto& sliderMesh : mSliderMeshes)
    {
        sliderMesh.mMesh.Draw(sliderMesh.mPosition);
    }
}

UIElementType Slider::GetType() const
{
    return UIElementType::Slider;
}

void Slider::SetPosition(const glm::vec3& position)
{
    mPosition = position;
    for (auto& sliderMesh : mSliderMeshes)
    {
        sliderMesh.mPosition = mPosition + sliderMesh.mOffset;
    }

    mHandleColliderBox.OnPositionUpdate(mSliderMeshes[5].mPosition);
}

void Slider::OnMouseHeld(glm::vec3 mousePosition)
{
    mWasPressed = true;

    const int steps = static_cast<int>((mMax - mMin) / mStep) + 1;
    const float minX = mPosition.x - (mWidth * 0.9f) / 2.0f;
    const float maxX = mPosition.x + (mWidth * 0.9f) / 2.0f;
    const float currentX = mousePosition.x - minX;
    const float stepSize = (maxX - minX) / (steps - 1);
    const float percent = currentX / (maxX - minX);
    const float percentPerStep = 1.0f / (steps - 1);
    const int stepsIn = static_cast<int>(std::roundf(percent / percentPerStep));
    float lastStepPercent = 0;
    float stepPercent = percentPerStep;
    // print out all variables
    std::cout << "mousePosition.x: " << mousePosition.x << ", mousePosition.y: " << mousePosition.y << std::endl;
    std::cout << "mPosition.x: " << mPosition.x << ", mPosition.y: " << mPosition.y << std::endl;
    std::cout << "MinX: " << minX << ", MaxX: " << maxX << ", CurrentX: " << currentX << ", StepSize: " << stepSize << std::endl;
    std::cout << "Percent: " << percent << std::endl;
    while (!(lastStepPercent < percent && percent < stepPercent))
    {
        lastStepPercent = stepPercent;
        stepPercent += percentPerStep;
    }
    // round to nearest step
    float roundedPercent = (percent - lastStepPercent) < (stepPercent - percent) ? lastStepPercent : stepPercent;
    std::cout << "Percent lower: " << lastStepPercent << ", upper: " << stepPercent << std::endl;
    std::cout << "Rounded percent: " << roundedPercent << std::endl;
    const float value = roundedPercent * (mMax - mMin) + mMin;
    std::cout << "Value: " << value << std::endl;
    roundedPercent -= 0.5f;
    const float newHandleXOffset = roundedPercent * (maxX - minX);
    mSliderMeshes[5].mOffset.x = newHandleXOffset;
    mSliderMeshes[5].mPosition.x = mPosition.x + mSliderMeshes[5].mOffset.x;
    //mSliderMeshes[5].mPosition.x = std::clamp(mSliderMeshes[5].mPosition.x, );
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
    return &mHandleColliderBox;
}

float Slider::GetValue() const
{
    return mValue;
}

} // namespace pong

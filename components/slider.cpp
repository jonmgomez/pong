#include "slider.h"

#include "gameobject.h"
#include "transform.h"

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
    Resize(width, height);
}

void Slider::CalculateStart()
{
    const float startXPos = BORDER_GAP + BORDER_THICKNESS;
    const float endXPos = mWidth + startXPos;
    const float fillHeight = mHeight - (BORDER_GAP + BORDER_THICKNESS) * 2.0f;
    const float fillWidth = mWidth * std::fabs(mValue - mMin) / (mMax - mMin) - startXPos;
    const float percentValue = std::fabs(mValue - mMin) / (mMax - mMin);
    const float fillXPos = fillWidth / -2.0f - (1.0f - percentValue - 0.5f) * (endXPos - startXPos);
    const float handleWidth = mHeight * HANDLE_WIDTH_PERCENT;
    const float handleHeight = mHeight * HANDLE_HEIGHT_PERCENT;
    const float handleXPos = fillWidth - mWidth / 2.0f;

    mFill   = { Rectangle(fillWidth,   fillHeight),   glm::vec3(fillXPos, 0.0f, 0.0f)   };
    mHandle = { Rectangle(handleWidth, handleHeight), glm::vec3(handleXPos, 0.0f, 0.0f) };
}

void Slider::SetVariables(float min, float max, float step, float startValue)
{
    ASSERT(min < max && step > 0.0f);
    mMin = min;
    mMax = max;
    mStep = step;
    mValue = std::clamp(startValue, min, max);

    CalculateStart();
}

void Slider::Resize(float width, float height)
{
    mWidth = width;
    mHeight = height;

    const float verticalBorderXPos = width / 2.0f - BORDER_THICKNESS / 2.0f;
    const float horizontalBorderYPos = height / 2.0f - BORDER_THICKNESS / 2.0f;

    mBorders = {
        OffsetRectangle { Rectangle(BORDER_THICKNESS, height),           glm::vec3(-verticalBorderXPos, 0.0f, 0.0f)   },
        OffsetRectangle { Rectangle(BORDER_THICKNESS, height),           glm::vec3(verticalBorderXPos, 0.0f, 0.0f)    },
        OffsetRectangle { Rectangle(width,            BORDER_THICKNESS), glm::vec3(0.0f, -horizontalBorderYPos, 0.0f) },
        OffsetRectangle { Rectangle(width,            BORDER_THICKNESS), glm::vec3(0.0f, horizontalBorderYPos, 0.0f)  }
    };

    CalculateStart();

    mBounds = {width, height};
}

std::vector<OffsetGraphic> Slider::GetRenderables()
{
    std::vector<OffsetGraphic> renderables {};
    constexpr int totalRenderables = 6;
    renderables.reserve(totalRenderables);
    renderables.emplace_back(mFill.mRectangle, mFill.mOffset);
    renderables.emplace_back(mHandle.mRectangle, mHandle.mOffset);
    for (const auto& border : mBorders)
    {
        renderables.emplace_back(border.mRectangle, border.mOffset);
    }

    return renderables;
}

BaseComponent* Slider::GetBaseComponent()
{
    return this;
}

void Slider::OnMouseDown(const glm::vec3& mousePosition)
{
    mWasPressed = true;

    const int steps = static_cast<int>((mMax - mMin) / mStep) + 1;
    const float percentPerStep = 1.0f / (steps - 1);

    const float halfFillWidth = (mWidth - (BORDER_GAP + BORDER_THICKNESS) * 2.0f) / 2.0f;

    glm::vec3 position(0.0f);
    if (GetComponent<Transform>() != nullptr)
    {
        position = GetComponent<Transform>()->mPosition;
    }
    const float minX = position.x - halfFillWidth;
    const float maxX = position.x + halfFillWidth;

    const float currentMouseX = std::clamp(mousePosition.x, minX, maxX) - minX;
    const float percentIn = currentMouseX / (maxX - minX);
    const int stepsIn = static_cast<int>(std::roundf(percentIn / percentPerStep));

    float stepPercent = percentPerStep * stepsIn;
    mValue = stepPercent * (mMax - mMin) + mMin;

    const float newFillWidth = stepPercent * (maxX - minX);
    const float newFillOffset = newFillWidth / -2.0f - (1.0f - stepPercent - 0.5f) * (maxX - minX);
    mFill.mOffset.x = newFillOffset;
    mFill.mRectangle.Resize(newFillWidth, mFill.mRectangle.GetHeight());

    const float newHandleXOffset = (stepPercent - 0.5f) * (maxX - minX);
    mHandle.mOffset.x = newHandleXOffset;

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

RectangleBounds Slider::GetBounds() const
{
    return mBounds;
}

float Slider::GetValue() const
{
    return mValue;
}

} // namespace pong

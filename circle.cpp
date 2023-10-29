#include "circle.h"

#include <glm/glm.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

#include <cmath>
#include <iostream>
#include <numeric>

Circle::Circle(float radius, int sides) :
    mRadius {radius},
    mSides {sides}
{

    const float circumference = 2.0f * mRadius * static_cast<float>(M_PI);
    const float arcLength = circumference / sides;
    const float angle = arcLength / mRadius;

    float currentAngle = 0.0f;
    float normalizedX = 1.0f;
    float normalizedY = 0.0f;

    std::vector<float> positions = {};
    positions.reserve(sides * 4);
    for (int i = 0; i < mSides; i++)
    {
        positions.push_back(normalizedX * mRadius);
        positions.push_back(normalizedY * mRadius);
        positions.push_back(normalizedX);
        positions.push_back(normalizedY);

        currentAngle += angle;
        normalizedX = cos(currentAngle);
        normalizedY = sin(currentAngle);
    }

    std::vector<unsigned int> indicies = {};
    indicies.reserve(sides * 3);

    for (int i = 0; i < sides - 2; i++)
    {
        indicies.push_back(0);
        indicies.push_back(i + 1);
        indicies.push_back(i + 2);
    }

    mVB = std::make_unique<VertexBuffer>(positions.data(), static_cast<unsigned int>(positions.size() * sizeof(float)));
    mIB = std::make_unique<IndexBuffer>(indicies.data(), static_cast<unsigned int>(indicies.size()));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    mVA.AddBuffer(*mVB, layout);

    const unsigned char kColorValue = 255;
    mTexture = std::make_unique<SolidColorTexture>(kColorValue, kColorValue, kColorValue, kColorValue);
}

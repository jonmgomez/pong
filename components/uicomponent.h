#pragma once

#include "colliderbox.h"
#include "graphic.h"
#include "rectangle.h"

#include <glm/glm.hpp>

#include <functional>

namespace pong
{

class UIComponent
{
public:
    virtual ~UIComponent() = default;
    virtual std::vector<OffsetGraphic> GetRenderables() = 0;
    virtual BaseComponent* GetBaseComponent() = 0;

    int GetOrderLayer() const;
    void SetOrderLayer(int orderLayer);

private:
    int mOrderLayer { 0 };
};

} // namespace pong

#pragma once

#include "component.h"
#include "graphic.h"
#include "renderable.h"

#include <memory>

namespace pong
{

class Mesh : public Component<Mesh>, public Renderable
{
public:
    Mesh() = default;
    Mesh(std::unique_ptr<Graphic> graphic);

    void SetGraphic(std::unique_ptr<Graphic> graphic);
    RenderData GetRenderData();

private:
    std::unique_ptr<Graphic> mGraphic { nullptr };

    friend class ComponentDeserializer;
};

} // namespace pong

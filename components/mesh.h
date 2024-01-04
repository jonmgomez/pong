#pragma once

#include "component.h"
#include "graphic.h"

#include <memory>

namespace pong
{

class Mesh : public Component<Mesh>
{
public:
    Mesh() = default;
    Mesh(std::unique_ptr<Graphic> graphic);

    void SetGraphic(std::unique_ptr<Graphic> graphic);
    RenderData GetRenderData();
    void SetEnabled(bool enabled);
    bool IsEnabled() const;

private:
    std::unique_ptr<Graphic> mGraphic { nullptr };
    bool mEnabled { true };

    friend class ComponentDeserializer;
};

} // namespace pong

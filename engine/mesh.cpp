#include "mesh.h"

#include "indexbuffer.h"
#include "renderer.h"
#include "renderutils.h"
#include "texture.h"
#include "vertexarray.h"

#include <glm/glm.hpp>

namespace pong
{

Mesh::Mesh(std::unique_ptr<Graphic> graphic)
    : mGraphic(std::move(graphic))
{
}

RenderData Mesh::GetRenderData()
{
    return mGraphic->GetRenderData();
}

void Mesh::SetEnabled(bool enabled)
{
    mEnabled = enabled;
}

bool Mesh::IsEnabled() const
{
    return mEnabled;
}

} // namespace pong

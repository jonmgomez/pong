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

void Mesh::SetGraphic(std::unique_ptr<Graphic> graphic)
{
    mGraphic = std::move(graphic);
}

RenderData Mesh::GetRenderData()
{
    return mGraphic->GetRenderData();
}

} // namespace pong

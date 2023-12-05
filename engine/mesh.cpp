#include "mesh.h"

#include "indexbuffer.h"
#include "renderer.h"
#include "renderutils.h"
#include "texture.h"
#include "vertexarray.h"

#include <glm/glm.hpp>

namespace pong
{

void Mesh::Draw(const glm::vec3& position) const
{
    if (mEnabled)
    {
        Renderer::Draw(mVA, mIB, position, mTexture, mColor);
    }
}

void Mesh::SetEnabled(bool enabled)
{
    mEnabled = enabled;
}

bool Mesh::IsEnabled() const
{
    return mEnabled;
}

void Mesh::SetColor(const GLRGBAColor& color)
{
    mColor = color;
}

} // namespace pong

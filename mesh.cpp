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
    // This object should always be instantiated by a derived class
    ASSERT(mTexture != nullptr);

    Renderer::Draw(mVA, mIB, position, *mTexture);
}

} // namespace pong

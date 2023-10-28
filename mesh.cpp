#include "mesh.h"

#include "indexbuffer.h"
#include "renderer.h"
#include "renderutils.h"
#include "texture.h"
#include "vertexarray.h"

#include <glm/glm.hpp>

void Mesh::Draw(const glm::vec3& position) const
{
    // These objects should always be instantiated by a derived class
    ASSERT(mVB != nullptr && mIB != nullptr && mTexture != nullptr);

    Renderer::Draw(mVA, *mIB, position, *mTexture);
}
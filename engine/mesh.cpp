#include "mesh.h"

#include "indexbuffer.h"
#include "renderer.h"
#include "renderutils.h"
#include "texture.h"
#include "vertexarray.h"

#include <glm/glm.hpp>

namespace pong
{

Mesh::Mesh(const Mesh& other) :
    mVA {other.mVA},
    mVB {other.mVB},
    mIB {other.mIB},
    mTexture {other.mTexture}
{
}

Mesh& Mesh::operator=(const Mesh& other)
{
    mVA = other.mVA;
    mVB = other.mVB;
    mIB = other.mIB;
    mTexture = other.mTexture;

    return *this;
}

Mesh::Mesh(Mesh&& other) :
    mVA {std::move(other.mVA)},
    mVB {std::move(other.mVB)},
    mIB {std::move(other.mIB)},
    mTexture {std::move(other.mTexture)}
{
}

Mesh& Mesh::operator=(Mesh&& other)
{
    mVA = std::move(other.mVA);
    mVB = std::move(other.mVB);
    mIB = std::move(other.mIB);
    mTexture = std::move(other.mTexture);

    return *this;
}

void Mesh::Draw(const glm::vec3& position) const
{
    Renderer::Draw(mVA, mIB, position, mTexture);
}

} // namespace pong

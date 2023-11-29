#include "uielement.h"

namespace pong
{

void UIElement::Render(const glm::vec3 position) const
{
    mMesh.Draw(position);
}

} // namespace pong

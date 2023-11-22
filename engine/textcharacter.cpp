#include "textcharacter.h"

namespace pong
{

TextCharacter::TextCharacter(const std::vector<unsigned char>& data)
{

    mTexture = std::make_unique<Texture>(data);
}

} // namespace pong

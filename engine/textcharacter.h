#pragma once

#include "mesh.h"

namespace pong
{

class TextCharacter : public Mesh
{
public:
    TextCharacter(const std::vector<unsigned char>& data);
};

} // namespace pong

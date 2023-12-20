#pragma once

#include "gameobject.h"
#include "scene.h"

#include <memory>
#include <vector>

namespace pong
{

class TitleScene : public Scene
{
public:
    void BuildScene() override;
};

class SettingScene : public Scene
{
public:
    void BuildScene() override;
};

class GameScene : public Scene
{
public:
    void BuildScene() override;
};


} // namespace pong

#include "pong.h"

#include "player.h"

void Pong::PongInit()
{
    auto player = std::make_unique<Player>();
    player->OnStart();
    mGameObjects.push_back(std::move(player));
}

void Pong::PongGameLoop()
{
    // loop through mGameObjects and call OnUpdate() on each
    for (auto& gameObject : mGameObjects)
    {
        gameObject->OnUpdate();
        gameObject->Render();
    }
}

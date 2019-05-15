//
// Created by Leon on 15.05.2019.
//

#include "../Headers/EntityBomberman.hpp"
#include "../Headers/Game.hpp"
#include "../Headers/Images.hpp"

EntityBomberman::EntityBomberman() : Entity(new EntityBombermanController)
{
    playerSprite.setTexture(*(TextManager::Get("frontface")));
    playerSprite.setOrigin(-50,0);
}

void EntityBomberman::SetLocation(const sf::Vector2f &loc)
{
    Entity::SetLocation(loc);
    playerSprite.setPosition(loc.x, loc.y);
}

void EntityBomberman::Draw()
{
    Game::Instance().GetWindow().draw(playerSprite);
}

EntityBombermanController::EntityBombermanController() : playerMoveSpeed(200)
{
}

void EntityBombermanController::Update(const float &deltaTime)
{
}
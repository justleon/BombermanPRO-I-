//
// Created by Leon on 15.05.2019.
//

#include "../Headers/EntityBomberman.hpp"
#include "../Headers/Game.hpp"
#include "../Headers/Images.hpp"

EntityBomberman::EntityBomberman() : Entity(new EntityBombermanController)
{
    //anim = GlobalAnimations[0];
    playerSprite.setTexture(*(TextManager::Get("front0")));
    playerSprite.setOrigin(32,64);
    //anim.SetTarget(playerSprite);
    direction = PlayerDir::PlayerDown;
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

void EntityBomberman::SetDirection(PlayerDir dir)
{
    if(direction != dir)
    {
        direction = dir;
        if(direction == PlayerUp)
        {
            playerSprite.setTexture(*(TextManager::Get("back0")));
            playerSprite.setScale(1, 1);
        }
        if(direction == PlayerDown)
        {
            playerSprite.setTexture(*(TextManager::Get("front0")));
            playerSprite.setScale(1, 1);
        }
        if(direction == PlayerLeft)
        {
            playerSprite.setTexture(*(TextManager::Get("side0")));
            playerSprite.setScale(-1, 1);
        }
        if(direction == PlayerRight)
        {
            playerSprite.setTexture(*(TextManager::Get("side0")));
            playerSprite.setScale(1, 1);
        }
    }
}

/*Animation EntityBomberman::GetAnimation() const
{
    return anim;
}*/

EntityBombermanController::EntityBombermanController() : playerMoveSpeed(200)
{
}

void EntityBombermanController::Update(const float &deltaTime)
{
    auto* owner_cast = dynamic_cast<EntityBomberman*>(owner);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        owner->Move(sf::Vector2f(0, -playerMoveSpeed * deltaTime));
        owner_cast->SetDirection(PlayerDir::PlayerUp);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        owner->Move(sf::Vector2f(0, playerMoveSpeed * deltaTime));
        owner_cast->SetDirection(PlayerDir::PlayerDown);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        owner->Move(sf::Vector2f(-playerMoveSpeed * deltaTime, 0));
        owner_cast->SetDirection(PlayerDir::PlayerLeft);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        owner->Move(sf::Vector2f(playerMoveSpeed * deltaTime, 0));
        owner_cast->SetDirection(PlayerDir::PlayerRight);
    }

    //owner_cast->GetAnimation().Update(deltaTime);
}
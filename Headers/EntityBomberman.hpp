//
// Created by Leon on 15.05.2019.
//

#ifndef SFML_ENTITYBOMBERMAN_HPP
#define SFML_ENTITYBOMBERMAN_HPP

#include "Entity.hpp"

enum PlayerDir{
    PlayerUp = 0,
    PlayerDown = 1,
    PlayerLeft = 2,
    PlayerRight = 3
};

class EntityBomberman : public Entity
{
private:
    sf::Sprite playerSprite;
    PlayerDir direction;
public:
    EntityBomberman();

    virtual void SetLocation(const sf::Vector2f& loc) override;
    virtual void Draw() override;

    void SetDirection(PlayerDir dir);

    inline PlayerDir GetDirection() const { return direction; }
};

class EntityBombermanController : public EntityController
{
private:
    float playerMoveSpeed;
public:
    EntityBombermanController();

    virtual void Update(const float& deltaTime) override;
};

#endif //SFML_ENTITYBOMBERMAN_HPP

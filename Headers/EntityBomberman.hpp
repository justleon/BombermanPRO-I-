//
// Created by Leon on 15.05.2019.
//

#ifndef SFML_ENTITYBOMBERMAN_HPP
#define SFML_ENTITYBOMBERMAN_HPP

#include "Entity.hpp"

class EntityBomberman : public Entity
{
private:
    sf::Sprite playerSprite;
public:
    EntityBomberman();

    virtual void SetLocation(const sf::Vector2f& loc) override;
    virtual void Draw() override;
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

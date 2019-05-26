//
// Created by Bartłomiej Binda on 24/05/2019.
//

#ifndef SFML_MAP_H
#define SFML_MAP_H

#include "Entity.hpp"
#include "../Headers/EntityBomberman.hpp"
#include "../Headers/Game.hpp"
#include "../Headers/Images.hpp"

class Bomb : public Entity
{
private:
    sf::Sprite bombsprite;
public:
    explicit Bomb();

    virtual void SetLocation(const sf::Vector2f& loc) override;
    virtual void Draw() override;

};

class BombController : public EntityController
{

public:
    explicit BombController();

    virtual void Update(const float& deltaTime) override;
};


#endif //SFML_MAP_H

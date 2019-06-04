//
// Created by Bartłomiej Binda on 24/05/2019.
//

#ifndef SFML_BOMB_HPP
#define SFML_BOMB_HPP

#include "Entity.hpp"
#include "../Headers/EntityBomberman.hpp"
#include "../Headers/Game.hpp"
#include "../Headers/Images.hpp"

class Bomb : public Entity
{
private:
    sf::Sprite bombsprite;
public:
    Bomb(int rad);
    int radius;

    virtual void SetLocation(const sf::Vector2f& loc) override;
    virtual void Draw() override;
};

class BombController : public EntityController
{
private:
    float explodeTime;

public:
    BombController();

    virtual void Update(const float& deltaTime) override;
};

class Explosion : public Entity
{
private:
    sf::Sprite flamesprite;
public:
    Explosion();

    virtual void SetLocation(const sf::Vector2f& loc) override;
    virtual void Draw() override;

};

class ExplosionController : public EntityController
{
private:
    float flameTime;

public:
    ExplosionController();

    virtual void Update(const float& deltaTime) override;
};

bool isSolid(const sf::Vector2f &);

#endif //SFML_BOMB_HPP

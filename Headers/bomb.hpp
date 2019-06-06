//
// Created by Bartłomiej Binda on 24/05/2019.
//

#ifndef SFML_BOMB_HPP
#define SFML_BOMB_HPP

#include "Entity.hpp"
#include "../Headers/EntityBomberman.hpp"
#include "../Headers/Game.hpp"
#include "../Headers/Images.hpp"

/// Class to create and draw bombs by bomberman character
class Bomb : public Entity
{
private:
    /** Bomb sf::sprite */
    sf::Sprite bombsprite;
public:
    Bomb(int* rad, int* bombs);
    /** the range of bomb's explosion (flames) */
    int* radius;
    /** number of bombs that bomberman has */
    int* numOfBombs;

    virtual void SetLocation(const sf::Vector2f& loc) override;
    virtual void Draw() override;
};

/// BombController. Manages bombs' explosions
class BombController : public EntityController
{
private:
    /** Time after which the bombs explode */
    float explodeTime;

public:
    BombController();
    /** Creates Explosions (draws flames after explosion), but only in right places (not solid) */
    virtual void Update(const float& deltaTime) override;
};

/// Explosion class that manages explosions (removes tiles if needed)
class Explosion : public Entity
{
private:
    /** Bomb sf::sprite */
    sf::Sprite flamesprite;
public:
    Explosion();

    virtual void SetLocation(const sf::Vector2f& loc) override;
    virtual void Draw() override;

};

/// Manages flames
class ExplosionController : public EntityController
{
private:
    /** The time that there are deadly flames on screen */
    float flameTime;

public:
    ExplosionController();
    /** destroys (removes from level) the flame textures when flameTime ends */
    virtual void Update(const float& deltaTime) override;
};

#endif //SFML_BOMB_HPP

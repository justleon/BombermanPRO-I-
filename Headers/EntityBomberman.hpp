//
// Created by Leon on 15.05.2019.
//

#ifndef SFML_ENTITYBOMBERMAN_HPP
#define SFML_ENTITYBOMBERMAN_HPP

#include "Entity.hpp"
#include "../Headers/bomb.hpp"
#include "Animation.hpp"

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
    //Animation anim;
    PlayerDir direction;
public:
    EntityBomberman(bool first);

    virtual void SetLocation(const sf::Vector2f& loc) override;
    virtual void Draw() override;
    bool IsColliding();

    void SetDirection(PlayerDir dir);
    //Animation GetAnimation() const;

    inline PlayerDir GetDirection() const { return direction; }
};

class EntityBombermanController : public EntityController
{
private:
    bool MoveUp(const float& delta, EntityBomberman* owner);
    bool MoveDown(const float& delta, EntityBomberman* owner);
    bool MoveLeft(const float& delta, EntityBomberman* owner);
    bool MoveRight(const float& delta, EntityBomberman* owner);
    void PlantBomb(const float& delta);
    float playerMoveSpeed;
    const float bombPeriod;
    float bombTime;
    int bombRadius;
    bool isFirst;
public:
    EntityBombermanController(bool first);

    inline int* GetRadius() { return &bombRadius; }
    inline float* GetSpeed() { return &playerMoveSpeed; }

    virtual void Update(const float& deltaTime) override;
};

#endif //SFML_ENTITYBOMBERMAN_HPP

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

/// Class to manage bomberman players
class EntityBomberman : public Entity
{
private:
    /** sprite of bomberman */
    sf::Sprite playerSprite;
    //Animation anim;
    /** current direction of bomberman */
    PlayerDir direction;
public:
    /** Creates bomberman (first = true means player one) */
    EntityBomberman(bool first);
    virtual void SetLocation(const sf::Vector2f& loc) override;
    virtual void Draw() override;
    /** Checks (manages) collisions with powerups */
    bool IsColliding();
    /** Sets the direction of the current player. Switches between front/back/left/right sprite texture */
    void SetDirection(PlayerDir dir);
    //Animation GetAnimation() const;

    inline PlayerDir GetDirection() const { return direction; }
};

/// Controller for bomberman players
class EntityBombermanController : public EntityController
{
private:
    bool MoveUp(const float& delta, EntityBomberman* owner);
    bool MoveDown(const float& delta, EntityBomberman* owner);
    bool MoveLeft(const float& delta, EntityBomberman* owner);
    bool MoveRight(const float& delta, EntityBomberman* owner);
    /** Plants the bomb in bomberman's current location tile */
    void PlantBomb(const float& delta);
    /** bobmerman's current speed */
    float playerMoveSpeed;
    /** time between planting new bombs (you can't plant faster than 0.8s) */
    const float bombPeriod;
    /** Number of bombs that bomberman can plant */
    int bombNum;
    /** initially set to bombPeriod when planted. Then when is lower than 0 You can plant again */
    float bombTime;
    /** Radius of bomb (strength) */
    int bombRadius;
    /** If true it means PlayerOne false is playerTwo */
    bool isFirst;
public:
    EntityBombermanController(bool first);

    inline int* GetRadius() { return &bombRadius; }
    inline float* GetSpeed() { return &playerMoveSpeed; }
    inline int* GetBombNum() { return &bombNum; }
    /** Using private methods it manages bombermans' motions */
    virtual void Update(const float& deltaTime) override;
};

#endif //SFML_ENTITYBOMBERMAN_HPP

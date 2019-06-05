//
// Created by pro-w on 02.06.2019.
//

#ifndef SFML_POWERUP_HPP
#define SFML_POWERUP_HPP

#include "block.hpp"
#include "Images.hpp"
#include "Game.hpp"

#define VAL_SPEED 20
#define VAL_BOMB 1

template <typename T>
class PowerUp : public Block
{
private:
    T value;
public:
    explicit PowerUp(BlockType, T);

    inline T GetValue() const { return value; }
};

//Methods
template <typename T>
PowerUp<T>::PowerUp(BlockType putype, T val) : Block(putype), value(val)
{
    if(GetType() == BlockType::PUExp)
        SetSprite("PUExp");
    else if(GetType() == BlockType::PUBomb)
        SetSprite("PUBomb");
    else if(GetType() == BlockType::PUSpeed)
        SetSprite("PUSpeed");
}

#endif //SFML_POWERUP_HPP

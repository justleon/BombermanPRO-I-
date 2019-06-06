//
// Created by Bartłomiej Binda on 21/05/2019.
//

#ifndef SFML_BLOCK_HPP
#define SFML_BLOCK_HPP

#include "Entity.hpp"
#include <string>
#define TILE_SIZE 64

enum BlockType{
    Background = 0,
    Explosive = 1,
    Solid = 2,
    PUExp = 3,
    PUBomb = 4,
    PUSpeed = 5
};

/// Manages all blocks (loading sprites, setting location, drawing)
class Block : public Entity
{
private:
    sf::Sprite bsprite; /** Block sf::sprite */
    BlockType type; /** Type of the block (enum) */
public:
    explicit Block(BlockType);
    ~Block();
    /** Sets location of block in location (loc) */
    virtual void SetLocation(const sf::Vector2f& loc) override;
    /** Gets and sets the block's texture  */
    void SetSprite(std::string whatsprite);
    /** Draws block */
    virtual void Draw() override;

    inline BlockType GetType() const { return type; }
    inline sf::Sprite GetSprite() const { return bsprite; }
};

/// Controller for blocks
class BlockController : public EntityController
{

public:
    explicit BlockController();
    /** Controls time (updates deltaTime) */
    virtual void Update(const float& deltaTime) override;
};


#endif //SFML_BLOCK_HPP

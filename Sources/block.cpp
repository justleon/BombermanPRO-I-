//
// Created by Bartłomiej Binda on 21/05/2019.
//

#include "../Headers/block.hpp"
#include "../Headers/EntityBomberman.hpp"
#include "../Headers/Game.hpp"
#include "../Headers/Images.hpp"

Block::Block(BlockType btype) : Entity(new BlockController), type(btype)
{
    if(type == BlockType::Background)
        bsprite.setTexture(*(TextManager::Get("Background")));
    else if(type == BlockType::Explosive)
        bsprite.setTexture(*(TextManager::Get("ExpBlock")));
    else if(type == BlockType::Solid)
        bsprite.setTexture(*(TextManager::Get("SolidBlock")));
    //bsprite.setScale(40.f/64.f, 40.f/64.f);
}

void Block::SetLocation(const sf::Vector2f &loc)
{
    Entity::SetLocation(loc);
    bsprite.setPosition(loc.x, loc.y);
}

void Block::Draw()
{
    Game::Instance().GetWindow().draw(bsprite);
}

BlockController::BlockController()
{
}

void BlockController::Update(const float &deltaTime) {

}
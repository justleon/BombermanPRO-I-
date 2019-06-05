//
// Created by Bartłomiej Binda on 21/05/2019.
//

#include "../Headers/block.hpp"
#include "../Headers/EntityBomberman.hpp"
#include "../Headers/Game.hpp"
#include "../Headers/Images.hpp"
#include "../Headers/PowerUp.hpp"
#include <ctime>
#include <cstdlib>

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

Block::~Block()
{
    if(BlockType::Explosive == type)
    {
        srand(time(0));
        int chance = (rand() % 100 + 1) + (rand() % 25);
        if(chance > 14 && chance <= 34){
            auto *powerup = new PowerUp<int>(BlockType::PUBomb, VAL_BOMB);
            powerup->SetLocation(sf::Vector2f(this->GetLocation().x+16, this->GetLocation().y+16));
            Game::Instance().GetCurrentLevel()->Add(powerup);
        } else if(chance > 34 && chance <= 64){
            auto *powerup = new PowerUp<int>(BlockType::PUSpeed, VAL_SPEED);
            powerup->SetLocation(sf::Vector2f(this->GetLocation().x+16, this->GetLocation().y+16));
            Game::Instance().GetCurrentLevel()->Add(powerup);
        } else if(chance > 64 && chance <= 84){
            auto *powerup = new PowerUp<int>(BlockType::PUExp, VAL_BOMB);
            powerup->SetLocation(sf::Vector2f(this->GetLocation().x+16, this->GetLocation().y+16));
            Game::Instance().GetCurrentLevel()->Add(powerup);
        }
    }
}

void Block::SetLocation(const sf::Vector2f &loc)
{
    Entity::SetLocation(loc);
    bsprite.setPosition(loc.x, loc.y);
}

void Block::SetSprite(std::string whatsprite)
{
    bsprite.setTexture(*(TextManager::Get(whatsprite)));
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
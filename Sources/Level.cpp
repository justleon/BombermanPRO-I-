//
// Created by Bartłomiej Binda on 21/05/2019.
//

#include "../Headers/Level.hpp"
#include "../Headers/EntityBomberman.hpp"
#include "../Headers/block.hpp"
#include "../Headers/PowerUp.hpp"


Level::Level()
{
}

Level::~Level()
{
    this->Cleanup();
}

bool Level::Add(Entity *unit)
{
    if (unit)
    {
        if (!this->Exists(unit))
        {
            units.push_back(unit);
            return true;
        }
    }
    return false;
}

bool Level::Remove(Entity *unit)
{
    if (unit)
    {
        auto unitIter = std::find(units.begin(), units.end(), unit);
        if (unitIter != units.end())
        {
            units.erase(unitIter);
            return true;
        }
    }
    return false;
}

bool Level::Exists(Entity *unit) const
{
    return std::find(units.begin(), units.end(), unit) != units.end();
}

std::vector<Entity*> Level::GetCollidingTiles()
{
    std::vector<Entity*> tiles;
    for(auto* tile : units)
    {
        auto* block = dynamic_cast<Block*>(tile);
        if(block && block->GetType() != BlockType::Background)
        {
            tiles.push_back(tile);
        }
    }
    return tiles;
}

std::vector<Entity*> Level::GetThreat()
{
    std::vector<Entity*> threats;
    for(auto* fire : units)
    {
        auto* entity = dynamic_cast<Explosion*>(fire);
        if(entity){
            threats.push_back(entity);
        }
    }
    return threats;
}

std::size_t Level::Cleanup()
{
    std::size_t unitsCount = units.size();
    for (auto *unit : units)
        delete unit;
    for(auto* player : players)
        delete player;
    return unitsCount;
}

void Level::Update(const float &deltaTime) {
    for (auto i = 0u; i < units.size(); i++) {
        units[i]->Update(deltaTime);
        if (units[i]->IsDestroyed()){
            delete units[i];
            units.erase(units.begin() + i);
            i--;
        }
    }
    for (auto i = 0u; i < players.size(); i++) {
        players[i]->Update(deltaTime);
        if (players[i]->IsDestroyed()){
            delete players[i];
            players.erase(players.begin() + i);
            i--;
        }
    }
}

void Level::Draw()
{
    for (auto *unit : units)
        unit->Draw();
    for (auto *player : players)
        player->Draw();
}

void setMap(Level *currentLevel){

    std::vector<std::vector<int>> blocks;
    std::ifstream myMapFile;
    myMapFile.open("../Maps/map2.txt");
    while (!myMapFile.eof()) {
        for(int i=0; i<Y_BLOCKS; i++){
            std::vector<int> tmpVec;
            for (int j=0; j<X_BLOCKS; j++){
                int k;
                myMapFile >> k;
                tmpVec.push_back(k);
            }
            blocks.push_back(tmpVec);
        }

    }

    for(auto y=0u; y<Y_BLOCKS; ++y){
        for(auto x=0u; x<X_BLOCKS; ++x){
            auto *block = new Block(BlockType::Background);
            block->SetLocation(sf::Vector2f(x*TILE_SIZE,y*TILE_SIZE));
            currentLevel->Add(block);
        }
    }


    for(auto y=0u; y<Y_BLOCKS; ++y){
        for(auto x=0u; x<X_BLOCKS; ++x){
            int &type = blocks[y][x];
            if(type == BlockType::Explosive){
                auto *block = new Block(BlockType::Explosive);
                block->SetLocation(sf::Vector2f(x*TILE_SIZE,y*TILE_SIZE));
                currentLevel->Add(block);
            }
            if(type == BlockType::Solid){
                auto *block = new Block(BlockType::Solid);
                block->SetLocation(sf::Vector2f(x*TILE_SIZE,y*TILE_SIZE));
                currentLevel->Add(block);
            }
            if(type == BlockType::PUBomb){
                auto *powerup = new PowerUp<int>(BlockType::PUBomb, VAL_BOMB);
                powerup->SetLocation(sf::Vector2f(x*TILE_SIZE+16,y*TILE_SIZE+16));
                currentLevel->Add(powerup);
            }
            if(type == BlockType::PUExp){
                auto *powerup = new PowerUp<int>(BlockType::PUExp, VAL_BOMB);
                powerup->SetLocation(sf::Vector2f(x*TILE_SIZE+16,y*TILE_SIZE+16));
                currentLevel->Add(powerup);
            }
            if(type == BlockType::PUSpeed){
                auto *powerup = new PowerUp<int>(BlockType::PUSpeed, VAL_SPEED);
                powerup->SetLocation(sf::Vector2f(x*TILE_SIZE+16,y*TILE_SIZE+16));
                currentLevel->Add(powerup);
            }
        }
    }
    myMapFile.close();
}
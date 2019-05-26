//
// Created by Bartłomiej Binda on 21/05/2019.
//

#include "../Headers/Level.hpp"
#include "../Headers/block.hpp"


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
        /*	Sprawdzamy czy przypadkiem podany unit
            nie znajduje się już na scenie.
        */
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
        /*	Sprawdzamy czy unit jest na scenie.
            Jeśli tak to go usuwamy.
        */
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

std::size_t Level::Cleanup()
{
    std::size_t unitsCount = units.size();
    for (auto *unit : units)
        delete unit;
    return unitsCount;
}

void Level::Update(const float &deltaTime)
{
    for (auto i = 0u; i<units.size(); i++)
        units[i]->Update(deltaTime);
}

void Level::Draw()
{
    for (auto *unit : units)
        unit->Draw();
}



void setMap(Level *currentLevel){

    std::vector<std::vector<int>> blocks;
    std::ifstream myMapFile;
    myMapFile.open("../Maps/map1.txt");
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

    /*std::vector<std::vector<char> > blocks =
            {
                    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
                    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                    {2,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                    {2,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                    {2,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                    {2,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,2},
                    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2},
                    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,2},
                    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,2},
                    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
                    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
            };*/

    for(auto y=0u; y<Y_BLOCKS; ++y){
        for(auto x=0u; x<X_BLOCKS; ++x){
            auto *block = new Block(BlockType::Background);
            block->SetLocation(sf::Vector2f(x*64,y*64));
            currentLevel->Add(block);
        }
    }


    for(auto y=0u; y<Y_BLOCKS; ++y){
        for(auto x=0u; x<X_BLOCKS; ++x){
            int &type = blocks[y][x];
            if(type == BlockType::Explosive){
                auto *block = new Block(BlockType::Explosive);
                block->SetLocation(sf::Vector2f(x*64,y*64));
                currentLevel->Add(block);
            }
            if(type == BlockType::Solid){
                auto *block = new Block(BlockType::Solid);
                block->SetLocation(sf::Vector2f(x*64,y*64));
                currentLevel->Add(block);
            }
        }
    }
    myMapFile.close();
}
//
// Created by Bartłomiej Binda on 21/05/2019.
//

#include "../Headers/Level.hpp"

Level::Level()
{
}
////////////////////////////////////////////////////////////////
Level::~Level()
{
    this->Cleanup();
}
////////////////////////////////////////////////////////////////
bool Level::Add(Entity *unit)
{
    /* Nie marnujmy czasu gdy podano wskaźnik zerowy. */
    if (unit)
    {
        /*	Sprawdzamy czy przypadkiem podany aktor
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
////////////////////////////////////////////////////////////////
bool Level::Remove(Entity *unit)
{
    /* Nie marnujmy czasu gdy podano wskaźnik zerowy. */
    if (unit)
    {
        /*	Sprawdzamy czy aktor jest na scenie.
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
////////////////////////////////////////////////////////////////
bool Level::Exists(Entity *unit) const
{
    return std::find(units.begin(), units.end(), unit) != units.end();
}
////////////////////////////////////////////////////////////////
std::size_t Level::Cleanup()
{
    /* Usuń wszystkich aktorów (z pamięci, nie tylko z kontenera)*/
    std::size_t unitsCount = units.size();
    for (auto *unit : units)
        delete unit;
    return unitsCount;
}
////////////////////////////////////////////////////////////////
void Level::Update(const float &deltaTime)
{
    /* Wszyscy aktorzy zostają uaktualnieni. */
    for (auto *unit : units)
        unit->Update(deltaTime);
}
////////////////////////////////////////////////////////////////
void Level::Draw()
{
    /* Wyświetlamy każdego aktora. */
    for (auto *unit : units)
        unit->Draw();
}

void setMap(Level *currentLevel){
    std::vector<std::vector<unsigned char> > blocks =
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
            };

    for(auto y=0u; y<Y_BLOCKS; ++y){
        for(auto x=0u; x<X_BLOCKS; ++x){
            auto *block = new Block(BlockType::Background);
            block->SetLocation(sf::Vector2f(x*64,y*64));
            currentLevel->Add(block);
        }
    }


    for(auto y=0u; y<Y_BLOCKS; ++y){
        for(auto x=0u; x<X_BLOCKS; ++x){
            unsigned char &type = blocks[y][x];
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
}
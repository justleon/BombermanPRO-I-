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
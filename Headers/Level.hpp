//
// Created by Bartłomiej Binda on 21/05/2019.
//

#ifndef SFML_LEVEL_H
#define SFML_LEVEL_H

#include <iostream>
#include <fstream>
#include <vector>
#include "../Headers/Entity.hpp"
#include "../Headers/block.hpp"

#define X_BLOCKS 15
#define Y_BLOCKS 11

class Level
{
public:
    typedef std::vector<Entity *> Vunits;

    Level();

    ~Level();

    bool Add(Entity *unit);

    inline void AddPlayer(Entity* player) { players.push_back(player); }

    bool Remove(Entity *unit);

    std::vector <Entity*> GetUnitsAtLocation(const sf::Vector2f &location);

    bool Exists(Entity *unit) const;

    std::vector<Entity*> GetCollidingTiles();
    std::vector<Entity*> GetThreat();

    std::size_t Cleanup();

    void Update(const float &deltaTime);

    void Draw();
    inline std::size_t Count() const { return players.size(); }
private:
    Vunits units;		// Wszystkie obiekty poza graczami
    Vunits players;     // Gracze na scenie
};

void setMap(Level *currentLevel);

#endif //SFML_LEVEL_H

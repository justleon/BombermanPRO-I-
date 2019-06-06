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

/// Our scene. Class for drawing and updating all of the objects.
class Level
{
public:
    /** typedef for our container */
    typedef std::vector<Entity *> Vunits;

    Level();

    ~Level();
    /** Adds unit to our Level  */
    bool Add(Entity *unit);
    /** Adds player to our Level */
    inline void AddPlayer(Entity* player) { players.push_back(player); }
    /** Removes unit from our Level */
    bool Remove(Entity *unit);
    /** Checks whether unit is on Level */
    bool Exists(Entity *unit) const;
    /** Returns a vector with tiles that can collide (Not background) */
    std::vector<Entity*> GetCollidingTiles();
    /** Returns a vector with fire tiles */
    std::vector<Entity*> GetThreat();
    /** Deletes all objects from units */
    std::size_t Cleanup();
    /** Updates all units from Level */
    void Update(const float &deltaTime);
    /** Draws all units from Level */
    void Draw();
    inline std::size_t Count() const { return units.size(); }
private:
    /** Every units (textures) other than players */
    Vunits units;
    /** Players on level */
    Vunits players;
};

void setMap(Level *currentLevel);

#endif //SFML_LEVEL_H

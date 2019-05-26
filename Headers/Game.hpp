//
// Created by Leon on 2019-05-12.
//

#ifndef SFML_GAME_HPP
#define SFML_GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "../Headers/Level.hpp"
#include "../Headers/Images.hpp"
#include "../Headers/EntityBomberman.hpp"

enum Status {
    Init    = 0,
    Running = 1,
    Paused  = 2,
    Exit    = 3
};

class Game {
public:
    ~Game();
    void Run();
    inline sf::RenderWindow& GetWindow() { return window; }
    inline Status GetStatus() const { return game_status; }
    inline Level *GetCurrentLevel() { return currentLevel; }
    inline static Game& Instance(){
        static Game instance;
        return instance;
    }

private:
    Game();
    sf::RenderWindow window;
    Status game_status;
    Level *currentLevel;

};

#endif //SFML_GAME_HPP

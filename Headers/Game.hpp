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

/*! \enum Possible status of the game */
enum Status {
    Init    = 0,
    Running = 1,
    Paused  = 2,
    Exit    = 3
};

/// Class for game instance.
/** Class includes window for game, game status. */
class Game {
public:
    ~Game();
    /** Method that runs the whole game */
    void Run();
    void TitleScreen();
    void GameOver();
    inline sf::RenderWindow& GetWindow() { return window; }
    inline Status GetStatus() const { return game_status; }
    inline Level *GetCurrentLevel() { return currentLevel; }
    /** Game constructor is private because we have only one game. That's why we need game instance to refer to. */
    inline static Game& Instance(){
        static Game instance;
        return instance;
    }

private:
    Game();
    /** Window for our game with resolution of (X_BLOCKS * TILE_SIZE / Y_BLOCKS * TILE_SIZE)*/
    sf::RenderWindow window;
    /** Game status. Status after constructor is Init (Initializing) */
    Status game_status;
    /** Level for all the Textures to add */
    Level *currentLevel;
    /** sf:Font for menu */
    sf::Font font;

};

#endif //SFML_GAME_HPP

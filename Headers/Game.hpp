//
// Created by Leon on 2019-05-12.
//

#ifndef SFML_GAME_HPP
#define SFML_GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

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
    inline static Game& Instance(){
        static Game instance;
        return instance;
    }

private:
    Game();
    sf::RenderWindow window;
    Status game_status;

};

#endif //SFML_GAME_HPP

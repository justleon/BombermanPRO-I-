//
// Created by Leon on 2019-05-12.
//

#ifndef SFML_GAME_HPP
#define SFML_GAME_HPP

#include <SFML/Graphics.hpp>

enum Status
{
    Init    = 0,
    Running = 1,
    Paused  = 2,
    Exit    = 3
};

class Game
{
private:
    Game();
    sf::RenderWindow window;
    Status game_status;

public:
    ~Game();
    void Run();
    inline sf::RenderWindow& GetWindow() { return window; }
    inline Status GetStatus() const { return game_status; }
    inline static Game& Instance(){
        static Game instance;
        return instance;
    }
};

#endif //SFML_GAME_HPP

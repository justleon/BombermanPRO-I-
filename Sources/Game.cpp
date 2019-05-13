//
// Created by Leon on 2019-05-12.
//

#include "../Headers/Game.hpp"
#include "../Headers/Images.hpp"

Game::Game() : window(sf::VideoMode(800, 600), "B O M B E R M A N  P R O i"), game_status(Status::Init)
{
}

Game::~Game()
{
    if(window.isOpen())
    {
        window.close();
    }
}

void Game::Run()
{
    game_status = Status::Running;

    //tlo
    sf::Color bColor(40, 40, 40);

    while(game_status != Status::Exit){
        sf::Event event;

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                game_status = Status::Exit;
        }

        window.clear(bColor);

        window.display();
    }
}
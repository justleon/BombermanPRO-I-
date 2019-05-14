//
// Created by Leon on 2019-05-12.
//

#include <iostream>
#include "../Headers/Game.hpp"
#include "../Headers/Images.hpp"

Game::Game() : window(sf::VideoMode(800, 600), "B O M B E R M A N  P R O i"), game_status(Status::Init)
{
}

Game::~Game() {
    //TextManager::Cleanup();
    if(window.isOpen())
        window.close();
}

void Game::Run() {
    game_status = Status::Running;
    //sf::Texture *image = TextManager::Load("sprite","../Graphics/Sprites/Bomberman/Front/Bman_F_f05.png");
    /*if (!image.loadFromFile("../Graphics/Sprites/Bomberman/Front/Bman_F_f05.png"))
    {
        std::cout << "error loading";
    }*/
    sf::Sprite test_sprite;
    test_sprite.setTexture(*(TextManager::Load("sprite","../Graphics/Sprites/Bomberman/Front/Bman_F_f05.png")));

    //tlo
    sf::Color bColor(40, 40, 40);

    while(game_status != Status::Exit) {
        sf::Event event;

        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                game_status = Status::Exit;
        }

        window.clear(bColor);
        window.draw(test_sprite);
        window.display();
    }
}
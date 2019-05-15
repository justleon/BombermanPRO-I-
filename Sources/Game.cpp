//
// Created by Leon on 2019-05-12.
//

#include <iostream>
#include "../Headers/Game.hpp"
#include "../Headers/Images.hpp"
#include "../Headers/Entity.hpp"
#include "../Headers/EntityBomberman.hpp"

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
    sf::Clock GameClock;
    float DeltaTime = 1/60.f;
    //sf::Texture *image = TextManager::Load("sprite","../Graphics/Sprites/Bomberman/Front/Bman_F_f05.png");
    /*if (!image.loadFromFile("../Graphics/Sprites/Bomberman/Front/Bman_F_f05.png"))
    {
        std::cout << "error loading";
    }*/
    sf::Sprite test_sprite, sprite2;
    // Wywolanie load i zapamietanie tekstury
    TextManager::Load("frontface","../Graphics/Sprites/Bomberman/Front/Bman_F_f00.png");

    auto* bomberman = new EntityBomberman();

    // Sprawdzenie get i zmiana pozycji sprite2
    //sprite2.setTexture(*(TextManager::Get("frontface")));
    //sprite2.setPosition(300,0);
    //tlo
    sf::Color bColor(40, 40, 40);

    while(game_status != Status::Exit) {
        float frameStart = GameClock.getElapsedTime().asSeconds();
        sf::Event event;

        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                game_status = Status::Exit;
        }

        window.clear(bColor);
        // draw sprites (for jak bedzie duzo xdd) ah te commenty
        window.draw(test_sprite);
        window.draw(sprite2);
        bomberman->Draw();
        window.display();
        DeltaTime = GameClock.getElapsedTime().asSeconds() - frameStart;
    }
}
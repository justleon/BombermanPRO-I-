//
// Created by Leon on 2019-05-12.
//

#include <iostream>
#include "../Headers/Game.hpp"
#include "../Headers/Images.hpp"
#include "../Headers/Entity.hpp"
#include "../Headers/EntityBomberman.hpp"

#define TIME_FRAME 1/60.f

Game::Game() : window(sf::VideoMode(800, 600), "B O M B E R M A N  P R O i"), game_status(Status::Init)
{
    TextManager::Load("front", "../Graphics/Sprites/Bomberman/Front/Bman_F_f00.png");
    TextManager::Load("back", "../Graphics/Sprites/Bomberman/Back/Bman_B_f00.png");
    TextManager::Load("side", "../Graphics/Sprites/Bomberman/Side/Bman_F_f00.png");

    TextManager::Load("ExpBlock", "../Graphics/Sprites/Blocks/ExplodableBlock.png");
    TextManager::Load("SolidBlock", "../Graphics/Sprites/Blocks/SolidBlock.png");
    TextManager::Load("background", "../Graphics/Sprites/Blocks/BackgroundTile.png");
}

Game::~Game() {
    TextManager::Cleanup();
    if(window.isOpen())
        window.close();
}

void Game::Run() {
    game_status = Status::Running;
    sf::Clock GameClock;
    float DeltaTime = TIME_FRAME;
    //sf::Texture *image = TextManager::Load("sprite","../Graphics/Sprites/Bomberman/Front/Bman_F_f05.png");
    /*if (!image.loadFromFile("../Graphics/Sprites/Bomberman/Front/Bman_F_f05.png"))
    {
        std::cout << "error loading";
    }*/

    // Wywolanie load i zapamietanie tekstury


    auto* bomberman = new EntityBomberman();

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
        bomberman->Update(DeltaTime);
        // draw sprites (for jak bedzie duzo xdd) ah te commenty
        bomberman->Draw();
        window.display();
        DeltaTime = GameClock.getElapsedTime().asSeconds() - frameStart;
    }
}
//
// Created by Leon on 2019-05-12.
//

#include "../Headers/Game.hpp"
#include "../Headers/Images.hpp"
#include "../Headers/Entity.hpp"
#include "../Headers/EntityBomberman.hpp"
#include "../Headers/block.hpp"
#include "../Headers/Animation.hpp"

#define TIME_FRAME 1/60.f

Game::Game() : window(sf::VideoMode(X_BLOCKS*64, Y_BLOCKS*64), "B O M B E R M A N  P R O i"), game_status(Status::Init), currentLevel(new Level())
{
    TextManager::Load("front0", "../Graphics/Sprites/Bomberman/Front/Bman_F_f00.png");
    TextManager::Load("front1", "../Graphics/Sprites/Bomberman/Front/Bman_F_f01.png");
    TextManager::Load("front2", "../Graphics/Sprites/Bomberman/Front/Bman_F_f02.png");
    TextManager::Load("front3", "../Graphics/Sprites/Bomberman/Front/Bman_F_f03.png");
    TextManager::Load("front4", "../Graphics/Sprites/Bomberman/Front/Bman_F_f04.png");
    TextManager::Load("front5", "../Graphics/Sprites/Bomberman/Front/Bman_F_f05.png");
    TextManager::Load("front6", "../Graphics/Sprites/Bomberman/Front/Bman_F_f06.png");
    TextManager::Load("front7", "../Graphics/Sprites/Bomberman/Front/Bman_F_f07.png");

    TextManager::Load("back0", "../Graphics/Sprites/Bomberman/Back/Bman_B_f00.png");
    TextManager::Load("back1", "../Graphics/Sprites/Bomberman/Back/Bman_B_f01.png");
    TextManager::Load("back2", "../Graphics/Sprites/Bomberman/Back/Bman_B_f02.png");
    TextManager::Load("back3", "../Graphics/Sprites/Bomberman/Back/Bman_B_f03.png");
    TextManager::Load("back4", "../Graphics/Sprites/Bomberman/Back/Bman_B_f04.png");
    TextManager::Load("back5", "../Graphics/Sprites/Bomberman/Back/Bman_B_f05.png");
    TextManager::Load("back6", "../Graphics/Sprites/Bomberman/Back/Bman_B_f06.png");
    TextManager::Load("back7", "../Graphics/Sprites/Bomberman/Back/Bman_B_f07.png");

    TextManager::Load("side0", "../Graphics/Sprites/Bomberman/Side/Bman_F_f00.png");
    TextManager::Load("side1", "../Graphics/Sprites/Bomberman/Side/Bman_F_f01.png");
    TextManager::Load("side2", "../Graphics/Sprites/Bomberman/Side/Bman_F_f02.png");
    TextManager::Load("side3", "../Graphics/Sprites/Bomberman/Side/Bman_F_f03.png");
    TextManager::Load("side4", "../Graphics/Sprites/Bomberman/Side/Bman_F_f04.png");
    TextManager::Load("side5", "../Graphics/Sprites/Bomberman/Side/Bman_F_f05.png");
    TextManager::Load("side6", "../Graphics/Sprites/Bomberman/Side/Bman_F_f06.png");
    TextManager::Load("side7", "../Graphics/Sprites/Bomberman/Side/Bman_F_f07.png");

    TextManager::Load("ExpBlock", "../Graphics/Sprites/Blocks/ExplodableBlock.png");
    TextManager::Load("SolidBlock", "../Graphics/Sprites/Blocks/SolidBlock.png");
    TextManager::Load("Background", "../Graphics/Sprites/Blocks/BackgroundTile.png");

    TextManager::Load("bomb", "../Graphics/Sprites/Bomb/Bomb_f03.png");
    TextManager::Load("flame", "/Users/bindas/Documents2/Projekt/Graphics/Sprites/Flame/Flame_f00.png");
}

Game::~Game() {
    auto textSize = TextManager::Cleanup();
    std::cout << "Number of textures: " << textSize << std::endl;
    if(window.isOpen())
        window.close();
    if(currentLevel)
        delete currentLevel;
}

void Game::Run() {
    game_status = Status::Running;
    sf::Clock GameClock;
    float DeltaTime = TIME_FRAME;

    for(auto y=0u; y<15; ++y){
        for(auto x=0u; x<20; ++x){
            auto *block = new Block(BlockType::Background);
            block->SetLocation(sf::Vector2f(x*40,y*40));
            currentLevel->Add(block);
        }
    }

    // Wywolanie load i zapamietanie tekstury

    setMap(currentLevel);

    auto* bomberman = new EntityBomberman();
    bomberman->SetLocation(sf::Vector2f(85,85));
    currentLevel->Add(bomberman);

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

        currentLevel->Update(DeltaTime);
        currentLevel->Draw();
        bomberman->Draw();

        window.display();
        DeltaTime = GameClock.getElapsedTime().asSeconds() - frameStart;
    }
}
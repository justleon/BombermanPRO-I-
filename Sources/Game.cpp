//
// Created by Leon on 2019-05-12.
//

#include <SFML/Window/Mouse.hpp>
#include <string>
#include "../Headers/Game.hpp"
#include "../Headers/Images.hpp"
#include "../Headers/Entity.hpp"
#include "../Headers/EntityBomberman.hpp"
#include "../Headers/block.hpp"
#include "../Headers/Animation.hpp"

#define TIME_FRAME 1/60.f

Game::Game() : window(sf::VideoMode(X_BLOCKS * TILE_SIZE, Y_BLOCKS * TILE_SIZE), "B O M B E R M A N  P R O i"), game_status(Status::Init), currentLevel(new Level)
{
    TextManager::Load("titlescreen", "../Graphics/Sprites/title_flat.jpg");

    TextManager::Load("front0", "../Graphics/Sprites/Bomberman/Front/Bman_F_f00.png");
    TextManager::Load("back0", "../Graphics/Sprites/Bomberman/Back/Bman_B_f00.png");
    TextManager::Load("side0", "../Graphics/Sprites/Bomberman/Side/Bman_F_f00.png");

    TextManager::Load("ExpBlock", "../Graphics/Sprites/Blocks/ExplodableBlock.png");
    TextManager::Load("SolidBlock", "../Graphics/Sprites/Blocks/SolidBlock.png");
    TextManager::Load("Background", "../Graphics/Sprites/Blocks/BackgroundTile.png");

    TextManager::Load("bomb", "../Graphics/Sprites/Bomb/Bomb_f03.png");
    TextManager::Load("flame", "../Graphics/Sprites/Flame/Flame_f00.png");

    TextManager::Load("PUExp", "../Graphics/Sprites/Powerups/FlamePowerup.png");
    TextManager::Load("PUBomb", "../Graphics/Sprites/Powerups/BombPowerup.png");
    TextManager::Load("PUSpeed", "../Graphics/Sprites/Powerups/SpeedPowerup.png");
}

Game::~Game() {
    if(window.isOpen())
        window.close();
    if(currentLevel)
        delete currentLevel;
}

void Game::TitleScreen()
{
    game_status = Status::Running;
    sf::Font font;
    font.loadFromFile("../Resources/arial-narrow.ttf");
    sf::Sprite mainmenu;
    mainmenu.setTexture(*(TextManager::Get("titlescreen")));
    mainmenu.scale(1.68, 1.25);

    sf::Text menu_text[3];
    std::string str[] = { "Play!", "Credits", "Exit" };
    for(int i = 0; i < 3; ++i){
        menu_text[i].setFont(font);
        menu_text[i].setCharacterSize(45);
        menu_text[i].setPosition((X_BLOCKS*TILE_SIZE/2 - 35), 400 + i*70);
        menu_text[i].setString(str[i]);
    }

    int key = 0, prev_key = 0;
    while(game_status != Status::Exit)
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){
                game_status = Status::Exit;
            }
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Escape)
                    game_status = Status::Exit;

                if(event.key.code == sf::Keyboard::S){
                    prev_key = key;
                    if(key<4) ++key;
                    if(key>=3) key = 0;
                }
                if(event.key.code == sf::Keyboard::W){
                    prev_key = key;
                    if(key >= 0) --key;
                    if(key < 0) key = 2;
                }
                if(event.key.code == sf::Keyboard::Enter){
                    if(key == 0) Run();
                    else if(key == 2)
                        game_status = Status::Exit;
                }
            }
        }

        menu_text[key].setColor(sf::Color(165,211,111));
        menu_text[prev_key].setColor(sf::Color(255,255,255));
        window.clear(sf::Color(40,40,40));
        window.draw(mainmenu);
        for(int i = 0; i < 3; ++i)
            window.draw(menu_text[i]);

        window.display();

    }

}

void Game::Run() {
    sf::Clock GameClock;
    float DeltaTime = TIME_FRAME;

    for(auto y=0u; y<15; ++y){
        for(auto x=0u; x<20; ++x){
            auto *block = new Block(BlockType::Background);
            block->SetLocation(sf::Vector2f(x*TILE_SIZE,y*TILE_SIZE));
            currentLevel->Add(block);
        }
    }

    // Wywolanie load i zapamietanie tekstury

    setMap(currentLevel);

    auto* bomberman = new EntityBomberman(true);
    bomberman->SetLocation(sf::Vector2f(96,96));
    auto* bomberman2 = new EntityBomberman(false);
    bomberman2->SetLocation(sf::Vector2f(865,585));

    currentLevel->AddPlayer(bomberman);
    currentLevel->AddPlayer(bomberman2);

    //tlo
    sf::Color bColor(40, 40, 40);

    while((game_status != Status::Exit) && currentLevel->Count() == 2) {
        float frameStart = GameClock.getElapsedTime().asSeconds();
        sf::Event event;

        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                game_status = Status::Exit;
        }

        window.clear(bColor);

        currentLevel->Update(DeltaTime);
        currentLevel->Draw();

        window.display();
        DeltaTime = GameClock.getElapsedTime().asSeconds() - frameStart;
    }
}
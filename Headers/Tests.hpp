//
// Created by Leon on 08.06.2019.
//

#ifndef SFML_TESTS_HPP
#define SFML_TESTS_HPP

//
// Created by Leon on 08.06.2019.
//

#include "Game.hpp"
#include <iostream>

#define ASSERT(cond) (CheckIfPassed(cond))

void CheckIfPassed(bool cond);

static int passed, failed;

class Tests
{
public:
    static void RunTests()
    {
        passed = 0; failed = 0;
        checkGame();
        checkTextManager();
        checkLevelCreation();
        checkPlayerCreation();
        checkPlayerAdd();
        std::cout << "Tests passed: " << passed << " Tests failed: " << failed << std::endl;
    }
private:
    static void checkGame()
    {
        ASSERT(Game::Instance().GetStatus() == Status::Init);
    }
    static void checkTextManager()
    {
        ASSERT(TextManager::Load("test_sprite", "../Graphics/Sprites/Creep/Front/Creep_F_f00.png"));
        ASSERT(TextManager::Exists("test_sprite"));
        ASSERT(TextManager::Unload("test_sprite"));
    }
    static void checkLevelCreation()
    {
        Level test;
        ASSERT(test.Count() == 0);
    }
    static void checkPlayerCreation()
    {
        EntityBomberman player(true);
        ASSERT(player.GetDirection() == PlayerDir::PlayerDown);
    }
    static void checkPlayerAdd()
    {
        Level test;
        EntityBomberman* testPlayer = new EntityBomberman(true);
        ASSERT(test.AddPlayer(testPlayer));
    }
};

void CheckIfPassed(bool cond) {
    (!cond) ? (failed)++ : (passed)++;
}

#endif //SFML_TESTS_HPP

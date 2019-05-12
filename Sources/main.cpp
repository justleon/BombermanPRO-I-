#include <iostream>
#include "Game.cpp"

int main() {
    auto &game = Game::Instance();
    game.Run();

    return 0;
}
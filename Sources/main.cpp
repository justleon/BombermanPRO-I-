#include <iostream>
#include "../Headers/Game.hpp"

int main() {
    auto &game = Game::Instance();
    game.Run();

    return 0;
}
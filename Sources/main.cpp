#include "../Headers/Game.hpp"

int main() {
    auto &game = Game::Instance();
    game.TitleScreen();

    return 0;
}
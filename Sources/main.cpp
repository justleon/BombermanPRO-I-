#include "../Headers/Game.hpp"

int main() {
    auto &game = Game::Instance();
    try {
        game.TitleScreen();
    } catch(std::string w){
        std::cout << "Exception!:" << w << std::endl;
    }
    return 0;
}
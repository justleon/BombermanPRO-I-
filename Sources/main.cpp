//#include "../Headers/Game.hpp"
#include "../Headers/Tests.hpp"

int main() {
    Tests::RunTests();
    auto &game = Game::Instance();
    try {
        game.TitleScreen();
    } catch(std::string w){
        std::cout << "Exception!:" << w << std::endl;
    }
    return 0;
}
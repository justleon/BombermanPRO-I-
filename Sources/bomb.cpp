//
// Created by Bartłomiej Binda on 26/05/2019.
//

#include "../Headers/bomb.hpp"


Bomb::Bomb() : Entity(new BombController) {
    bombsprite.setTexture(*(TextManager::Get("bomb")));
    bombsprite.setOrigin(-10, -10);
}

void Bomb::SetLocation(const sf::Vector2f &loc) {
    Entity::SetLocation(loc);
    bombsprite.setPosition(loc.x, loc.y);
}

void Bomb::Draw() {
    Game::Instance().GetWindow().draw(bombsprite);

}

BombController::BombController() {

}

void BombController::Update(const float &deltaTime) {

}

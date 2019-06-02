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

BombController::BombController()
    : explodeTime(3.f)
{

}

void BombController::Update(const float &deltaTime) {
    explodeTime -= deltaTime;
    if (explodeTime <= 0){
        owner->Destroy();
        {
            auto *explosion1 = new Explosion();
            explosion1->SetLocation(owner->GetLocation());
            Game::Instance().GetCurrentLevel()->Add(explosion1);
        }
        {
            auto *explosion1 = new Explosion();
            explosion1->SetLocation(owner->GetLocation() + sf::Vector2f(0, 64));
            Game::Instance().GetCurrentLevel()->Add(explosion1);
        }
        {
            auto *explosion1 = new Explosion();
            explosion1->SetLocation(owner->GetLocation() + sf::Vector2f(0, -64));
            Game::Instance().GetCurrentLevel()->Add(explosion1);
        }
        {
            auto *explosion1 = new Explosion();
            explosion1->SetLocation(owner->GetLocation() + sf::Vector2f(64, 0));
            Game::Instance().GetCurrentLevel()->Add(explosion1);
        }
        {
            auto *explosion1 = new Explosion();
            explosion1->SetLocation(owner->GetLocation() + sf::Vector2f(-64, 0));
            Game::Instance().GetCurrentLevel()->Add(explosion1);
        }
    }

}


Explosion::Explosion() : Entity(new ExplosionController) {
    flamesprite.setTexture(*(TextManager::Get("flame")));
    flamesprite.setOrigin(-10, -10);
}

void Explosion::SetLocation(const sf::Vector2f &loc) {
    Entity::SetLocation(loc);
    flamesprite.setPosition(loc.x, loc.y);
}

void Explosion::Draw() {
    Game::Instance().GetWindow().draw(flamesprite);

}

ExplosionController::ExplosionController()
        : flameTime(2.f)
{

}

void ExplosionController::Update(const float &deltaTime) {
    flameTime -= deltaTime;
    if (flameTime <= 0)
        owner->Destroy();
}

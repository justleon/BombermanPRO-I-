//
// Created by Bartłomiej Binda on 26/05/2019.
//

#include "../Headers/bomb.hpp"

void setRadius(sf::Vector2f loc, int rad, int x, int y);

Bomb::Bomb(int rad) : Entity(new BombController) {
    radius = rad;
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
    auto* owner_cast = dynamic_cast<Bomb*>(owner);
    explodeTime -= deltaTime;
    if (explodeTime <= 0){
        owner->Destroy();
        {
            auto *explosion1 = new Explosion();
            auto blockloc = owner->GetLocation();
            explosion1->SetLocation(blockloc);
            if(!isSolid(blockloc))
                Game::Instance().GetCurrentLevel()->Add(explosion1);
        }
        setRadius(owner->GetLocation(), owner_cast->radius, 0, 64);
        setRadius(owner->GetLocation(), owner_cast->radius, 0, -64);
        setRadius(owner->GetLocation(), owner_cast->radius, 64, 0);
        setRadius(owner->GetLocation(), owner_cast->radius, -64, 0);

        /*for(int i = 1; i-1 < owner_cast->radius; ++i){
            auto *explosion1 = new Explosion();
            auto blockloc = owner->GetLocation() + sf::Vector2f(0, 64*i);
            explosion1->SetLocation(blockloc);
            if(!isSolid(blockloc))
                Game::Instance().GetCurrentLevel()->Add(explosion1);
        }*/
    }

}


Explosion::Explosion() : Entity(new ExplosionController) {
    flamesprite.setTexture(*(TextManager::Get("flame")));
    flamesprite.setOrigin(-10, -10);
}

void Explosion::SetLocation(const sf::Vector2f &loc) {
    Entity::SetLocation(loc);
    flamesprite.setPosition(loc.x, loc.y);
    sf::FloatRect collider(sf::Vector2f(loc), sf::Vector2f(35, 25));

    auto tiles = Game::Instance().GetCurrentLevel()->GetCollidingTiles();
    for(auto* tile : tiles)
    {
        auto* block_cast = dynamic_cast<Block*>(tile);
        if(block_cast->GetType() == BlockType::Explosive){
            sf::FloatRect tileCollider(sf::Vector2f(tile->GetLocation().x, tile->GetLocation().y), sf::Vector2f(TILE_SIZE/2, TILE_SIZE/2));
            if(tileCollider.intersects(collider))
                tile->Destroy();
        }
    }

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


bool isSolid(const sf::Vector2f &loc) {
    sf::FloatRect collider(sf::Vector2f(loc), sf::Vector2f(35, 25));
    auto tiles = Game::Instance().GetCurrentLevel()->GetCollidingTiles();
    for(auto* tile : tiles)
    {
        auto* block_cast = dynamic_cast<Block*>(tile);
        if(block_cast->GetType() == BlockType::Solid){
            sf::FloatRect tileCollider(sf::Vector2f(tile->GetLocation().x, tile->GetLocation().y), sf::Vector2f(TILE_SIZE/2, TILE_SIZE/2));
            if(tileCollider.intersects(collider))
                return true;
        }
    }
    return false;
}

void setRadius(sf::Vector2f loc, int rad, int x, int y){
    for(int i = 1; i-1 < rad; ++i){
        auto *explosion1 = new Explosion();
        auto blockloc = loc + sf::Vector2f(x*i, y*i);
        explosion1->SetLocation(blockloc);
        if(!isSolid(blockloc))
            Game::Instance().GetCurrentLevel()->Add(explosion1);
    }
}
//
// Created by Bartłomiej Binda on 26/05/2019.
//

#include "../Headers/bomb.hpp"

BlockType isSolid(const sf::Vector2f &);
void setRadius(sf::Vector2f loc, int rad, int x, int y);

Bomb::Bomb(int* rad, int* bombs) : Entity(new BombController) {
    radius = rad;
    numOfBombs = bombs;
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

BombController::BombController() : explodeTime(3.f)
{
}

void BombController::Update(const float &deltaTime) {
    auto* owner_cast = dynamic_cast<Bomb*>(owner);
    explodeTime -= deltaTime;
    if (explodeTime <= 0){
        (*(owner_cast->numOfBombs))++;
        owner->Destroy();
        {
            auto *explosion1 = new Explosion();
            auto blockloc = owner->GetLocation();
            explosion1->SetLocation(blockloc);
            if(isSolid(blockloc) != BlockType::Solid)
                Game::Instance().GetCurrentLevel()->Add(explosion1);
        }
        setRadius(owner->GetLocation(), *(owner_cast->radius), 0, TILE_SIZE);
        setRadius(owner->GetLocation(), *(owner_cast->radius), 0, -TILE_SIZE);
        setRadius(owner->GetLocation(), *(owner_cast->radius), TILE_SIZE, 0);
        setRadius(owner->GetLocation(), *(owner_cast->radius), -TILE_SIZE, 0);

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


BlockType isSolid(const sf::Vector2f &loc) {
    sf::FloatRect collider(sf::Vector2f(loc), sf::Vector2f(TILE_SIZE, TILE_SIZE));
    auto tiles = Game::Instance().GetCurrentLevel()->GetCollidingTiles();
    for(auto* tile : tiles)
    {
        auto* block_cast = dynamic_cast<Block*>(tile);
        if(block_cast->GetType() == BlockType::Solid){
            sf::FloatRect tileCollider(sf::Vector2f(tile->GetLocation().x, tile->GetLocation().y), sf::Vector2f(TILE_SIZE, TILE_SIZE));
            if(tileCollider.intersects(collider))
                return BlockType::Solid;
        } else if(block_cast->GetType() == BlockType::Explosive){
            sf::FloatRect tileCollider(sf::Vector2f(tile->GetLocation().x, tile->GetLocation().y), sf::Vector2f(TILE_SIZE, TILE_SIZE));
            if(tileCollider.intersects(collider))
                return BlockType::Explosive;
        }
    }
    return BlockType::Background;
}

void setRadius(sf::Vector2f loc, int rad, int x, int y){
    for(int i = 1; i-1 < rad; ++i){
        auto *explosion = new Explosion();
        auto blockloc = loc + sf::Vector2f(x*i, y*i);
        explosion->SetLocation(blockloc);
        if(isSolid(blockloc) == BlockType::Background)
            Game::Instance().GetCurrentLevel()->Add(explosion);
        else if(isSolid(blockloc) == BlockType::Explosive){
            Game::Instance().GetCurrentLevel()->Add(explosion);
            i = rad;
        } else
            i = rad;
    }
}
//
// Created by Leon on 15.05.2019.
//

#include "../Headers/EntityBomberman.hpp"
#include "../Headers/Game.hpp"
#include "../Headers/Images.hpp"
#include "../Headers/block.hpp"
#include "../Headers/PowerUp.hpp"

EntityBomberman::EntityBomberman(bool first) : Entity(new EntityBombermanController(first)), direction(PlayerDir::PlayerDown)
{
    //anim = GlobalAnimations[0];
    playerSprite.setTexture(*(TextManager::Get("front0")));
    playerSprite.setOrigin(32,92);
    //anim.SetTarget(playerSprite);
}

void EntityBomberman::SetLocation(const sf::Vector2f &loc)
{
    Entity::SetLocation(loc);
    playerSprite.setPosition(loc.x, loc.y);
}

void EntityBomberman::Draw()
{
    Game::Instance().GetWindow().draw(playerSprite);
}

bool EntityBomberman::IsColliding()
{
    sf::FloatRect collider(sf::Vector2f(location.x-17.5, location.y+5), sf::Vector2f(35, 25));
    auto* controller_cast = dynamic_cast<EntityBombermanController*>(controller);

    auto tiles = Game::Instance().GetCurrentLevel()->GetCollidingTiles();
    for(auto* tile : tiles)
    {
        auto* block_cast = dynamic_cast<Block*>(tile);
        auto* bomb_cast = dynamic_cast<Bomb*>(tile);
        if((block_cast->GetType() != BlockType::PUExp) && (block_cast->GetType() != BlockType::PUBomb) && (block_cast->GetType() != BlockType::PUSpeed)){
            sf::FloatRect tileCollider(sf::Vector2f(tile->GetLocation().x, tile->GetLocation().y), sf::Vector2f(TILE_SIZE, TILE_SIZE));
            if(tileCollider.intersects(collider))
                return true;
        } else{
            sf::FloatRect tileCollider(sf::Vector2f(tile->GetLocation().x, tile->GetLocation().y), sf::Vector2f(TILE_SIZE/2, TILE_SIZE/2));
            if(tileCollider.intersects(collider)) {
                auto* powerup_cast = dynamic_cast<PowerUp<int>*>(tile);
                if(powerup_cast->GetType() == BlockType::PUSpeed){
                    *(controller_cast->GetSpeed()) += powerup_cast->GetValue();
                } else if(powerup_cast->GetType() == BlockType::PUExp){
                    *(controller_cast->GetRadius()) += powerup_cast->GetValue();
                } else{
                    *(controller_cast->GetBombNum()) += powerup_cast->GetValue();
                }
                tile->Destroy();
            }
        }
    }

    return false;
}

void EntityBomberman::SetDirection(PlayerDir dir)
{
    if(direction != dir)
    {
        direction = dir;
        if(direction == PlayerUp)
        {
            playerSprite.setTexture(*(TextManager::Get("back0")));
            playerSprite.setScale(1, 1);
        }
        if(direction == PlayerDown)
        {
            playerSprite.setTexture(*(TextManager::Get("front0")));
            playerSprite.setScale(1, 1);
        }
        if(direction == PlayerLeft)
        {
            playerSprite.setTexture(*(TextManager::Get("side0")));
            playerSprite.setScale(-1, 1);
        }
        if(direction == PlayerRight)
        {
            playerSprite.setTexture(*(TextManager::Get("side0")));
            playerSprite.setScale(1, 1);
        }
    }
}

EntityBombermanController::EntityBombermanController(bool first) : playerMoveSpeed(200), bombNum(1), bombPeriod(0.8f),
    bombTime(0.8f), bombRadius(1), isFirst(first)
{

}

void EntityBombermanController::Update(const float &deltaTime) {
    auto* owner_cast = dynamic_cast<EntityBomberman*>(owner);
    sf::FloatRect collider(sf::Vector2f(owner->GetLocation().x-17.5, owner->GetLocation().y+5), sf::Vector2f(35, 25));
    bombTime -= deltaTime;
    if(isFirst){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            this->MoveUp(-playerMoveSpeed * deltaTime, owner_cast);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            this->MoveDown(playerMoveSpeed * deltaTime, owner_cast);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            this->MoveLeft(-playerMoveSpeed * deltaTime, owner_cast);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            this->MoveRight(playerMoveSpeed * deltaTime, owner_cast);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (bombTime <= 0) && (bombNum > 0)){
            PlantBomb(deltaTime);
        }
    }
    else{
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            this->MoveUp(-playerMoveSpeed * deltaTime, owner_cast);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            this->MoveDown(playerMoveSpeed * deltaTime, owner_cast);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            this->MoveLeft(-playerMoveSpeed * deltaTime, owner_cast);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            this->MoveRight(playerMoveSpeed * deltaTime, owner_cast);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::B) && (bombTime <= 0) && (bombNum > 0)){
            PlantBomb(deltaTime);
        }
    }

    auto fires = Game::Instance().GetCurrentLevel()->GetThreat();
    for(auto* fire : fires)
    {
        sf::FloatRect tileCollider(sf::Vector2f(fire->GetLocation().x, fire->GetLocation().y), sf::Vector2f(TILE_SIZE, TILE_SIZE));
        if(tileCollider.intersects(collider))
            owner->Destroy();
    }

    //owner_cast->GetAnimation().Update(deltaTime);
}

bool EntityBombermanController::MoveUp(const float& delta, EntityBomberman* owner_cast)
{
    owner->Move(sf::Vector2f(0, delta));
    owner_cast->SetDirection(PlayerDir::PlayerUp);

    if(owner_cast->IsColliding())
        owner->Move(sf::Vector2f(0, -delta));

    return false;
}

bool EntityBombermanController::MoveDown(const float& delta, EntityBomberman* owner_cast)
{
    owner->Move(sf::Vector2f(0, delta));
    owner_cast->SetDirection(PlayerDir::PlayerDown);

    if(owner_cast->IsColliding())
        owner->Move(sf::Vector2f(0, -delta));

    return false;
}

bool EntityBombermanController::MoveLeft(const float& delta, EntityBomberman* owner_cast)
{
    owner->Move(sf::Vector2f(delta, 0));
    owner_cast->SetDirection(PlayerDir::PlayerLeft);

    if(owner_cast->IsColliding())
        owner->Move(sf::Vector2f(-delta, 0));

    return false;
}

bool EntityBombermanController::MoveRight(const float& delta, EntityBomberman* owner_cast)
{
    owner->Move(sf::Vector2f(delta, 0));
    owner_cast->SetDirection(PlayerDir::PlayerRight);

    if(owner_cast->IsColliding())
        owner->Move(sf::Vector2f(-delta, 0));

    return false;
}

void EntityBombermanController::PlantBomb(const float &delta) {
    bombTime = bombPeriod;
    auto *bomb = new Bomb(this->GetRadius(), this->GetBombNum());
    sf::Vector2f loc = owner->GetLocation();
    loc.y += 10;
    loc.x = (int(loc.x) / TILE_SIZE)*TILE_SIZE;
    loc.y = (int(loc.y) / TILE_SIZE)*TILE_SIZE;
    bomb->SetLocation(loc);
    Game::Instance().GetCurrentLevel()->Add(bomb);
    bombNum--;
}

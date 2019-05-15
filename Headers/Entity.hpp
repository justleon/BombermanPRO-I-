#ifndef SFML_ENTITY_HPP
#define SFML_ENTITY_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

class EntityController;

class Entity
{
private:

protected:
    EntityController* controller;
    sf::Texture texture;
    sf::Vector2f location;
    float rotation;
public:
    Entity(EntityController* controller);
    virtual ~Entity();

    inline virtual void SetLocation(const sf::Vector2f& loc)
    { location = loc; }
    inline virtual void SetRotation(const float& rot)
    { rotation = rot; }
    inline void Move(const sf::Vector2f& delta)
    { this->SetLocation(location + delta); }
    inline void Rotate(const float& delta)
    { this->SetRotation(rotation + delta); }
    virtual void Draw() = 0;

    inline sf::Vector2f GetLocation() const
    { return location; }
    inline float GetRotation() const
    { return rotation; }

    void ResetController(EntityController* controller);
    virtual void Update(const float &deltaTime);
};

class EntityController
{
private:
    bool Control(Entity* owner);
protected:
    Entity* owner;
public:
    EntityController();
    virtual ~EntityController();
    virtual void Update(const float& deltaTime) = 0;
    inline bool IsControlled() const { return owner != nullptr;}

    friend class Entity;
};

#endif
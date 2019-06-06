#ifndef SFML_ENTITY_HPP
#define SFML_ENTITY_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

class EntityController;

/// Abstact class used to create units on Level
class Entity
{
private:

protected:
    /** controller for the unit (manages operations) */
    EntityController* controller;
    /** texture of the unit */
    sf::Texture texture;
    /** location of the unit */
    sf::Vector2f location;
    /** rotation of the unit */
    float rotation;
    /** By default false. If true then the unit is destroyed. */
    bool destroyed;
public:
    /** constructor of Entity. By default sets controller to nullptr (if not used). Sets destroyed to false  */
    Entity(EntityController* controller);
    virtual ~Entity();

    inline virtual void SetLocation(const sf::Vector2f& loc)
    { location = loc; }
    inline virtual void SetRotation(const float& rot)
    { rotation = rot; }
    /** Moves our unit  */
    inline void Move(const sf::Vector2f &delta)
    { this->SetLocation(location + delta); }
    /** Rotates our unit */
    inline void Rotate(const float& delta)
    { this->SetRotation(rotation + delta); }
    /** Sets destroyed to true */
    void Destroy()
    {destroyed = true;}
    /** Base virtual method to draw objects (units) */
    virtual void Draw() = 0;

    inline sf::Vector2f GetLocation() const
    { return location; }
    inline float GetRotation() const
    { return rotation; }
    inline bool IsDestroyed() const
    {return destroyed;}
    /** Resets the controller */
    void ResetController(EntityController* controller);
    /** virtual method to update units */
    virtual void Update(const float &deltaTime);
};

/// Abstract class for all the controllers for other classes
class EntityController
{
private:
    /** returns True if changed the owner (protected) to owner */
    bool Control(Entity* owner);
protected:
    /** Unit to be controlled */
    Entity* owner;
public:
    EntityController();
    virtual ~EntityController();
    /** virtual method for inherited classes (controllers) */
    virtual void Update(const float& deltaTime) = 0;
    inline bool IsControlled() const { return owner != nullptr;}
    /** friend class */
    friend class Entity;
};

#endif
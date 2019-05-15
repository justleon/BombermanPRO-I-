//
// Created by pro-w on 14.05.2019.
//

#include "../Headers/Entity.hpp"

Entity::Entity(EntityController *control) : controller(nullptr), rotation(0)
{
    if(control && control->Control(this))
    {
        controller = control;
    }
}

Entity::~Entity()
{
    if(controller)
        delete controller;
}

void Entity::ResetController(EntityController *control)
{
    if(control != controller)
    {
        if(control)
            delete control;
        if(control && control->Control(this))
            controller = control;
        else
            controller = nullptr;
    }
}

void Entity::Update(const float &deltaTime)
{
    if(controller)
        controller->Update(deltaTime);
}

//EntityController definitions
EntityController::EntityController() : owner(nullptr)
{
}

EntityController::~EntityController()
{
}

bool EntityController::Control(Entity *own)
{
    if(!owner)
    {
        owner = own;
        return true;
    }
    return false;
}
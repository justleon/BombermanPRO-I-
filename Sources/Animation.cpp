//
// Created by pro-w on 23.05.2019.
//

#include "../Headers/Animation.hpp"
#include "../Headers/Images.hpp"

Animation::Animation() : totalProgress(0.0)
{
}

Animation::Animation(sf::Sprite &target)
{
    this->target = &target;
    totalProgress = 0.0;
}

void Animation::SetTarget(sf::Sprite &target)
{
    this->target = &target;
}

void Animation::addFrame(Frame&& frame)
{
    frames.push_back(std::move(frame));
    totalLength += frame.duration;
}

void Animation::Update(const float &deltaTime)
{
    totalProgress += deltaTime;
    float progress = totalProgress;
    for(auto frame : frames){
        progress -= frame.duration;

        if(progress <= 0.0 || &frame == &frames.back())
        {
            target->setTexture(frame.sprite);
            break;
        }
    }
}

void Animation::SetUpAnimations()
{
    Animation walkDown, walkUp, walkSide;
    walkDown.addFrame({*(TextManager::Get("front0")), 0.1});
    walkDown.addFrame({*(TextManager::Get("front1")), 0.1});
    walkDown.addFrame({*(TextManager::Get("front2")), 0.1});
    walkDown.addFrame({*(TextManager::Get("front3")), 0.1});
    walkDown.addFrame({*(TextManager::Get("front4")), 0.1});
    walkDown.addFrame({*(TextManager::Get("front5")), 0.1});
    walkDown.addFrame({*(TextManager::Get("front6")), 0.1});
    walkDown.addFrame({*(TextManager::Get("front7")), 0.1});
    GlobalAnimations.push_back(walkDown);
}
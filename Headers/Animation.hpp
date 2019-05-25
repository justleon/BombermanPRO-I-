//
// Created by Leon on 23.05.2019.
//

#ifndef SFML_ANIMATION_HPP
#define SFML_ANIMATION_HPP

#include <vector>
#include <SFML/Graphics.hpp>

struct Frame
{
    sf::Texture sprite;
    float duration;
};

class Animation
{
private:
    std::vector<Frame> frames;
    float totalLength;
    float totalProgress;
    sf::Sprite* target;
public:
    Animation();
    Animation(sf::Sprite& target);

    void SetTarget(sf::Sprite& target);
    void addFrame(Frame&& frame);
    void Update(const float& deltaTime);

    static void SetUpAnimations();
};
static std::vector<Animation> GlobalAnimations;

#endif //SFML_ANIMATION_HPP

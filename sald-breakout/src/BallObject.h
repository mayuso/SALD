#pragma once
#include "sald.h"

#include "GameObject.h"

class BallObject : public GameObject
{
public:
    // ball state
    float Radius;
    bool Stuck;
    // constructor(s)
    BallObject();
    BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Sald::Texture* sprite);
    // moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
    glm::vec2 Move(Sald::Timestep timestep, unsigned int window_width);
    // resets the ball to original state with given position and velocity
    void Reset(glm::vec2 position, glm::vec2 velocity);
};

#pragma once
#include "sald.h"

// TODO: Extend from Sald class object and add all relevant variables there
// making sure it works both for 3D and 2D
class GameObject : public Sald::Entity
{
public:
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, Sald::Texture* sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    ~GameObject();
    // object state
    glm::vec2 Position, Size, Velocity;
    glm::vec3 Color;
    float Rotation;
    bool IsSolid;
    bool Destroyed;
    // render state
    Sald::Texture* m_Texture;

    // draw sprite
    virtual void Draw(Sald::SpriteRenderer *renderer);
};
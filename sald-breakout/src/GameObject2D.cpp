#include "GameObject2D.h"


GameObject2D::GameObject2D()
    : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), m_Texture(), IsSolid(false), Destroyed(false) { }

GameObject2D::GameObject2D(glm::vec2 pos, glm::vec2 size, Sald::Texture* texture, glm::vec3 color, glm::vec2 velocity)
    : Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), m_Texture(texture), IsSolid(false), Destroyed(false) { }


GameObject2D::~GameObject2D()
{
}

void GameObject2D::Draw(Sald::Sprite &renderer)
{
    renderer.Draw(this->m_Texture, this->Position, this->Size, this->Rotation, this->Color);
}
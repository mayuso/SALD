#pragma once
#include "Sald/Core/Timestep.h"
#include "sald.h"

class Sandbox2DLayer : public Sald::Layer
{
public:
    Sandbox2DLayer();
    ~Sandbox2DLayer();

    void OnUpdate(Sald::Timestep timestep) override;
    void OnEvent(Sald::Event &event) override;

private:
    void CreateTriangle();
    void CreateShaders();

    // Window dimensions
    //const float toRadians = 3.14159265f / 180.0f;

    GLuint VBO, VAO, IBO, shader, uniformModel;

    bool direction = true;
    float triOffset = 0.0f;
    float triMaxOffset = 0.7f;
    float triIncrement = 0.0005f;

    float curAngle = 0.0f;

    bool sizeDirection = true;
    float curSize = 0.4f;
    float maxSize = 0.8f;
    float minSize = 0.1f;

    //std::vector<Sald::Mesh *> meshList;

    Sald::SpriteRenderer *m_SpriteRenderer;
};
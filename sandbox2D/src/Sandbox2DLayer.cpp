#include "Sandbox2DLayer.h"
#include "sald.h"

Sandbox2DLayer::Sandbox2DLayer()
    : Layer(" Sandbox2DLayer ")
{
    Sald::ShaderManager::NewShader("sprite", "Shaders/sprite.vert", "Shaders/sprite.frag");
    Sald::ShaderManager::NewShader("shader_old", "Shaders/shader_old.vert", "Shaders/shader_old.frag");
    Sald::TextureManager::NewTexture("triangle", "Textures/triangle.png");
    m_SpriteRenderer = new Sald::SpriteRenderer(Sald::ShaderManager::GetShader("sprite"));
    // CreateTriangle();
}

void Sandbox2DLayer::CreateTriangle()
{
    /*unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2};

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f};

    Sald::Mesh *obj1 = new Sald::Mesh(vertices, indices, 12, 12, false);
    meshList.push_back(obj1);*/
}

void Sandbox2DLayer::OnUpdate(GLfloat deltaTime)
{
    Sald::RenderCommand::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    Sald::RenderCommand::Clear();

    if (direction)
    {
        triOffset += triIncrement;
    }
    else
    {
        triOffset -= triIncrement;
    }

    if (abs(triOffset) >= triMaxOffset)
    {
        direction = !direction;
    }

    curAngle += 1.0f;
    if (curAngle >= 360)
    {
        curAngle -= 360;
    }

    if (direction)
    {
        curSize += 0.0001f;
    }
    else
    {
        curSize -= 0.0001f;
    }

    if (curSize >= maxSize || curSize <= minSize)
    {
        sizeDirection = !sizeDirection;
    }

    m_SpriteRenderer->Draw(Sald::TextureManager::GetTexture("triangle"), glm::vec2(0.0f, 0.0f), glm::vec2(0.5f, 0.5f), curAngle);
}

void Sandbox2DLayer::OnEvent(Sald::Event &event)
{
    // SALD_LOG("ExampleLayer :: OnUpdate - DeltaTime: {0}", event);
}

Sandbox2DLayer::~Sandbox2DLayer()
{
}
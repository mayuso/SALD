#include "Sandbox2DLayer.h"
#include "sald.h"

Sandbox2DLayer::Sandbox2DLayer()
    : Layer(" Sandbox2DLayer ")
{
    CreateTriangle();
    CreateShaders();
}

void Sandbox2DLayer::CreateTriangle()
{
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2};

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f};

    Sald::Mesh *obj1 = new Sald::Mesh();
    obj1->CreateMesh(vertices, indices, 12, 12, false);
    meshList.push_back(obj1);
}

void Sandbox2DLayer::CreateShaders()
{
    Sald::ShaderManager::NewShader(Sald::ShaderManager::COLOR, vShader, fShader);
}

void Sandbox2DLayer::OnUpdate(GLfloat deltaTime)
{
    Sald::Renderer2D::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    Sald::Renderer2D::Clear();

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

    curAngle += 0.01f;
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

    Sald::ShaderManager::GetShader(Sald::ShaderManager::COLOR)->Bind();

    meshList[0]->RenderMesh();

    glm::mat4 model(1.0f);
    model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

    Sald::ShaderManager::GetShader(Sald::ShaderManager::COLOR)->SetMat4("model", model);
}

void Sandbox2DLayer::OnEvent(Sald::Event &event)
{
    SALD_LOG("ExampleLayer :: OnUpdate - DeltaTime: {0}", event);
}

Sandbox2DLayer::~Sandbox2DLayer()
{
}
#include "Sandbox2DApp.h"

Sandbox2DApp::Sandbox2DApp() : Sald::Application(800, 600)
{
    m_MainWindow->SetCursorEnabled(false);
    m_MainWindow->SetVSync(true);
    CreateTriangle();
    CreateShaders();
}

Sandbox2DApp::~Sandbox2DApp()
{
}

void Sandbox2DApp::CreateTriangle()
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

void Sandbox2DApp::CreateShaders()
{
    Sald::Shader *shader1 = new Sald::Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);
}

void Sandbox2DApp::Run()
{
    // Loop until window closed
    while (!m_MainWindow->GetShouldClose())
    {
        // Get + Handle user input events
        m_MainWindow->PollEvents();

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

        Sald::Renderer2D::SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        Sald::Renderer2D::Clear();

        shaderList[0].Bind();

        meshList[0]->RenderMesh();

        glm::mat4 model(1.0f);
        model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

        shaderList[0].SetMat4("model", model);

        m_MainWindow->SwapBuffers();
        m_MainWindow->ShowFPS();
    }
}

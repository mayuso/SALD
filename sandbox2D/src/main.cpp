#include "Window.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Shader.h"

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Window dimensions
const float toRadians = 3.14159265f / 180.0f;

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

std::unique_ptr<Sald::Window> mainWindow;
std::vector<Sald::Mesh *> meshList;
std::vector<Sald::Shader> shaderList;

// Vertex Shader
static const char *vShader = "Shaders/shader.vert";

// Fragment Shader
static const char *fShader = "Shaders/shader.frag";

void CreateTriangle()
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

void CreateShaders()
{
    Sald::Shader *shader1 = new Sald::Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);
}

int main()
{
    mainWindow = std::make_unique<Sald::Window>(800, 600);
    mainWindow->Initialize();

    CreateTriangle();
    CreateShaders();

    // Loop until window closed
    while (!mainWindow->GetShouldClose())
    {
        // Get + Handle user input events
        mainWindow->PollEvents();

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

        Sald::Renderer::SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        Sald::Renderer::Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderList[0].Bind();

        meshList[0]->RenderMesh();

        glm::mat4 model(1.0f);
        model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

        shaderList[0].SetMat4("model", model);

        mainWindow->SwapBuffers();
        mainWindow->ShowFPS();
    }

    return 0;
}
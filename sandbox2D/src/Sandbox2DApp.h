#pragma once
#include "Sald/sald_api.h"

#include "Sald/Application.h"
#include "Sald/Renderer2D.h"
#include "Sald/Mesh.h"
#include "Sald/Shader.h"

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Sandbox2DApp : public Sald::Application
{
public:
    Sandbox2DApp();
    Sandbox2DApp(GLint windowWidth, GLint windowHeight);
    ~Sandbox2DApp();

private:
    void CreateTriangle();
    void CreateShaders();

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

    std::vector<Sald::Mesh *> meshList;
    std::vector<Sald::Shader> shaderList;

    // Vertex Shader
    const char *vShader = "Shaders/shader.vert";

    // Fragment Shader
    const char *fShader = "Shaders/shader.frag";
};
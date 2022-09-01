#pragma once
#include "Sald/Core.h"

#include "Sald/Application.h"
#include "Sald/Mesh.h"
#include "Sald/Shader.h"
#include "Sald/Camera.h"
#include "Sald/Texture.h"
#include "Sald/DirectionalLight.h"
#include "Sald/PointLight.h"
#include "Sald/SpotLight.h"
#include "Sald/Material.h"
#include "Sald/Model.h"
#include "Sald/Skybox.h"
#include "Sald/TimeManager.h"
#include "Sald/Renderer3D.h"

#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <memory>

class SandboxApp : public Sald::Application
{
public:
    SandboxApp();
    SandboxApp(GLint windowWidth, GLint windowHeight);
    ~SandboxApp();

private:
    void CalcAverageNormals(unsigned int *indices, unsigned int indiceCount, GLfloat *vertices, unsigned int verticeCount,
                            unsigned int vLength, unsigned int normalOffset);
    void CreateObjects();
    void CreateShaders();
    void RenderScene(Sald::Shader &currentShader);
    void DirectionalShadowMapPass(Sald::DirectionalLight *light);
    void OmniShadowMapPass(Sald::PointLight *light);
    void RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
    void LightningPass();

    Sald::Camera camera;

    std::vector<Sald::Mesh *> meshList;
    std::vector<Sald::Shader> shaderList;
    Sald::Shader directionalShadowShader;
    Sald::Shader omniShadowShader;

    Sald::Material shinyMaterial;
    Sald::Material dullMaterial;

    Sald::Texture brickTexture, dirtTexture, plainTexture;

    Sald::Model blackhawk, xwing;

    Sald::DirectionalLight directionalLight;
    Sald::PointLight pointLights[MAX_POINT_LIGHTS];
    Sald::SpotLight spotLights[MAX_SPOT_LIGHTS];

    Sald::Skybox skybox;

    unsigned int pointLightCount = 0;
    unsigned int spotLightCount = 0;

    GLfloat blackhawkAngle = 0.0f;

    // Vertex Shader
    const char *vShader = "Shaders/shader.vert";

    // Fragment Shader
    const char *fShader = "Shaders/shader.frag";
};
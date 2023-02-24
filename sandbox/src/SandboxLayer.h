#pragma once
#include "sald.h"

#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <memory>

class SandboxLayer : public Sald::Layer
{
public:
    SandboxLayer();
    ~SandboxLayer();

    void OnUpdate(GLfloat deltaTime) override;
    void OnEvent(Sald::Event &event) override;

private:
    void CalcAverageNormals(unsigned int *indices, unsigned int indiceCount, GLfloat *vertices, unsigned int verticeCount,
                            unsigned int vLength, unsigned int normalOffset);
    void CreateObjects();
    void CreateShaders();
    void RenderScene(Sald::Shader *currentShader);
    void DirectionalShadowMapPass(Sald::DirectionalLight *light);
    void OmniShadowMapPass(Sald::PointLight *light);
    void RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
    void LightningPass();

    Sald::Camera m_Camera;

    std::vector<Sald::Mesh *> meshList;

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

    glm::mat4 m_Projection;
};
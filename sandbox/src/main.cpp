#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Renderer.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
#include "Model.h"
#include "Skybox.h"
#include "TimeManager.h"

#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <memory>

Sald::Camera camera;

std::unique_ptr<Sald::Window> mainWindow;
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

GLfloat deltaTime = 0.0f, lastTime = 0.0f;

GLfloat blackhawkAngle = 0.0f;

// Vertex Shader
static const char *vShader = "Shaders/shader.vert";

// Fragment Shader
static const char *fShader = "Shaders/shader.frag";

void calcAverageNormals(unsigned int *indices, unsigned int indiceCount, GLfloat *vertices, unsigned int verticeCount,
                        unsigned int vLength, unsigned int normalOffset)
{
    for (size_t i = 0; i < indiceCount; i += 3)
    {
        unsigned int in0 = indices[i] * vLength;
        unsigned int in1 = indices[i + 1] * vLength;
        unsigned int in2 = indices[i + 2] * vLength;
        glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
        glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
        glm::vec3 normal = glm::cross(v1, v2);
        normal = glm::normalize(normal);

        in0 += normalOffset;
        in1 += normalOffset;
        in2 += normalOffset;

        vertices[in0] += normal.x;
        vertices[in0 + 1] += normal.y;
        vertices[in0 + 2] += normal.z;

        vertices[in1] += normal.x;
        vertices[in1 + 1] += normal.y;
        vertices[in1 + 2] += normal.z;

        vertices[in2] += normal.x;
        vertices[in2 + 1] += normal.y;
        vertices[in2 + 2] += normal.z;
    }
    for (size_t i = 0; i < verticeCount / vLength; i++)
    {
        unsigned int nOffset = i * vLength + normalOffset;
        glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
        vec = glm::normalize(vec);
        vertices[nOffset] = vec.x;
        vertices[nOffset + 1] = vec.y;
        vertices[nOffset + 2] = vec.z;
    }
}

void CreateObjects()
{
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2};

    GLfloat vertices[] = {
        // x		 y	   z	 u	   v     nx    ny    nz
        -1.0f, -1.0f, -0.6f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, -0.6f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f};

    unsigned int floorIndices[] = {
        0, 2, 1,
        1, 2, 3};

    GLfloat floorVertices[] = {
        -10.0f, 0.0f, -10.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        10.0f, 0.0f, -10.0f, 10.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        -10.0f, 0.0f, 10.0f, 0.0f, 10.0f, 0.0f, -1.0f, 0.0f,
        10.0f, 0.0f, 10.0f, 10.0f, 10.0f, 0.0f, -1.0f, 0.0f};

    calcAverageNormals(indices, 12, vertices, 32, 8, 5);

    Sald::Mesh *obj1 = new Sald::Mesh();
    obj1->CreateMesh(vertices, indices, 32, 12, true);
    meshList.push_back(obj1);

    Sald::Mesh *obj2 = new Sald::Mesh();
    obj2->CreateMesh(vertices, indices, 32, 12, true);
    meshList.push_back(obj2);

    Sald::Mesh *obj3 = new Sald::Mesh();
    obj3->CreateMesh(floorVertices, floorIndices, 32, 6, true);
    meshList.push_back(obj3);
}

void CreateShaders()
{
    Sald::Shader *shader1 = new Sald::Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);

    directionalShadowShader.CreateFromFiles("Shaders/directional_shadow_map.vert", "Shaders/directional_shadow_map.frag");
    omniShadowShader.CreateFromFiles("Shaders/omni_directional_shadow_map.vert", "Shaders/omni_directional_shadow_map.geom", "Shaders/omni_directional_shadow_map.frag");
}

// TODO [MAR]: Shader Manager
/*
So there are two ways to fix this:

1. Remove the ClearShader(); call from the Shader class destructor.
2. Always pass the shader by reference.

I prefer option #1. As I said, my destructor really shouldn't have had that code to begin with, that was a result of me rushing a little too much while writing up this lesson.
If you do this though, you should make sure to call the "ClearShader" functions manually when your application closes. Preferably create a "shader manager" class to handle all this for you.
But for now, to just get the code working, removing "ClearShader" from the destructor should be enough.

Anyway, hopefully one of those two options will fix it!
*/

// Pass by reference because if not, the local currentShader gets detroyed, and the Sald::Shader destructor runs glDeleteProgram(m_RendererID);
// which deletes the Shader program from the GPU.
void RenderScene(Sald::Shader &currentShader)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
    // model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
    currentShader.SetMat4("model", model);
    brickTexture.UseTexture();
    shinyMaterial.UseMaterial(&(currentShader));
    meshList[0]->RenderMesh();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-4.0f, 1.0f, -4.0f));
    // model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
    currentShader.SetMat4("model", model);
    dirtTexture.UseTexture();
    dullMaterial.UseMaterial(&(currentShader));
    meshList[1]->RenderMesh();

    blackhawkAngle += 0.1f;
    if (blackhawkAngle > 360.0f)
    {
        blackhawkAngle = 0.1f;
    }

    model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-blackhawkAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(-8.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(-20.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
    currentShader.SetMat4("model", model);
    shinyMaterial.UseMaterial(&(currentShader));
    blackhawk.RenderModel();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-7.0f, 1.0f, 10.0f));
    model = glm::scale(model, glm::vec3(0.006f, 0.006f, 0.006f));
    currentShader.SetMat4("model", model);
    shinyMaterial.UseMaterial(&(currentShader));
    xwing.RenderModel();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
    // model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
    currentShader.SetMat4("model", model);
    dirtTexture.UseTexture();
    shinyMaterial.UseMaterial(&(currentShader));
    meshList[2]->RenderMesh();
}

void DirectionalShadowMapPass(Sald::DirectionalLight *light)
{

    directionalShadowShader.Bind();
    glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

    light->GetShadowMap()->CreateFrameBuffer();
    glClear(GL_DEPTH_BUFFER_BIT);

    glm::mat4 calculatedLightTransform = light->CalculateLightTransform();
    directionalShadowShader.SetDirectionalLightTransform(&calculatedLightTransform);

    directionalShadowShader.Validate();
    RenderScene(directionalShadowShader);
    light->GetShadowMap()->DeleteFrameBuffer();
}

void OmniShadowMapPass(Sald::PointLight *light)
{
    glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

    omniShadowShader.Bind();
    light->GetShadowMap()->CreateFrameBuffer();
    glClear(GL_DEPTH_BUFFER_BIT);

    omniShadowShader.SetFloat3("lightPos", light->GetPosition().x, light->GetPosition().y, light->GetPosition().z);
    omniShadowShader.SetFloat("farPlane", light->GetFarPlane());

    omniShadowShader.SetOmniLightMatrices(light->CalculateLightTransform());
    omniShadowShader.Validate();
    RenderScene(omniShadowShader);

    light->GetShadowMap()->DeleteFrameBuffer();
}

void RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{

    glViewport(0, 0, 1280, 720);

    Sald::Renderer::SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    Sald::Renderer::Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    skybox.DrawSkybox(viewMatrix, projectionMatrix);

    shaderList[0].Bind();

    shaderList[0].SetMat4("projection", projectionMatrix);
    shaderList[0].SetMat4("view", viewMatrix);
    shaderList[0].SetFloat3("eyePosition", camera.GetCameraPosition().x, camera.GetCameraPosition().y, camera.GetCameraPosition().z);

    directionalLight.UseLight(&(shaderList[0]));
    pointLights[0].UseLight(&(shaderList[0]), pointLightCount, 3, 0);
    pointLights[1].UseLight(&(shaderList[0]), pointLightCount, 3, 0);
    spotLights[0].UseLight(&(shaderList[0]), spotLightCount, 3 + pointLightCount, pointLightCount);

    glm::mat4 calculatedLightTransform = directionalLight.CalculateLightTransform();
    shaderList[0].SetDirectionalLightTransform(&calculatedLightTransform);

    directionalLight.GetShadowMap()->Read(GL_TEXTURE2);

    shaderList[0].SetTexture(1);
    shaderList[0].SetDirectionalShadowMap(2);
    glm::vec3 lowerLight = camera.GetCameraPosition();
    lowerLight.y -= 0.2f;
    spotLights[0].Move(lowerLight, camera.GetCameraDirection());

    shaderList[0].Validate();
    RenderScene(shaderList[0]);
}

void LightningPass()
{
    DirectionalShadowMapPass(&directionalLight);
    for (size_t i = 0; i < pointLightCount; i++)
    {
        OmniShadowMapPass(&pointLights[i]);
    }
    for (size_t i = 0; i < spotLightCount; i++)
    {
        OmniShadowMapPass(&spotLights[i]);
    }
}
int main()
// int WinMain()
{
    mainWindow = std::make_unique<Sald::Window>(1280, 720);
    mainWindow->Initialize();
    mainWindow->SetCursorEnabled(false);
    mainWindow->SetVSync(true);

    CreateObjects();
    CreateShaders();

    camera = Sald::Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

    brickTexture = Sald::Texture("Textures/brick.png");
    brickTexture.LoadTexture();
    dirtTexture = Sald::Texture("Textures/dirt.png");
    dirtTexture.LoadTexture();
    plainTexture = Sald::Texture("Textures/plain.png");
    plainTexture.LoadTexture();

    shinyMaterial = Sald::Material(1.0f, 32.0f);
    dullMaterial = Sald::Material(0.3f, 4.0f);

    blackhawk = Sald::Model();
    blackhawk.LoadModel("Models/uh60.obj");

    xwing = Sald::Model();
    xwing.LoadModel("Models/x-wing.obj");

    directionalLight = Sald::DirectionalLight(2048, 2048,
                                              1.0f, 0.53f, 0.3f,
                                              0.1f, 0.9f,
                                              -10.0f, -12.0f, 18.5f);

    pointLights[0] = Sald::PointLight(1024, 1024,
                                      0.01f, 100.0f,
                                      0.0f, 0.0f, 1.0f,
                                      0.0f, 1.0f,
                                      1.0f, 2.0f, 0.0f,
                                      0.3f, 0.2f, 0.1f, 0);
    pointLightCount++;
    pointLights[1] = Sald::PointLight(1024, 1024,
                                      0.01f, 100.0f,
                                      0.0f, 1.0f, 0.0f,
                                      0.0f, 1.0f,
                                      -4.0f, 3.0f, 0.0f,
                                      0.3f, 0.2f, 0.1f, 1);
    pointLightCount++;

    spotLights[0] = Sald::SpotLight(1024, 1024,
                                    0.01f, 100.0f,
                                    1.0f, 1.0f, 1.0f,
                                    0.0f, 2.0f,
                                    0.0f, 0.0f, 0.0f,
                                    0.0f, -1.0f, 0.0f,
                                    1.0f, 0.0f, 0.0f,
                                    20.0f, 0);
    spotLightCount++;

    std::vector<std::string> skyboxFaces;
    skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
    skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
    skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
    skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
    skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
    skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

    skybox = Sald::Skybox(skyboxFaces);

    glm::mat4 projection = glm::perspective(glm::radians(60.0f), mainWindow->GetBufferWidth() / mainWindow->GetBufferHeight(), 0.1f, 100.0f);
    while (!mainWindow->GetShouldClose())
    {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        mainWindow->PollEvents();

        camera.KeyControl(mainWindow->GetKeys(), deltaTime);
        camera.MouseControl(mainWindow->GetXChange(), mainWindow->GetYChange());

        if (mainWindow->GetKeys()[GLFW_KEY_L])
        {
            spotLights[0].Toggle();
            mainWindow->GetKeys()[GLFW_KEY_L] = false;
        }

        LightningPass();
        RenderPass(camera.CalculateViewMatrix(), projection);

        mainWindow->SwapBuffers();
        mainWindow->ShowFPS();
    }

    return 0;
}
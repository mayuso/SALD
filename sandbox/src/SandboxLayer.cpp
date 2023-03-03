#include "SandboxLayer.h"
#include "sald.h"

SandboxLayer::SandboxLayer()
    : Layer(" SandboxLayer ")
{
    CreateObjects();
    CreateShaders();

    m_Camera = Sald::Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 10.0f, 10.0f);

    Sald::TextureManager::NewTexture("brick", "Textures/brick.png");
    Sald::TextureManager::NewTexture("dirt", "Textures/dirt.png");
    Sald::TextureManager::NewTexture("plain", "Textures/plain.png");


    shinyMaterial = Sald::Material(1.0f, 32.0f);
    dullMaterial = Sald::Material(0.3f, 4.0f);

    blackhawk = Sald::Model();
    blackhawk.Load("Models/uh60.obj");

    xwing = Sald::Model();
    xwing.Load("Models/x-wing.obj");

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

    m_Projection = glm::perspective(glm::radians(60.0f), m_Camera.GetAspectRatio(), 0.1f, 100.0f);
}

void SandboxLayer::CreateObjects()
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

    CalcAverageNormals(indices, 12, vertices, 32, 8, 5);

    Sald::Mesh *obj1 = new Sald::Mesh(vertices, indices, 32, 12, true);
    meshList.push_back(obj1);

    Sald::Mesh *obj2 = new Sald::Mesh(vertices, indices, 32, 12, true);
    meshList.push_back(obj2);

    Sald::Mesh *obj3 = new Sald::Mesh(floorVertices, floorIndices, 32, 6, true);
    meshList.push_back(obj3);
}

void SandboxLayer::CalcAverageNormals(unsigned int *indices, unsigned int indiceCount, GLfloat *vertices, unsigned int verticeCount,
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

void SandboxLayer::CreateShaders()
{
    Sald::ShaderManager::NewShader("shader", vShader, fShader);
    Sald::ShaderManager::NewShader("light", "Shaders/directional_shadow_map.vert", "Shaders/directional_shadow_map.frag");
    Sald::ShaderManager::NewShader("shadowMap", "Shaders/omni_directional_shadow_map.vert", "Shaders/omni_directional_shadow_map.geom", "Shaders/omni_directional_shadow_map.frag");
}

void SandboxLayer::OnUpdate(GLfloat deltaTime)
{
    m_Camera.OnUpdate(deltaTime);
    if (Sald::Input::IsKeyPressed(Sald::Key::L))
    {
        spotLights[0].Toggle();
    }
    LightningPass();
    RenderPass(m_Camera.CalculateViewMatrix(), m_Projection);
}

void SandboxLayer::LightningPass()
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

void SandboxLayer::DirectionalShadowMapPass(Sald::DirectionalLight *light)
{
    Sald::Shader* directionalShadowShader = Sald::ShaderManager::GetShader("light");
    directionalShadowShader->Bind();

    light->GetShadowMap()->CreateFrameBuffer();

    glm::mat4 calculatedLightTransform = light->CalculateLightTransform();
    directionalShadowShader->SetDirectionalLightTransform(&calculatedLightTransform);

    directionalShadowShader->Validate();
    RenderScene(directionalShadowShader);
    light->GetShadowMap()->DeleteFrameBuffer();
}

void SandboxLayer::OmniShadowMapPass(Sald::PointLight *light)
{
    Sald::Shader* omniShadowShader = Sald::ShaderManager::GetShader("shadowMap");
    omniShadowShader->Bind();
    light->GetShadowMap()->CreateFrameBuffer();

    omniShadowShader->SetFloat3("lightPos", light->GetPosition().x, light->GetPosition().y, light->GetPosition().z);
    omniShadowShader->SetFloat("farPlane", light->GetFarPlane());

    omniShadowShader->SetOmniLightMatrices(light->CalculateLightTransform());
    omniShadowShader->Validate();
    RenderScene(omniShadowShader);

    light->GetShadowMap()->DeleteFrameBuffer();
}

void SandboxLayer::RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
    Sald::Renderer3D::SetViewport(0, 0, 1280, 720);
    Sald::Renderer3D::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    Sald::Renderer3D::Clear();

    skybox.DrawSkybox(viewMatrix, projectionMatrix);

    Sald::Shader* shader = Sald::ShaderManager::GetShader("shader");
    shader->Bind();

    shader->SetMat4("projection", projectionMatrix);
    shader->SetMat4("view", viewMatrix);
    shader->SetFloat3("eyePosition", m_Camera.GetCameraPosition().x, m_Camera.GetCameraPosition().y, m_Camera.GetCameraPosition().z);

    directionalLight.UseLight(shader);
    pointLights[0].UseLight(shader, pointLightCount, 3, 0);
    pointLights[1].UseLight(shader, pointLightCount, 3, 0);
    spotLights[0].UseLight(shader, spotLightCount, 3 + pointLightCount, pointLightCount);

    glm::mat4 calculatedLightTransform = directionalLight.CalculateLightTransform();
    shader->SetDirectionalLightTransform(&calculatedLightTransform);

    directionalLight.GetShadowMap()->Read(GL_TEXTURE2);

    shader->SetTexture(1);
    shader->SetDirectionalShadowMap(2);
    glm::vec3 lowerLight = m_Camera.GetCameraPosition();
    lowerLight.y -= 0.2f;
    spotLights[0].Move(lowerLight, m_Camera.GetCameraDirection());

    shader->Validate();
    RenderScene(shader);
}

void SandboxLayer::RenderScene(Sald::Shader *currentShader)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
    // model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
    currentShader->SetMat4("model", model);
    Sald::TextureManager::GetTexture("brick")->Use();
    shinyMaterial.UseMaterial(currentShader);
    meshList[0]->RenderMesh();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-4.0f, 1.0f, -4.0f));
    // model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
    currentShader->SetMat4("model", model);
    Sald::TextureManager::GetTexture("dirt")->Use();
    dullMaterial.UseMaterial(currentShader);
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
    currentShader->SetMat4("model", model);
    shinyMaterial.UseMaterial(currentShader);
    blackhawk.Render();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-7.0f, 1.0f, 10.0f));
    model = glm::scale(model, glm::vec3(0.006f, 0.006f, 0.006f));
    currentShader->SetMat4("model", model);
    shinyMaterial.UseMaterial(currentShader);
    xwing.Render();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
    // model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
    currentShader->SetMat4("model", model);
    Sald::TextureManager::GetTexture("dirt")->Use();
    shinyMaterial.UseMaterial(currentShader);
    meshList[2]->RenderMesh();
}

void SandboxLayer::OnEvent(Sald::Event &event)
{
    SALD_LOG("ExampleLayer :: OnUpdate - DeltaTime: {0}", event);

    // TODO: Controls with new Event system
    /*m_Camera.KeyControl(m_MainWindow->GetKeys(), deltaTime);
    m_Camera.MouseControl(m_MainWindow->GetXChange(), m_MainWindow->GetYChange());
    */
}

SandboxLayer::~SandboxLayer()
{
}
#include "GameLayer.h"
#include "sald.h"
#include "GameObject2D.h"

using namespace Sald;

GameLayer::GameLayer()
    : Layer(" GameLayer ")
{
    ShaderManager::NewShader("sprite", "Shaders/sprite.vert", "Shaders/sprite.frag");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
                                      static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);

    ShaderManager::GetShader("sprite")->Bind();
    ShaderManager::GetShader("sprite")->SetInt("image", 0);
    ShaderManager::GetShader("sprite")->SetMat4("projection", projection);

    // set render-specific controls
    m_SpriteRenderer = new Sprite(ShaderManager::GetShader("sprite"));
    // load textures

    Sald::TextureManager::NewTexture("background", "Textures/background.jpg");
    Sald::TextureManager::NewTexture("awesomeface", "Textures/awesomeface.png");
    Sald::TextureManager::NewTexture("block", "Textures/block.png");
    Sald::TextureManager::NewTexture("block_solid", "Textures/block_solid.png");
    Sald::TextureManager::NewTexture("paddle", "Textures/paddle.png");

    // load levels
    GameLevel one;
    one.Load("Levels/one.lvl", this->Width, this->Height / 2);
    GameLevel two;
    two.Load("Levels/two.lvl", this->Width, this->Height / 2);
    GameLevel three;
    three.Load("Levels/three.lvl", this->Width, this->Height / 2);
    GameLevel four;
    four.Load("Levels/four.lvl", this->Width, this->Height / 2);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    m_CurrentLevel = 0;
    // configure game objects
    glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
    player = new GameObject2D(playerPos, PLAYER_SIZE, Sald::TextureManager::GetTexture("paddle"));
    m_State = GAME_ACTIVE;
}

GameLayer::~GameLayer()
{
}

void GameLayer::OnUpdate(GLfloat deltaTime)
{
    // TODO: Make Render a Layer function at the same level as OnUpdate
    Sald::Renderer2D::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    Sald::Renderer2D::Clear();
    Render();
}

void GameLayer::OnEvent(Sald::Event &event)
{
    // SALD_LOG("ExampleLayer :: OnUpdate - Event: {0}", event);

    if (m_State == GAME_ACTIVE)
    {
        // TODO: This 1 should be deltaTime. Right now OnUpdate receives it, but OnEvent does not.
        // Think about how to pass it here in a clean way
        float velocity = PLAYER_VELOCITY * 1;

        if (this->Keys[GLFW_KEY_A])
        {
            if (player->Position.x >= 0.0f)
                player->Position.x -= velocity;
        }
        if (this->Keys[GLFW_KEY_D])
        {
            if (player->Position.x <= this->Width - player->Size.x)
                player->Position.x += velocity;
        }
    }
}

void GameLayer::Render()
{
    if (m_State == GAME_ACTIVE)
    {
        // draw background
        m_SpriteRenderer->Draw(Sald::TextureManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
        // draw level
        this->Levels[m_CurrentLevel].Draw(*m_SpriteRenderer);
        // draw player
        player->Draw(*m_SpriteRenderer);
    }
}
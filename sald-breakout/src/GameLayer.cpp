#include "GameLayer.h"
#include "sald.h"
#include "GameObject.h"

using namespace Sald;

// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
const float BALL_RADIUS = 12.5f;

GameLayer::GameLayer()
    : Layer(" GameLayer ")
{
    ShaderManager::NewShader("sprite", "Shaders/sprite.vert", "Shaders/sprite.frag");
    // configure shaders
    m_Width = 1280;
    m_Height = 720;
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_Width),
                                      static_cast<float>(m_Height), 0.0f, -1.0f, 1.0f);

    ShaderManager::GetShader("sprite")->Bind();
    ShaderManager::GetShader("sprite")->SetInt("image", 0);
    ShaderManager::GetShader("sprite")->SetMat4("projection", projection);

    // set render-specific controls
    m_SpriteRenderer = new SpriteRenderer(ShaderManager::GetShader("sprite"));
    // load textures

    Sald::TextureManager::NewTexture("background", "Textures/background.jpg");
    Sald::TextureManager::NewTexture("face", "Textures/awesomeface.png");
    Sald::TextureManager::NewTexture("block", "Textures/block.png");
    Sald::TextureManager::NewTexture("block_solid", "Textures/block_solid.png");
    Sald::TextureManager::NewTexture("paddle", "Textures/paddle.png");

    // load levels
    GameLevel one;
    one.Load("Levels/one.lvl", m_Width, m_Height / 2);
    GameLevel two;
    two.Load("Levels/two.lvl", m_Width, m_Height / 2);
    GameLevel three;
    three.Load("Levels/three.lvl", m_Width, m_Height / 2);
    GameLevel four;
    four.Load("Levels/four.lvl", m_Width, m_Height / 2);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    m_CurrentLevel = 0;
    // configure game objects
    glm::vec2 playerPos = glm::vec2(m_Width / 2.0f - PLAYER_SIZE.x / 2.0f, m_Height - PLAYER_SIZE.y);
    m_Player = new GameObject(playerPos, PLAYER_SIZE, Sald::TextureManager::GetTexture("paddle"));

    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS,
                                              -BALL_RADIUS * 2.0f);
    m_Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY,
                            Sald::TextureManager::GetTexture("face"));

    m_State = GAME_ACTIVE;
}

GameLayer::~GameLayer()
{
}

void GameLayer::OnUpdate(GLfloat deltaTime)
{
    // TODO: Make Render a Layer function at the same level as OnUpdate
    Sald::RenderCommand::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    Sald::RenderCommand::Clear();

    m_Ball->Move(deltaTime, m_Width);

    Render();
}

void GameLayer::OnEvent(Sald::Event &event)
{
    SALD_LOG("ExampleLayer :: OnUpdate - Event: {0}", event);

    // TODO: PLAYER_VELOCITY * 0.01f should be multiplying deltaTime. Right now OnUpdate receives it, but OnEvent does not.
    // Think about how to pass it here in a clean way

    if (event.GetEventType() == Sald::EventType::KeyPressed)
    {

        float velocity = PLAYER_VELOCITY * 0.01f;
        // move playerboard
        if (Sald::Input::IsKeyPressed(Sald::Key::A))
        {
            if (m_Player->Position.x >= 0.0f)
            {
                m_Player->Position.x -= velocity;
                if (m_Ball->Stuck)
                    m_Ball->Position.x -= velocity;
            }
        }
        if (Sald::Input::IsKeyPressed(Sald::Key::D))
        {
            if (m_Player->Position.x <= m_Width - m_Player->Size.x)
            {
                m_Player->Position.x += velocity;
                if (m_Ball->Stuck)
                    m_Ball->Position.x += velocity;
            }
        }
        if (this->Keys[GLFW_KEY_SPACE])
            m_Ball->Stuck = false;
    }
}

void GameLayer::Render()
{
    if (m_State == GAME_ACTIVE)
    {
        // draw background
        m_SpriteRenderer->Draw(Sald::TextureManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(m_Width, m_Height), 0.0f);
        // draw level
        this->Levels[m_CurrentLevel].Draw(m_SpriteRenderer);
        // draw player
        m_Player->Draw(m_SpriteRenderer);

        m_Ball->Draw(m_SpriteRenderer);
    }
}
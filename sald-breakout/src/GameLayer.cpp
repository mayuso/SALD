#include "GameLayer.h"
#include "sald.h"
#include "GameObject.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    m_Levels.push_back(one);
    m_Levels.push_back(two);
    m_Levels.push_back(three);
    m_Levels.push_back(four);
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

void GameLayer::OnUpdate(Sald::Timestep timestep)
{
    // TODO: Make Render a Layer function at the same level as OnUpdate
    Sald::RenderCommand::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    Sald::RenderCommand::Clear();

    m_Ball->Move(timestep, m_Width);

    this->DoCollisions();

    if (m_Ball->Position.y >= m_Height) // did ball reach bottom edge?
    {
        SALD_LOG("RESET LEVEL AND PLAYER HERE");
        //this->ResetLevel();
        //this->ResetPlayer();
    }

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
        m_Levels[m_CurrentLevel].Draw(m_SpriteRenderer);
        // draw player
        m_Player->Draw(m_SpriteRenderer);

        m_Ball->Draw(m_SpriteRenderer);
    }
}


void GameLayer::DoCollisions()
{
    for (GameObject &box : m_Levels[m_CurrentLevel].m_Bricks)
    {
        if (!box.Destroyed)
        {
            Collision collision = CheckCollisionCircle(*m_Ball, box);
            if (std::get<0>(collision)) // if collision is true
            {
                // destroy block if not solid
                if (!box.IsSolid)
                    box.Destroyed = true;
                // collision resolution
                Direction dir = std::get<1>(collision);
                glm::vec2 diff_vector = std::get<2>(collision);
                if (dir == LEFT || dir == RIGHT) // horizontal collision
                {
                    m_Ball->Velocity.x = -m_Ball->Velocity.x; // reverse horizontal velocity
                    // relocate
                    float penetration = m_Ball->Radius - std::abs(diff_vector.x);
                    if (dir == LEFT)
                        m_Ball->Position.x += penetration; // move ball to right
                    else
                        m_Ball->Position.x -= penetration; // move ball to left;
                }
                else // vertical collision
                {
                    m_Ball->Velocity.y = -m_Ball->Velocity.y; // reverse vertical velocity
                    // relocate
                    float penetration = m_Ball->Radius - std::abs(diff_vector.y);
                    if (dir == UP)
                        m_Ball->Position.y -= penetration; // move ball back up
                    else
                        m_Ball->Position.y += penetration; // move ball back down
                }
            }
        }
    }

    Collision result = CheckCollisionCircle(*m_Ball, *m_Player);
    if (!m_Ball->Stuck && std::get<0>(result))
    {
        // check where it hit the board, and change velocity based on where it hit the board
        float centerBoard = m_Player->Position.x + m_Player->Size.x / 2.0f;
        float distance = (m_Ball->Position.x + m_Ball->Radius) - centerBoard;
        float percentage = distance / (m_Ball->Size.x / 2.0f);
        // then move accordingly
        float strength = 2.0f;
        glm::vec2 oldVelocity = m_Ball->Velocity;
        m_Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength; 
        //m_Ball->Velocity.y = -m_Ball->Velocity.y;
        m_Ball->Velocity.y = -1.0f * abs(m_Ball->Velocity.y);
        m_Ball->Velocity = glm::normalize(m_Ball->Velocity) * glm::length(oldVelocity);
    } 
} 


bool GameLayer::CheckCollision(GameObject &one, GameObject &two)
{
    // collision x-axis?
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
        two.Position.x + two.Size.x >= one.Position.x;
    // collision y-axis?
    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
        two.Position.y + two.Size.y >= one.Position.y;
    // collision only if on both axes
    return collisionX && collisionY;
} 


Collision GameLayer::CheckCollisionCircle(BallObject &one, GameObject &two) // AABB - Circle collision
{
    // get center point circle first 
    glm::vec2 center(one.Position + one.Radius);
    // calculate AABB info (center, half-extents)
    glm::vec2 aabb_half_extents(two.Size.x / 2.0f, two.Size.y / 2.0f);
    glm::vec2 aabb_center(
        two.Position.x + aabb_half_extents.x, 
        two.Position.y + aabb_half_extents.y
    );
    // get difference vector between both centers
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    // add clamped value to AABB_center and we get the value of box closest to circle
    glm::vec2 closest = aabb_center + clamped;
    // retrieve vector between center circle and closest point AABB and check if length <= radius
    difference = closest - center;
    if (glm::length(difference) <= one.Radius)
        return std::make_tuple(true, VectorDirection(difference), difference);
    else
        return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}   


Direction GameLayer::VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),	// up
        glm::vec2(1.0f, 0.0f),	// right
        glm::vec2(0.0f, -1.0f),	// down
        glm::vec2(-1.0f, 0.0f)	// left
    };
    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}   
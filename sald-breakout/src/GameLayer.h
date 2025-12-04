#pragma once
#include "Sald/Core/Timestep.h"
#include "sald.h"

#include "GameLevel.h"
#include "BallObject.h"

enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};   

using Collision = std::tuple<bool, enum Direction, glm::vec2>;

const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const float PLAYER_VELOCITY(1000.0f);

class GameLayer : public Sald::Layer
{
public:
    GameLayer();
    ~GameLayer();

    GameState m_State;
    bool Keys[1024];
    unsigned int m_Width, m_Height;
    std::vector<GameLevel> m_Levels;
    unsigned int m_CurrentLevel;

    void Init();

    void ProcessInput(float dt);
    void Render();

    void OnUpdate(Sald::Timestep timestep) override;
    void OnEvent(Sald::Event &event) override;

    void DoCollisions();
    bool CheckCollision(GameObject &one, GameObject &two);
    Collision CheckCollisionCircle(BallObject &one, GameObject &two);
    Direction VectorDirection(glm::vec2 target);

    Sald::SpriteRenderer *m_SpriteRenderer;
    GameObject *m_Player;
    BallObject *m_Ball;
};
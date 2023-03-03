#pragma once
#include "sald.h"

#include "GameLevel.h"

enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const float PLAYER_VELOCITY(500.0f);

class GameLayer : public Sald::Layer
{
public:
    GameLayer();
    ~GameLayer();

    GameState m_State;
    bool Keys[1024];
    unsigned int Width, Height;
    std::vector<GameLevel> Levels;
    unsigned int m_CurrentLevel;

    void Init();

    void ProcessInput(float dt);
    void Render();

    void OnUpdate(GLfloat deltaTime) override;
    void OnEvent(Sald::Event &event) override;

    Sald::Sprite *m_SpriteRenderer;
    GameObject2D *player;
};
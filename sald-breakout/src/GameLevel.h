
#include <vector>
#include "sald.h"
#include "GameObject2D.h"

class GameLevel
{
public:
    GameLevel();
    ~GameLevel();
    // level state
    std::vector<GameObject2D> Bricks;
    // constructor

    // loads level from file
    void Load(const char *file, unsigned int levelWidth, unsigned int levelHeight);
    // render level
    void Draw(Sald::Sprite &renderer);
    // check if the level is completed (all non-solid tiles are destroyed)
    bool IsCompleted();
private:
    // initialize level from tile data
    void init(std::vector<std::vector<unsigned int>> tileData,
              unsigned int levelWidth, unsigned int levelHeight);
};
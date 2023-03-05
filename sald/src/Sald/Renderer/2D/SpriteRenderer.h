#pragma once
#include "Sald/Core/Core.h"

#include "Sald/Renderer/Shader.h"
#include "Sald/Renderer/Texture.h"
#include "Sald/Renderer/Mesh.h"

namespace Sald
{
    class SpriteRenderer
    {
    public:
        SALD_API SpriteRenderer(Shader *shader);
        SALD_API ~SpriteRenderer();

        SALD_API void Draw(Texture *texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

    private:
        void CreateSprite();

        Shader *m_Shader;
        GLuint m_VAO;
    };

}

#pragma once
#include "Sald/Core/Core.h"

#include "Sald/Utils/CommonValues.h"
#include "Sald/Renderer/Shader.h"
#include "Sald/Renderer/Mesh.h"
#include "Sald/Renderer/Texture.h"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Sald
{
    class Skybox
    {
    public:
        SALD_API Skybox();
        SALD_API Skybox(std::vector<std::string> faceLocations);

        SALD_API void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
        SALD_API ~Skybox();

    private:
        Mesh *skyMesh;
        Shader *skyShader;

        GLuint textureId;
        Sald::Texture texture;
    };

}
#pragma once
#include "Sald/sald_api.h"

#include "Sald/CommonValues.h"
#include "Sald/Shader.h"
#include "Sald/Mesh.h"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>

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
    };

}
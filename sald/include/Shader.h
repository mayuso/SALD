#pragma once
#include "sald_api.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

namespace Sald
{
    class Shader
    {
    public:
        SALD_API Shader();
        SALD_API ~Shader();

        SALD_API void CreateFromFiles(const char *vertexLocation, const char *fragmentLocation);
        SALD_API void CreateFromFiles(const char *vertexLocation, const char *geometryLocation, const char *fragmentLocation);
        SALD_API void Validate();

        SALD_API std::string ReadFile(const char *fileLocation);

        SALD_API void Bind();
        SALD_API void Unbind();
        SALD_API void ClearShader();

        SALD_API void SetInt(const std::string &name, GLuint value);
        SALD_API void SetFloat(const std::string &name, GLfloat value);
        SALD_API void SetFloat3(const std::string &name, GLfloat x, GLfloat y, GLfloat z);
        SALD_API void SetMat4(const std::string &name, const glm::mat4 &matrix);

        SALD_API void SetTexture(GLuint textureUnit);
        SALD_API void SetDirectionalShadowMap(GLuint textureUnit);
        SALD_API void SetDirectionalLightTransform(glm::mat4 *lTransform);
        SALD_API void SetOmniLightMatrices(std::vector<glm::mat4> lightMatrices);

    private:
        GLuint m_RendererID;

        void CompileShader(const char *vertexCode, const char *fragmentCode);
        void CompileShader(const char *vertexCode, const char *geometryCode, const char *fragmentCode);
        void AddShader(GLuint theProgram, const char *shaderCode, GLenum shaderType);
        void CompileProgram();
    };
}

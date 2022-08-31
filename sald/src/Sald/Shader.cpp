#include "saldpch.h"
#include "Shader.h"

#include "Log.h"

#include "glm/gtc/type_ptr.hpp"

#include <cstring>

Sald::Shader::Shader()
    : m_RendererID(0)
{
}

Sald::Shader::~Shader()
{
    ClearShader();
}

void Sald::Shader::CreateFromFiles(const char *vertexLocation, const char *fragmentLocation)
{
    std::string vertexString = ReadFile(vertexLocation);
    std::string fragmentString = ReadFile(fragmentLocation);

    const char *vertexCode = vertexString.c_str();
    const char *fragmentCode = fragmentString.c_str();

    CompileShader(vertexCode, fragmentCode);
}

void Sald::Shader::CreateFromFiles(const char *vertexLocation, const char *geometryLocation, const char *fragmentLocation)
{
    std::string vertexString = ReadFile(vertexLocation);
    std::string geometryString = ReadFile(geometryLocation);
    std::string fragmentString = ReadFile(fragmentLocation);

    const char *vertexCode = vertexString.c_str();
    const char *geometryCode = geometryString.c_str();
    const char *fragmentCode = fragmentString.c_str();

    CompileShader(vertexCode, geometryCode, fragmentCode);
}

std::string Sald::Shader::ReadFile(const char *fileLocation)
{
    std::string content;
    std::ifstream fileStream(fileLocation, std::ios::in);

    if (!fileStream.is_open())
    {
        SALD_CORE_ERROR("Failed to read {0}! File does not exist.", fileLocation);
        return "";
    }

    std::string line = "";
    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }
    fileStream.close();
    return content;
}

void Sald::Shader::Bind()
{
    glUseProgram(m_RendererID);
}
void Sald::Shader::Unbind()
{
    glUseProgram(0);
}

void Sald::Shader::ClearShader()
{
    if (m_RendererID != 0)
    {
        glDeleteProgram(m_RendererID);
        m_RendererID = 0;
    }
}

void Sald::Shader::CompileShader(const char *vertexCode, const char *fragmentCode)
{
    m_RendererID = glCreateProgram();
    if (!m_RendererID)
    {
        SALD_CORE_ERROR("Error creating shader program!");
        return;
    }

    AddShader(m_RendererID, vertexCode, GL_VERTEX_SHADER);
    AddShader(m_RendererID, fragmentCode, GL_FRAGMENT_SHADER);

    CompileProgram();
}

void Sald::Shader::CompileShader(const char *vertexCode, const char *geometryCode, const char *fragmentCode)
{
    m_RendererID = glCreateProgram();
    if (!m_RendererID)
    {
        SALD_CORE_ERROR("Error creating shader program!");
        return;
    }

    AddShader(m_RendererID, vertexCode, GL_VERTEX_SHADER);
    AddShader(m_RendererID, geometryCode, GL_GEOMETRY_SHADER);
    AddShader(m_RendererID, fragmentCode, GL_FRAGMENT_SHADER);

    CompileProgram();
}

void Sald::Shader::Validate()
{
    GLint result = 0;
    GLchar eLog[1024] = {0};
    glValidateProgram(m_RendererID);
    glGetProgramiv(m_RendererID, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(m_RendererID, sizeof(eLog), NULL, eLog);
        SALD_CORE_ERROR("Error validating program: '{0}'", eLog);
        return;
    }
}

void Sald::Shader::CompileProgram()
{
    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(m_RendererID);
    glGetProgramiv(m_RendererID, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(m_RendererID, sizeof(eLog), NULL, eLog);
        SALD_CORE_ERROR("Error linking program: '{0}'", eLog);
        return;
    }
}

void Sald::Shader::AddShader(GLuint theProgram, const char *shaderCode, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType);

    const GLchar *theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(theShader, sizeof(eLog), NULL, eLog);
        SALD_CORE_ERROR("Error compiling the {0} shader: '{1}'", shaderType, eLog);
        return;
    }

    glAttachShader(theProgram, theShader);
}

void Sald::Shader::SetTexture(GLuint textureUnit)
{
    SetInt("theTexture", textureUnit);
}
void Sald::Shader::SetDirectionalShadowMap(GLuint textureUnit)
{
    SetInt("directionalShadowMap", textureUnit);
}
void Sald::Shader::SetDirectionalLightTransform(glm::mat4 *lTransform)
{
    SetMat4("directionalLightTransform", *lTransform);
}
void Sald::Shader::SetOmniLightMatrices(std::vector<glm::mat4> lightMatrices)
{
    char locBuff[100] = {'\0'};
    for (size_t i = 0; i < 6; i++)
    {
        snprintf(locBuff, sizeof(locBuff), "lightMatrices[%zu]", i);
        SetMat4(locBuff, lightMatrices[i]);
    }
}

void Sald::Shader::SetInt(const std::string &name, GLuint value)
{
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform1i(location, value);
}
void Sald::Shader::SetFloat(const std::string &name, GLfloat value)
{
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform1f(location, value);
}
void Sald::Shader::SetFloat3(const std::string &name, GLfloat x, GLfloat y, GLfloat z)
{
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform3f(location, x, y, z);
}

void Sald::Shader::SetMat4(const std::string &name, const glm::mat4 &matrix)
{
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

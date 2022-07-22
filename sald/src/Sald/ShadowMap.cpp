#include "saldpch.h"
#include "ShadowMap.h"

Sald::ShadowMap::ShadowMap()
{
    m_FBO = 0;
    m_ShadowMap = 0;
}

bool Sald::ShadowMap::Init(GLuint width, GLuint height)
{
    m_ShadowWidth = width;
    m_ShadowHeight = height;

    glGenFramebuffers(1, &m_FBO);

    glGenTextures(1, &m_ShadowMap);
    glBindTexture(GL_TEXTURE_2D, m_ShadowMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    CreateFrameBuffer();
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_ShadowMap, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("Framebuffer error: %i\n", Status);
        return false;
    }
    DeleteFrameBuffer();

    return true;
}

void Sald::ShadowMap::CreateFrameBuffer()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO);
    glViewport(0, 0, GetShadowWidth(), GetShadowHeight());
    glClear(GL_DEPTH_BUFFER_BIT);
}

void Sald::ShadowMap::DeleteFrameBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Sald::ShadowMap::Read(GLenum texUnit)
{
    glActiveTexture(texUnit);
    glBindTexture(GL_TEXTURE_2D, m_ShadowMap);
}

GLuint Sald::ShadowMap::GetShadowWidth()
{
    return m_ShadowWidth;
}
GLuint Sald::ShadowMap::GetShadowHeight()
{
    return m_ShadowHeight;
}

Sald::ShadowMap::~ShadowMap()
{
    if (m_FBO)
    {
        glDeleteFramebuffers(1, &m_FBO);
    }

    if (m_ShadowMap)
    {
        glDeleteTextures(1, &m_ShadowMap);
    }
}

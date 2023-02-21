#include "saldpch.h"
#include "OmniShadowMap.h"

#include "Sald/Core/Log.h"

Sald::OmniShadowMap::OmniShadowMap() : ShadowMap() {}

Sald::OmniShadowMap::~OmniShadowMap()
{
}

bool Sald::OmniShadowMap::Init(unsigned int width, unsigned int height)
{
    m_ShadowWidth = width;
    m_ShadowHeight = height;

    glGenFramebuffers(1, &m_FBO);

    glGenTextures(1, &m_ShadowMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_ShadowMap);

    // 6 textures because it is a cube
    for (size_t i = 0; i < 6; i++)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, m_ShadowWidth, m_ShadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    CreateFrameBuffer();
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_ShadowMap, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE)
    {
        SALD_CORE_ERROR("Framebuffer error: {0}", Status);
        return false;
    }

    DeleteFrameBuffer();

    return true;
}
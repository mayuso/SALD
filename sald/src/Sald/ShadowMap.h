#pragma once
#include "Core.h"

#include <glad/glad.h>

#include <stdio.h>

namespace Sald
{
    class ShadowMap
    {
    public:
        SALD_API ShadowMap();
        SALD_API ~ShadowMap();

        SALD_API virtual bool Init(GLuint width, GLuint height);
        SALD_API void Read(GLenum textureUnit);

        SALD_API void CreateFrameBuffer();
        SALD_API void DeleteFrameBuffer();

        SALD_API GLuint GetShadowWidth();
        SALD_API GLuint GetShadowHeight();

    protected:
        GLuint m_FBO, m_ShadowMap;
        GLuint m_ShadowWidth, m_ShadowHeight;
    };

}
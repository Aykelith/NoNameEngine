#ifndef NNE_TEXTURE_HPP
#define NNE_TEXTURE_HPP

#include <NNE/Global.hpp>
#include <NNE/GL.hpp>

namespace NNE {
    template <GLenum target>
    class Texture {
    public:
        Texture();

        void bind();
        static void unbind();

        static void activateTexture(unsigned int id);

        static void setTextureWrapping(GLenum WRAP_S, GLenum WRAP_T);
        static void setTextureFiltering(GLenum MIN, GLenum MAG);

        static void generateMipmap();

        static void loadImage(GLint level,
         	GLint internalFormat,
         	GLsizei width,
         	GLsizei height,
         	GLint border,
         	GLenum format,
         	GLenum type,
         	const GLvoid * data
        );

    protected:
        GLuint m_id;
    };

    typedef Texture<GL_TEXTURE_2D> 2DTexture;
}

#include <NNE/Texture.inl>

#endif // NNE_TEXTURE_HPP

namespace NNE {
    template <GLenum target>
    Texture<target>::Texture() {
        glGenTextures(1, &m_id);
    }

    template <GLenum target>
    void Texture<target>::bind() {
        glBindTexture(target, m_id);
    }

    template <GLenum target>
    void Texture<target>::unbind() {
        glBindTexture(target, 0);
    }

    template <GLenum target>
    void Texture<target>::activateTexture(unsigned int id) {
        glActiveTexture(GL_TEXTURE0 + id);
    }

    template <GLenum target>
    void Texture<target>::setTextureWrapping(GLenum WRAP_S, GLenum WRAP_T) {
        glTexParameteri(target, GL_TEXTURE_WRAP_S, WRAP_S);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, WRAP_T);
    }

    template <GLenum target>
    void Texture<target>::setTextureFiltering(GLenum MIN, GLenum MAG) {
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, MIN);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, MAG);
    }

    template <GLenum target>
    void Texture<target>::generateMipmap() {
        glGenerateMipmap(target);
    }

    template <GLenum target>
    void Texture<target>::loadImage(GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * data) {
        glTexImage2D(target, level, internalFormat, width, height, border, format, type, data);
    }
}

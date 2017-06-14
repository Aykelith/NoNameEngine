#ifndef NNE_BO_HPP
#define NNE_BO_HPP

#include <NNE/Global.hpp>

#include <GL.hpp>

namespace NNE {
    class NNE_API BO {
    public:
        BO();
        ~BO();

        void bind(GLenum target);
        void unbind() const;

        void loadData(GLsizeiptr size, const GLvoid* data, GLenum usage) const;

    private:
        GLuint m_id;
        GLenum m_target;
    };
}

#endif // NNE_BO_HPP

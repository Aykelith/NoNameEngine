#include <NNE/BO.hpp>

namespace NNE {
    BO::BO() {
        glGenBuffers(1, &m_id);
        glCheckForError();
    }

    BO::~BO() {
        glDeleteBuffers(1, &m_id);
    }

    void BO::bind(GLenum target) {
        m_target = target;
        glBindBuffer(target, m_id);
        glCheckForError();
    }

    void BO::unbind() const {
        glBindBuffer(m_target, 0);
    }

    void BO::loadData(GLsizeiptr size, const GLvoid* data, GLenum usage) const {
        glBufferData(m_target, size, data, usage);
        glCheckForError();
    }
}

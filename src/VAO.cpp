#include <NNE/VAO.hpp>

namespace NNE {
    VAO::VAO() {
        glGenVertexArrays(1, &m_id);
        glCheckForError();
    }

    VAO::~VAO() {
        glDeleteVertexArrays(1, &m_id);
    }

    void VAO::bind() const {
        glBindVertexArray(m_id);
        glCheckForError();
    }

    void VAO::unbind() {
        glBindVertexArray(0);
    }

    void VAO::configure(const std::vector<DataArrangement>& configuration, std::size_t totalSize) {
        for (GLuint i=0; i<configuration.size(); ++i) {
            const auto& arrangement = configuration[i];
            glVertexAttribPointer(i, arrangement.size, arrangement.type, arrangement.normalized, totalSize, arrangement.offset);
            glEnableVertexAttribArray(i);

            glCheckForError();
        }
    }
}

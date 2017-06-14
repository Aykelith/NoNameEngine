#ifndef NNE_VAO_HPP
#define NNE_VAO_HPP

#include <NNE/Global.hpp>
#include <GL.hpp>

#include <vector>

namespace NNE {
    class NNE_API VAO {
    public:
        struct DataArrangement {
            GLint size;
            GLenum type;
            GLboolean normalized;
            const GLvoid* offset;

            DataArrangement(GLint p_size, GLenum p_type, GLboolean p_normalized, const GLvoid* p_offset)
            : size { p_size }
            , type { p_type }
            , normalized { p_normalized }
            , offset { p_offset }
            { }
        };

    public:
        VAO();
        ~VAO();

        void bind() const;
        static void unbind();

        static void configure(const std::vector<DataArrangement>& configuration, std::size_t totalSize);

    private:
        GLuint m_id;
    };
}

#endif // NNE_VAO_HPP

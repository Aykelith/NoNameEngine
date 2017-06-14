#ifndef NNE_SHADERPROGRAM_HPP
#define NNE_SHADERPROGRAM_HPP

#include <NNE/Global.hpp>
#include <GL.hpp>
#include <vector>

#include <NNE/UniformKeeper.hpp>

namespace NNE {
    class NNE_API ShaderProgram: public UniformKeeper {
    public:
        ShaderProgram();

        bool loadShader(const char* data, GLenum type);

        bool link();
        void use() const;
        static void stop();

        bool storeUniform(uint key, const GLchar* name);

    private:
        using UniformKeeper::addUniform;

    private:
        GLuint m_program;

        std::vector<GLuint> m_shaders;
    };
}

#endif // NNE_SHADERPROGRAM_HPP

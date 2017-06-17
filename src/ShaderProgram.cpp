#include <NNE/ShaderProgram.hpp>

#include <iostream>

#include <fstream>
#include <iterator>
#include <string>

namespace NNE {
    ShaderProgram::ShaderProgram() {
        m_program = glCreateProgram();
        glCheckForError();
    }

    bool ShaderProgram::loadShader(const char* data, GLenum type) {
        auto id = glCreateShader(type);
        glShaderSource(id, 1, &data, NULL);
        glCompileShader(id);
        glCheckForError();

        GLint success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);

        if (!success) {
#ifdef NNE_ERROR_MESSAGES
            GLchar infoLog[INFOLOG_SIZE];
            glGetShaderInfoLog(id, INFOLOG_SIZE, NULL, infoLog);

            std::string shaderType = (type == GL_VERTEX_SHADER) ? "VertexShader" : "FragmentShader";
            std::cout << shaderType << " | " << infoLog << "\n";
#endif
            glDeleteShader(id);
            return false;
        }

        m_shaders.push_back(id);
        return true;
    }

    bool ShaderProgram::loadShaderFromFile(const std::string& file, GLenum type) {
        std::ifstream in(file);
        std::string contents((std::istreambuf_iterator<char>(in)),
                              std::istreambuf_iterator<char>());

#ifdef NNE_DEBUG
        std::cout << type << "\n" << "========================\n" << contents << "\n========================\n";
#endif

        return loadShader(contents.c_str(), type);
    }

    bool ShaderProgram::link() {
        for (const auto& shader : m_shaders) {
            glAttachShader(m_program, shader);
            glCheckForError();
        }
        glLinkProgram(m_program);

        GLint success;
        glGetProgramiv(m_program, GL_LINK_STATUS, &success);

        if (!success) {
#ifdef NNE_ERROR_MESSAGES
            GLchar infoLog[INFOLOG_SIZE];
            glGetProgramInfoLog(m_program, INFOLOG_SIZE, NULL, infoLog);
            std::cout << infoLog << "\n";
#endif
            return false;
        }

        // We delete the shaders because we don't need them anymore after the link was successfully
        for (const auto& shader : m_shaders) {
            glDeleteShader(shader);
        }
        m_shaders.clear();
        return true;
    }

    void ShaderProgram::use() const {
        glUseProgram(m_program);
        glCheckForError();
    }

    void ShaderProgram::stop() {
        glUseProgram(0);
    }

    bool ShaderProgram::storeUniform(uint key, const GLchar* name) {
        auto id = getUniformLocation(name);

#ifdef NNE_DEBUG
        std::cout << "Storing uniform \"" << name << "\" => " << (id != -1) << "\n";
#endif
        if (id == -1) return false;

        UniformKeeper::addUniform(key, id);
        return true;
    }

    GLint ShaderProgram::getUniformLocation(const GLchar* name) {
        return glGetUniformLocation(m_program, name);
    }
}

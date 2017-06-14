#ifndef NNE_UNIFORMKEEPER_HPP
#define NNE_UNIFORMKEEPER_HPP

#include <NNE/Global.hpp>
#include <GL.hpp>

#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace NNE {
    class UniformKeeper {
    public:
        UniformKeeper() = default;

        void addUniform(uint key, GLint id) { m_uniforms.emplace(key, id); }
        void getUniform(uint key) { m_uniforms[key]; }

        void setInt(uint id, GLint value) { glUniform1i(m_uniforms[id], value); glCheckForError(); }
        void setUInt(uint id, GLuint value) { glUniform1ui(m_uniforms[id], value); glCheckForError(); }
        void setFloat(uint id, GLfloat value) { glUniform1f(m_uniforms[id], value);  }
        void setVec3(uint id, const glm::vec3& vec3) { glUniform3f(m_uniforms[id], vec3.x, vec3.y, vec3.z); glCheckForError(); }
        void setVec4(uint id, const glm::vec4& vec4) { glUniform4f(m_uniforms[id], vec4.x, vec4.y, vec4.z, vec4.w); glCheckForError(); }
        void setMatrix(uint id, const glm::mat4& mat4) { glUniformMatrix4fv(m_uniforms[id], 1, GL_FALSE, glm::value_ptr(mat4)); glCheckForError(); }
    private:
        std::unordered_map<uint, GLint> m_uniforms;
    };
}

#endif // NNE_UNIFORMKEEPER_HPP

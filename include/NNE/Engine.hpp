#ifndef NNE_ENGINE_HPP
#define NNE_ENGINE_HPP

#include <NNE/Global.hpp>
#include <GL.hpp>

namespace NNE {
    class NNE_API Engine {
    public:
        static bool initialize() {
            glewExperimental = GL_TRUE;
            return (glewInit() == GLEW_OK);
        }
    };
}

#endif // NNE_ENGINE_HPP

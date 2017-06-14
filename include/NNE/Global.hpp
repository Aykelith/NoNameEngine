#ifndef NNE_GLOBAL_HPP
#define NNE_GLOBAL_HPP

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
  #define NNE_HELPER_DLL_IMPORT __declspec(dllimport)
  #define NNE_HELPER_DLL_EXPORT __declspec(dllexport)
  #define NNE_HELPER_DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define NNE_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define NNE_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define NNE_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define NNE_HELPER_DLL_IMPORT
    #define NNE_HELPER_DLL_EXPORT
    #define NNE_HELPER_DLL_LOCAL
  #endif
#endif

// Now we use the generic helper definitions above to define NNE_API and NNE_LOCAL.
// NNE_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// NNE_LOCAL is used for non-api symbols.

#ifdef NNE_DLL // defined if NNE is compiled as a DLL
  #ifdef NNE_DLL_EXPORTS // defined if we are building the NNE DLL (instead of using it)
    #define NNE_API NNE_HELPER_DLL_EXPORT
  #else
    #define NNE_API NNE_HELPER_DLL_IMPORT
  #endif // NNE_DLL_EXPORTS
  #define NNE_LOCAL NNE_HELPER_DLL_LOCAL
#else // NNE_DLL is not defined: this means NNE is a static lib.
  #define NNE_API
  #define NNE_LOCAL
#endif // NNE_DLL

typedef unsigned int uint;

#ifdef NNE_DEBUG
    #define NNE_ERROR_MESSAGES

    #include <iostream>
    #include <GL.hpp>
    inline GLenum glCheckForError_(const char *file, int line) {
        GLenum errorCode;
        if ((errorCode = glGetError()) != GL_NO_ERROR)
        {
            std::string error;
            switch (errorCode)
            {
                case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
                case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
                case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
                case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
                case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
                case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
                case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
            }
            std::cout << error << " | " << file << " (" << line << ")" << std::endl;
        }
        return errorCode;
    }
    #define glCheckForError() glCheckForError_(__FILE__, __LINE__)
#else
    #define glCheckForError()
#endif

#ifdef NNE_ERROR_MESSAGES
    #define INFOLOG_SIZE 512
#endif

#define GLM_FORCE_CXX14

#endif // NNE_GLOBAL_HPP

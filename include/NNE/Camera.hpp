#ifndef NNE_CAMERA_HPP
#define NNE_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace NNE {
    class Camera {
    public:
        Camera() = default;

        void setPosition(const glm::vec3& pos);
        void setFront(const glm::vec3& front);
        void setUp(const glm::vec3& up);

        const glm::mat4& getView();

    private:
        void update();

    private:
        glm::vec3 m_pos;
        glm::vec3 m_front;
        glm::vec3 m_up;

        glm::mat4 m_view;

        bool m_needUpdate = false;
    };
}

#endif // NNE_CAMERA_HPP

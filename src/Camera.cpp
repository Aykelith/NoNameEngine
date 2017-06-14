#include <NNE/Camera.hpp>

namespace NNE {
    void Camera::setPosition(const glm::vec3& pos) {
        m_pos = pos;
        m_needUpdate = true;
    }

    void Camera::setFront(const glm::vec3& front) {
        m_front = front;
        m_needUpdate = true;
    }

    void Camera::setUp(const glm::vec3& up) {
        m_up = up;
        m_needUpdate = true;
    }

    void Camera::update() {
        if (m_needUpdate) {
            m_view = glm::lookAt(m_pos, m_pos + m_front, m_up);
            m_needUpdate = false;
        }
    }

    const glm::mat4& Camera::getView() {
        update();
        return m_view;
    }
}

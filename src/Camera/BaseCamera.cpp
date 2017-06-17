#include <NNE/Camera/BaseCamera.hpp>

namespace NNE {
    void BaseCamera::setPosition(const glm::vec3& pos) {
        m_position = pos;
        m_needViewUpdate = true;
    }

    void BaseCamera::setDirection(const glm::vec3& direction) {
        m_direction = direction;
        m_needViewUpdate = true;
    }

    void BaseCamera::setUp(const glm::vec3& up) {
        m_worldUp = up;
        m_needViewUpdate = true;
    }

    void BaseCamera::setViewport(float width, float height) {
        m_viewportWidth = width;
        m_viewportHeight = height;
        m_needProjectionUpdate = true;
    }

    void BaseCamera::setNear(float near) {
        m_near = near;
        m_needProjectionUpdate = true;
    }

    void BaseCamera::setFar(float far) {
        m_far = far;
        m_needProjectionUpdate = true;
    }
}

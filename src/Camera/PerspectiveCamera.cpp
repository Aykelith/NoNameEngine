#include <NNE/Camera/PerspectiveCamera.hpp>

#include <glm/gtx/quaternion.hpp>

namespace NNE {
    PerspectiveCamera::PerspectiveCamera(float viewportWidth, float viewportHeight, float FOV, float near, float far)
    : m_fov { FOV }
    {
        m_viewportWidth = viewportWidth;
        m_viewportHeight = viewportHeight;
        m_near = near;
        m_far = far;

        m_needProjectionUpdate = true;
    }

    void PerspectiveCamera::setYaw(float yaw) {
        m_yaw = yaw;
        m_needViewUpdate = true;
    }

    void PerspectiveCamera::setPitch(float pitch) {
        m_pitch = pitch;
        m_needViewUpdate = true;
    }

    bool PerspectiveCamera::update() {
        if (m_needProjectionUpdate) {
            m_projection = glm::perspective(glm::radians(m_fov), m_viewportWidth / m_viewportHeight, m_near, m_far);

            m_needProjectionUpdate = false;

            if (!m_needViewUpdate) {
                m_combined = m_projection * m_view;
                return true;
            }
        }

        if (m_needViewUpdate) {
            glm::vec3 tempDirection;
            tempDirection.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
            tempDirection.y = sin(glm::radians(m_pitch));
            tempDirection.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
            m_direction = glm::normalize(tempDirection);

            m_right = glm::normalize(glm::cross(m_direction, m_worldUp));
            m_up    = glm::normalize(glm::cross(m_right, m_direction));

            m_view  = glm::lookAt(m_position, m_position + m_direction, m_up);
            m_combined = m_projection * m_view;

            m_needViewUpdate = false;
            return true;
        }

        return false;
    }
}

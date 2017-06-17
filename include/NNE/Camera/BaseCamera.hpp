#ifndef NNE_CAMERA_BASECAMERA_HPP
#define NNE_CAMERA_BASECAMERA_HPP

#include <NNE/Global.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace NNE {
    class NNE_API BaseCamera {
    public:
        BaseCamera() = default;

        void setPosition(const glm::vec3& pos);
        void setDirection(const glm::vec3& front);
        void setUp(const glm::vec3& up);

        void setViewport(float width, float height);
        void setNear(float near);
        void setFar(float far);

        virtual bool update() = 0;

        const glm::vec3& getPosition() const { return m_position; }
        const glm::vec3& getDirection() const { return m_direction; }
        const glm::vec3& getRight() const { return m_right; }

        const glm::mat4& getView() const { return m_view; }
        const glm::mat4& getProjection() const { return m_projection; }
        const glm::mat4& getCombined() const { return m_combined; }

    protected:
        glm::vec3 m_position;
        glm::vec3 m_direction;
        glm::vec3 m_right;
        glm::vec3 m_up;
        glm::vec3 m_worldUp;

        glm::mat4 m_projection;
        glm::mat4 m_view;
        glm::mat4 m_combined;

        float m_viewportWidth;
        float m_viewportHeight;

        float m_near;
        float m_far;

        bool m_needViewUpdate = false;
        bool m_needProjectionUpdate = false;
    };
}

#endif // NNE_CAMERA_BASECAMERA_HPP

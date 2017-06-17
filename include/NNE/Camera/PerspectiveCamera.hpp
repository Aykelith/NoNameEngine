#ifndef NNE_CAMERA_PERSPECTIVECAMERA_HPP
#define NNE_CAMERA_PERSPECTIVECAMERA_HPP

#include <NNE/Global.hpp>

#include <NNE/Camera/BaseCamera.hpp>

namespace NNE {
    class NNE_API PerspectiveCamera: public BaseCamera {
    public:
        PerspectiveCamera(float viewportWidth, float viewportHeight, float FOV, float near, float far);

        void setYaw(float yaw);
        void setPitch(float pitch);

        float getYaw() const { return m_yaw; }
        float getPitch() const { return m_pitch; }

        virtual bool update() override;
    protected:
        float m_fov;

        float m_yaw = -90.f;
        float m_pitch = 0.f;
    };
}

#endif // NNE_CAMERA_PERSPECTIVECAMERA_HPP

#include "include\ASGF\Camera.h"
#include <iostream>
#include "include\ASGF\Input.h"
#include "include\ASGF\Frames.h"

Camera* Camera::GetMainCamera()
{
    return ms_pCamera;
}

Camera::Camera(uint32_t nWidth, uint32_t nHeight) :
    m_nWidth(nWidth), m_nHeight(nHeight)
{
    if (ms_pCamera == nullptr)
        ms_pCamera = this;
    CenterCamera();
}

Camera::~Camera()
{
    if (ms_pCamera == this)
        ms_pCamera = nullptr;
}

void Camera::SetConfig(T_CameraConfig tConfig)
{
    m_tConfig = tConfig;
    if (m_tConfig.bEnableEdgePan)
    {
        std::cout << "Warning: Camera edge pan not yet implemented" << std::endl;
    }
    if (m_tConfig.bEnableGrabPan)
    {
        std::cout << "Warning: Camera grab pan not yet implemented" << std::endl;
    }
}

void Camera::MakeMain()
{
    ms_pCamera = this;
}

bool Camera::IsMain()
{
    return ms_pCamera == this;
}

void Camera::Update()
{
    if (m_tConfig.bEnableRecenter && Input::Instance()->GetKey(m_tConfig.eRecenter))
    {
        CenterCamera();
    }
    float nCamDelta = ms_zCamSpeed * Frames::DeltaTime();
    if (m_tConfig.bEnableSpeedup && Input::Instance()->GetKey(m_tConfig.eSpeedup))
    {
        nCamDelta *= 3;
    }
    if (m_tConfig.bEnableKeyMovement && Input::Instance()->GetKey(m_tConfig.eUp))
    {
        ms_pCamera->m_nY -= nCamDelta;
    }
    if (m_tConfig.bEnableKeyMovement && Input::Instance()->GetKey(m_tConfig.eDown))
    {
        ms_pCamera->m_nY += nCamDelta;
    }
    if (m_tConfig.bEnableKeyMovement && Input::Instance()->GetKey(m_tConfig.eLeft))
    {
        ms_pCamera->m_nX -= nCamDelta;
    }
    if (m_tConfig.bEnableKeyMovement && Input::Instance()->GetKey(m_tConfig.eRight))
    {
        ms_pCamera->m_nX += nCamDelta;
    }

    // todo: edge pan
    // todo: drag pan
}

void Camera::SetPos(float x, float y)
{
    m_nX = x;
    m_nY = y;
}

void Camera::SetBounds(int nMinX, int nMinY, int nMaxX, int nMaxY)
{
    throw std::exception("Unimplemented function");
    // TODO
}

WorldCoord Camera::ScreenSpaceToWorldSpace(int x, int y)
{
    return {x + static_cast<int>(m_nX), y + static_cast<int>(m_nY)};
}

WorldCoord Camera::ScreenSpaceToWorldSpace(ScreenCoord tCoord)
{
    return { tCoord.x + static_cast<int>(m_nX), tCoord.y + static_cast<int>(m_nY) };
}

float Camera::GetXOffset()
{
    return m_nX;
}

float Camera::GetYOffset()
{
    return m_nY;
}

void Camera::CenterCamera(WorldCoord coords)
{
    ms_pCamera->m_nX = static_cast<float>(coords.x - static_cast<int32_t>(m_nWidth)/2);
    ms_pCamera->m_nY = static_cast<float>(coords.y - static_cast<int32_t>(m_nHeight)/2);
}

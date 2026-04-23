#include "include\ASGF\Camera.h"
#include <iostream>
#include "include\ASGF\Input.h"
#include "include\ASGF\Frames.h"
#include "include\ASGF\Window.h"

Camera* Camera::GetMainCamera()
{
    return ms_pCamera;
}

Camera::Camera() :
    Camera(Window::GetMainWindow()->GetWidth(), Window::GetMainWindow()->GetHeight())
{}

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

void Camera::Resize(uint32_t nWidth, uint32_t nHeight)
{
    m_nHeight = nHeight;
    m_nWidth = nWidth;
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
        ms_pCamera->m_fY -= nCamDelta;
    }
    if (m_tConfig.bEnableKeyMovement && Input::Instance()->GetKey(m_tConfig.eDown))
    {
        ms_pCamera->m_fY += nCamDelta;
    }
    if (m_tConfig.bEnableKeyMovement && Input::Instance()->GetKey(m_tConfig.eLeft))
    {
        ms_pCamera->m_fX -= nCamDelta;
    }
    if (m_tConfig.bEnableKeyMovement && Input::Instance()->GetKey(m_tConfig.eRight))
    {
        ms_pCamera->m_fX += nCamDelta;
    }

    if (m_tConfig.bEnableEdgePan)
    {
        EdgePan();
    }
    if (m_tConfig.bEnableGrabPan && Input::Instance()->GetMouseButton(m_tConfig.uDragButton))
    {
        DragPan();
    }
}

void Camera::SetPos(float x, float y)
{
    m_fX = x;
    m_fY = y;
    if (m_bUseBounds)
    {
        m_fX = std::max(m_fX, m_tBoundsLower.x);
        m_fY = std::max(m_fY, m_tBoundsLower.y);
        m_fX = std::min(m_fX, m_tBoundsUpper.y);
        m_fY = std::min(m_fY, m_tBoundsUpper.y);
    }
}

void Camera::SetPos(Vector2<float> tPos)
{
    SetPos(tPos.x, tPos.y);
}

void Camera::SetBounds(float nMinX, float nMinY, float nMaxX, float nMaxY)
{
    m_tBoundsLower.x = nMinX;
    m_tBoundsLower.y = nMinY;
    m_tBoundsUpper.x = nMaxX;
    m_tBoundsUpper.y = nMaxX;
    if (m_bUseBounds)
    {
        SetPos(m_fX, m_fY);
    }
}

void Camera::SetBounds(Vector2<float> tMins, Vector2<float> tMaxs)
{
    SetBounds(tMins.x, tMins.y, tMaxs.x, tMaxs.y);
}

void Camera::SetBounds(Rect<float> tBounds)
{
    SetBounds(tBounds.x, tBounds.y, tBounds.x + tBounds.w, tBounds.y + tBounds.h);
}

void Camera::UseBounds(bool bUseBounds)
{
    m_bUseBounds = bUseBounds;
    SetPos(m_fX, m_fY);
}

WorldCoord Camera::ScreenSpaceToWorldSpace(int x, int y)
{
    return {x + static_cast<int>(m_fX), y + static_cast<int>(m_fY)};
}

WorldCoord Camera::ScreenSpaceToWorldSpace(ScreenCoord tCoord)
{
    return { tCoord.x + static_cast<int>(m_fX), tCoord.y + static_cast<int>(m_fY) };
}

float Camera::GetXOffset()
{
    return m_fX;
}

float Camera::GetYOffset()
{
    return m_fY;
}

void Camera::SetCenterPos(WorldCoord tPos)
{
    m_tCenter.x = static_cast<float>(tPos.x - static_cast<int32_t>(m_nWidth) / 2);;
    m_tCenter.y = static_cast<float>(tPos.y - static_cast<int32_t>(m_nHeight) / 2);
}

void Camera::SetScale(float fScale)
{
    m_fScale = fScale;
}

float Camera::GetScale()
{
    return m_fScale;
}

// todo: test EdgePan
void Camera::EdgePan()
{
    Vector2<float> delta;
    ScreenCoord mousePos = Input::Instance()->GetMousePos();
    if (mousePos.x <= m_tConfig.nEdgePanThreshold)
    {
        delta.x -= m_tConfig.fEdgePanSpeed;
    }
    if (mousePos.y <= m_tConfig.nEdgePanThreshold)
    {
        delta.y -= m_tConfig.fEdgePanSpeed;
    }
    if (mousePos.x >= static_cast<int32_t>(m_nWidth) - m_tConfig.nEdgePanThreshold)
    {
        delta.x += m_tConfig.fEdgePanSpeed;
    }
    if (mousePos.y >= static_cast<int32_t>(m_nHeight) - m_tConfig.nEdgePanThreshold)
    {
        delta.y += m_tConfig.fEdgePanSpeed;
    }
    delta = delta * Frames::DeltaTime();
    SetPos(m_fX + delta.x, m_fY + delta.y);
}

// todo: test DragPan
void Camera::DragPan()
{
    ScreenCoord newPos = Input::Instance()->GetMousePos();
    Vector2<float> delta = (newPos - m_tPrevMousePos).cast<float>() * m_tConfig.fDragSpeedScale * m_fScale;
    SetPos(m_fX + delta.x, m_fY + delta.y);
    m_tPrevMousePos = newPos;
}

void Camera::CenterCamera()
{
    ms_pCamera->m_fX = m_tCenter.x;
    ms_pCamera->m_fY = m_tCenter.y;
}

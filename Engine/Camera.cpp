#include "include\ASGF\Camera.h"
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
    if (Input::Instance()->GetKey(E_Keys::C))
    {
        CenterCamera();
    }
    float nCamDelta = ms_zCamSpeed * Frames::DeltaTime();
    if (Input::Instance()->GetKey(E_Keys::ShiftL))
    {
        nCamDelta *= 3;
    }
    if (Input::Instance()->GetKey(E_Keys::W))
    {
        ms_pCamera->m_nY -= nCamDelta;
    }
    if (Input::Instance()->GetKey(E_Keys::S))
    {
        ms_pCamera->m_nY += nCamDelta;
    }
    if (Input::Instance()->GetKey(E_Keys::A))
    {
        ms_pCamera->m_nX -= nCamDelta;
    }
    if (Input::Instance()->GetKey(E_Keys::D))
    {
        ms_pCamera->m_nX += nCamDelta;
    }
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

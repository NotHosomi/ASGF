#pragma once
#include <stdint.h>
#include <optional>
#include "Input.h"
#include "Coords.h"
#include "Rect.h"

struct T_CameraConfig
{
	bool bEnableRecenter = false;
	E_Keys eRecenter = E_Keys::Space;

	bool bEnableEdgePan = false;
	int nEdgePanThreshold = 10;

	bool bEnableKeyMovement = false;
	E_Keys eUp = E_Keys::W;
	E_Keys eLeft = E_Keys::A;
	E_Keys eDown = E_Keys::S;
	E_Keys eRight = E_Keys::D;

	bool bEnableGrabPan = false;
	float fEdgePanSpeed = 10;

	uint8_t uDragButton = 0;
	float fDragSpeedScale = 1;

	bool bEnableSpeedup = false;
	E_Keys eSpeedup;
};

class Camera
{
public:
	static Camera* GetMainCamera();
	Camera();
	Camera(uint32_t nWidth, uint32_t nHeight);
	~Camera();
	void Resize(uint32_t nWidth, uint32_t nHeight);
	void SetConfig(T_CameraConfig tConfig);
	void MakeMain();
	bool IsMain();
	void Update();

	void SetPos(float x, float y);
	void SetPos(Vector2<float> tPos);
	void SetBounds(float nMinX, float nMinY, float nMaxX, float nMaxY);
	void SetBounds(Vector2<float> tMins, Vector2<float> tMaxs);
	void SetBounds(Rect<float> tBounds);
	void UseBounds(bool bUseBounds);
	WorldCoord ScreenSpaceToWorldSpace(int x, int y);
	WorldCoord ScreenSpaceToWorldSpace(ScreenCoord tCoord);
	float GetXOffset();
	float GetYOffset();
	void CenterCamera();
	void SetCenterPos(WorldCoord tPos);
	void SetScale(float fScale);
	float GetScale();
private:
	void EdgePan();
	void DragPan();

	inline static Camera* ms_pCamera = nullptr;
	static constexpr float ms_zCamSpeed = 200;
	T_CameraConfig m_tConfig;
	float m_fX = 0;
	float m_fY = 0;
	uint32_t m_nWidth = 0;
	uint32_t m_nHeight = 0;
	Vector2<float> m_tCenter;
	bool m_bUseBounds;
	Vector2<float> m_tBoundsUpper;
	Vector2<float> m_tBoundsLower;
	ScreenCoord m_tPrevMousePos;
	float m_fScale;
};


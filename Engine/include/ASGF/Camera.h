#pragma once
#include <stdint.h>
#include <optional>
#include "Input.h"
#include "Coords.h"

struct T_CameraConfig
{
	bool bEnableRecenter = false;
	E_Keys eRecenter;

	bool bEnableEdgePan = false;
	int nEdgePanThreshold;

	bool bEnableKeyMovement = false;
	E_Keys eUp;
	E_Keys eLeft;
	E_Keys eDown;
	E_Keys eRight;

	bool bEnableGrabPan = false;
	uint8_t uDragButton;

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
	void SetConfig(T_CameraConfig tConfig);
	void MakeMain();
	bool IsMain();
	void Update();

	void SetPos(float x, float y);
	void SetBounds(int nMinX, int nMinY, int nMaxX, int nMaxY);
	WorldCoord ScreenSpaceToWorldSpace(int x, int y);
	WorldCoord ScreenSpaceToWorldSpace(ScreenCoord tCoord);
	float GetXOffset();
	float GetYOffset();
	void CenterCamera();
	void SetCenterPos(WorldCoord tPos);
private:
	inline static Camera* ms_pCamera = nullptr;
	static constexpr float ms_zCamSpeed = 200;
	T_CameraConfig m_tConfig;
	float m_nX = 0;
	float m_nY = 0;
	uint32_t m_nWidth = 0;
	uint32_t m_nHeight = 0;
	Vector2<float> m_tCenter;
};


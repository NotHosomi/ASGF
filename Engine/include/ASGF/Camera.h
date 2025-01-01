#pragma once
#include <stdint.h>
#include "Coords.h"

class Camera
{
public:
	static Camera* GetMainCamera();
	Camera(uint32_t nWidth, uint32_t nHeight);
	~Camera();
	void MakeMain();
	bool IsMain();
	void Update();

	void SetPos(float x, float y);
	void SetBounds(int nMinX, int nMinY, int nMaxX, int nMaxY);
	WorldCoord ScreenSpaceToWorldSpace(int x, int y);
	WorldCoord ScreenSpaceToWorldSpace(ScreenCoord tCoord);
	float GetXOffset();
	float GetYOffset();
	void CenterCamera(WorldCoord coords = {0,0});
private:
	inline static Camera* ms_pCamera = nullptr;
	static constexpr float ms_zCamSpeed = 200;
	float m_nX = 0;
	float m_nY = 0;
	uint32_t m_nWidth = 0;
	uint32_t m_nHeight = 0;
};


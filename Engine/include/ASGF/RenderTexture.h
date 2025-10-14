#pragma once
#include "RenderGeneric.h"
#include "Vector2.h"
#include "Coords.h"

class RenderTexture : public RenderGeneric
{
public:
	void Render() override;

	int GetX();
	int GetY();
	WorldCoord GetPos();
	void SetX(int val);
	void SetY(int val);
	void SetPos(WorldCoord tPos);

	int GetWidth();
	int GetHeight();
	Vector2<int> GetDims();
	void SetWidth(int w);
	void SetHeight(int h);
	void SetDims(Vector2<int> tDims);

	void SetPivot(Vector2<float> tPivot);
	Vector2<float> GetPivot();

	void SetRotation(float fDegrees);
	float GetRotation();

	void SetFlipState(ASGF::E_FlipState eFlipState);
	ASGF::E_FlipState GetFlipState();

protected:
	RenderTexture() = default;
	RenderTexture(RenderTexture&& other)  noexcept;
	// Copy constructor - performs a shallow copy, and clears the new object's texture pointer
	RenderTexture(const RenderTexture& other);
	~RenderTexture();

	virtual void Free();

	SDL_Texture* m_pTexture = nullptr;
	int m_nX = 0;
	int m_nY = 0;
	int m_nWidth = 0;
	int m_nHeight = 0;
	float m_fAngle = 0;
	Vector2<float> m_tPivot = { 0.5f,0.5f };
	SDL_RendererFlip m_eFlip = SDL_FLIP_NONE;
};


#pragma once
#include "Texture.h"

class Game
{
public:
	Game(int nWindowWidth, int nWindowHeight);
	~Game();
	void Update(float dt);
	void Render();
private:
	const int m_nWindowWidth;
	const int m_nWindowHeight;
	Texture* m_pBall;
	float m_nVelX = 0;
	float m_nVelY = 0;
	static constexpr float GRAVITY = 1;
};


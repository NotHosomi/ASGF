#pragma once
class Game
{
public:
	Game(int nWindowWidth, int nWindowHeight);
	~Game();
	void Update(float dt);
	void Render();
};


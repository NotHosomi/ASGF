#include "Game.h"
#include "Input.h"

Game::Game(int nWindowWidth, int nWindowHeight) :
	m_nWindowWidth(nWindowWidth), m_nWindowHeight(nWindowHeight)
{
	m_pBall = new Texture("Ball.png");
	m_pBall->SetX(50);
	m_pBall->SetY(50);
}

Game::~Game()
{
}

void Game::Update(float dt)
{
	m_nVelY -= GRAVITY;
	if (Input::Instance()->GetMouseButtonDown(0))
	{
		SDL_Point mousePos = Input::Instance()->GetMousePos();
		m_nVelX += mousePos.x - (m_pBall->GetX() + m_pBall->GetWidth() / 2.0f);
		m_nVelY += mousePos.y - (m_pBall->GetY() + m_pBall->GetHeight() / 2.0f);
	}
	int newX = m_pBall->GetX() + m_nVelX * dt;
	int newY = m_pBall->GetY() + m_nVelY * dt;
	if (newX < 0)
	{
		newX = abs(newX);
		m_nVelX *= -0.9f;
	}
	else if (newX > m_nWindowWidth)
	{
		newX = m_nWindowWidth - (newX - m_nWindowWidth);
		m_nVelX *= -0.9f;
	}
	if (newY < 0)
	{
		newY = abs(newY);
		m_nVelY *= -0.9f;
	}
	else if (newY > m_nWindowWidth)
	{
		newY = m_nWindowHeight - (newY - m_nWindowHeight);
		m_nVelY *= -0.9f;
	}
	m_pBall->SetX(newX);
	m_pBall->SetY(newY);
}

void Game::Render()
{
	m_pBall->Render();
}

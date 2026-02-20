#pragma once
#include "RenderGeneric.h"
#include "Vector2.h"

class LineRender : public RenderGeneric
{
public:
	LineRender() = default;
	LineRender(Vector2<int> tStart, Vector2<int> tEnd);
	
	void Render();

	void SetStart(Vector2<int> tStart);
	Vector2<int> GetStart();
	void SetEnd(Vector2<int> tEnd);
	Vector2<int> GetEnd();


private:
	Vector2<int> m_tStart;
	Vector2<int> m_tEnd;
};


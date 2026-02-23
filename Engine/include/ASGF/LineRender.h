#pragma once
#include "RenderGeneric.h"
#include "Line.h"
#include "Vector2.h"

class LineRender : public RenderGeneric
{
public:
	LineRender() = default;
	LineRender(Line<int> tLine);
	LineRender(Vector2<int> tStart, Vector2<int> tEnd);
	
	void Render();

	void SetLine(Line<int> tLine);
	Line<int> GetLine();

	void SetStart(Vector2<int> tStart);
	Vector2<int> GetStart();
	void SetEnd(Vector2<int> tEnd);
	Vector2<int> GetEnd();


private:
	Vector2<int> m_tStart;
	Vector2<int> m_tEnd;
};


#include "include/ASGF/Grid.h"

void ASGF::GridTileBase::SetDimensions(Vector2<unsigned int> tDims)
{
	ms_tDimensions = tDims;
}

Vector2<unsigned int> ASGF::GridTileBase::GetDimensions()
{
	return ms_tDimensions;
}

void ASGF::GridTileBase::SetPosition(WorldCoord tPos)
{
	m_tPosition = tPos;
}

WorldCoord ASGF::GridTileBase::GetWorldCoord()
{
	return m_tPosition;
}

void ASGF::GridTileBase::SetGridCoord(GridCoord tCoord)
{
	m_tCoord = tCoord;
}

GridCoord ASGF::GridTileBase::GetGridCoord()
{
	return m_tCoord;
}

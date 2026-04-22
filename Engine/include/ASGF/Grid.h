#pragma once
#include <vector>
#include <functional>
#include <cassert>
#include "Coords.h"
#include "LineRender.h"

using GridCoord = Vector2<unsigned int>;

namespace ASGF
{
	class GridTileBase
	{
	public:
		static void SetDimensions(Vector2<unsigned int> tDims);
		static Vector2<unsigned int> GetDimensions();
		void SetPosition(WorldCoord tPos);
		WorldCoord GetWorldCoord();
		void SetGridCoord(GridCoord tCoord);
		GridCoord GetGridCoord();

		virtual void Update() {};
		virtual void Render() {};

	private:
		WorldCoord m_tPosition;
		GridCoord m_tCoord;
		static Vector2<unsigned int> ms_tDimensions;
	};
}

template <typename Tile_t> requires std::is_base_of_v<ASGF::GridTileBase, Tile_t>
class Grid
{
public:
	Grid(int nCols, int nRows, int nTileWidth, int nTileHeight, Vector2<int> tOriginPos, std::function<Tile_t(GridCoord)> hTileConstruction = nullptr);
	//void SetGridDims(int nCols, int nRows);
	//void SetTileDims(int nDimension);
	//void SetTileDims(int nWidth, int nHeight);

	GridCoord WorldCoordToGridCoord(WorldCoord tCoord);
	WorldCoord GridCoordToWorldCood(GridCoord tCoord);
	Tile_t* GetTile(GridCoord tCoord);
	WorldCoord GetOrigin();

	void UpdateTiles();
	void RenderGridEdge();
	void RenderGrid();
	void RenderTiles();

private:
	int WorldCoordToIndex(WorldCoord tCoord);
	int GridCoordToIndex(GridCoord tCoord);

	std::vector<Tile_t> m_vTiles;
	WorldCoord m_tOriginPos;
	int m_nRows;
	int m_nCols;

	// renderables
	std::array<LineRender, 4> m_aOutline;
	std::vector<LineRender> m_vColLines;
	std::vector<LineRender> m_vRowLines;
};

template<typename Tile_t> requires std::is_base_of_v<ASGF::GridTileBase, Tile_t>
inline Grid<Tile_t>::Grid(int nCols, int nRows, int nTileWidth, int nTileHeight, Vector2<int> tOriginPos, std::function<Tile_t(GridCoord)> hTileConstruction) :
	m_nCols(nCols), m_nRows(nRows), m_tOriginPos(tOriginPos)
{
	assert(nCols > 0 && nRows > 0 && nTileWidth > 0 && nTileHeight > 0 && "Invalid grid constructor parameters");
	m_vTiles.reserve(nCols * nRows);
	Tile_t::SetDimensions({ nTileWidth, nTileHeight });
	m_vTiles.resize(nCols * nRows);
	for (int y = 0; y < nRows; ++y)
	{
		m_vRowLines.emplace_back(
			{m_tOriginPos.x, m_tOriginPos.y + y*nTileHeight},
			{m_tOriginPos.x + nRows*nTileWidth, m_tOriginPos.y + y*nTileHeight});
		for (int x = 0; x < nCols; ++x)
		{
			if (hTileConstruction != nullptr)
			{
				m_vTiles[y * nCols + x] = hTileConstruction({ x, y });
			}
			m_vTiles[y * nCols + x].SetPosition({ x,y });
		}
	}
}

//template<typename Tile_t>
//inline void Grid<Tile_t>::SetTileDims(int nDimension)
//{
//	SetTileDims(nDimension, nDimension);
//}
//
//template<typename Tile_t>
//inline void Grid<Tile_t>::SetTileDims(int nWidth, int nHeight)
//{
//	Tile_t::SetDimensions(nWidth, nHeight);
//}

template<typename Tile_t> requires std::is_base_of_v<ASGF::GridTileBase, Tile_t>
inline GridCoord Grid<Tile_t>::WorldCoordToGridCoord(WorldCoord tCoord)
{
	tCoord -= m_tOriginPos;
	Vector2<int> tileDims = Tile_t::GetDimensions().cast<int>();
	tCoord = tCoord / tileDims;
	return tCoord.cast<unsigned int>();
}

template<typename Tile_t> requires std::is_base_of_v<ASGF::GridTileBase, Tile_t>
inline WorldCoord Grid<Tile_t>::GridCoordToWorldCood(GridCoord tCoord)
{
	WorldCoord coord = (tCoord * Tile_t::GetDimensions()).cast<int>();
	coord += m_tOriginPos;
	return coord;
}

template<typename Tile_t> requires std::is_base_of_v<ASGF::GridTileBase, Tile_t>
inline Tile_t* Grid<Tile_t>::GetTile(GridCoord tCoord)
{
	int index = GridCoordToIndex(tCoord);
	if (index > m_vTiles.size()) [[unlikely]]
	{
		return nullptr;
	}
	return m_vTiles[index];
}

template<typename Tile_t> requires std::is_base_of_v<ASGF::GridTileBase, Tile_t>
inline WorldCoord Grid<Tile_t>::GetOrigin()
{
	return m_tOriginPos;
}

template<typename Tile_t> requires std::is_base_of_v<ASGF::GridTileBase, Tile_t>
inline void Grid<Tile_t>::UpdateTiles()
{
	for (auto& tile : m_vTiles)
	{
		tile.Update();
	}
}

template<typename Tile_t> requires std::is_base_of_v<ASGF::GridTileBase, Tile_t>
inline void Grid<Tile_t>::RenderGridEdge()
{
	for (auto& line : m_aOutline)
	{
		line.Render();
	}
}

template<typename Tile_t> requires std::is_base_of_v<ASGF::GridTileBase, Tile_t>
inline void Grid<Tile_t>::RenderGrid()
{
	for (auto& line : m_vColLines)
	{
		line.Render();
	}
	for (auto line : m_vRowLines)
	{
		line.Render();
	}
}

template<typename Tile_t> requires std::is_base_of_v<ASGF::GridTileBase, Tile_t>
inline void Grid<Tile_t>::RenderTiles()
{
	for (auto& tile : m_vTiles)
	{
		tile.Render();
	}
}

template<typename Tile_t> requires std::is_base_of_v<ASGF::GridTileBase, Tile_t>
inline int Grid<Tile_t>::WorldCoordToIndex(WorldCoord tCoord)
{
	Vector2<int> gcoord = WorldCoordToGridCoord(tCoord);
	Vector2<int> tileDims = Tile_t::GetDimensions();
	gcoord.x *= tileDims.x;
	gcoord.y *= tileDims.y;
	gcoord += m_tOriginPos;
	return m_tOriginPos;
}

template<typename Tile_t> requires std::is_base_of_v<ASGF::GridTileBase, Tile_t>
inline int Grid<Tile_t>::GridCoordToIndex(GridCoord tCoord)
{
	return tCoord.x + tCoord.y * m_nCols;
}

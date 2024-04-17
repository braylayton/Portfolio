#include "Precompiled.h"
#include "Graph.h"

using namespace SWGE;
using namespace ArtificialIntelligence;

Graph::Graph()
	: mNodes{ nullptr }
	, mColumns{ 0 }
	, mRows{ 0 }
{
}
Graph::~Graph()
{
}

void Graph::Intialize(uint32_t columns, uint32_t rows)
{
	mNodes = std::make_unique<Node[]>(columns * rows);
	for (uint32_t y = 0; y < rows; ++y)
	{
		for (uint32_t x = 0; x < columns; ++x)
		{
			GetNode({ x,y }).coord = { x,y };
		}
	}
	mColumns = columns;
	mRows = rows;
}

void Graph::Clear()
{
	mNodes.reset();
	mColumns = 0;
	mRows = 0;
}

Graph::Node& Graph::GetNode(Coord coord)
{
	ASSERT(coord.x < mColumns && coord.y < mRows, "[Graph] Invalid Coordinates");
	return mNodes[coord.x + (coord.y * mColumns)];
}

bool Graph::RunBFS(Coord start, Coord end)
{
	Reset();

	mOpenList.push_back(start);
	GetNode(start).opened = true;

	bool found = false;
	while (!found && mOpenList.empty())
	{
		Coord current = mOpenList.front();
		mOpenList.pop_front();

		if (current == end)
		{
			found = true;
		}
	}

	return found;
}

bool  Graph::RunDFS(Coord start, Coord end)
{
	return false;
}
bool  Graph::RunDijkstra(Coord start, Coord end, CostFunc costFunc)
{
	return false;
}
bool  Graph::RunAStar(Coord start, Coord end, CostFunc g, HeuristicFunc h)
{
	return false;
}

std::vector<Coord> Graph::GetPath()
{
	return std::vector<Coord>();
}

void Graph::Reset()
{
	for (uint32_t i = 0; i < mColumns * mRows; ++i)
	{
		mNodes[i].opened = false;
		mNodes[i].closed = false;
		mNodes[i].parent = nullptr;
	}
	mOpenList.clear();
	mClosedList.clear();
}
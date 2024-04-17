#ifndef  INCLUDED_ARTIFICIALINTELLIGENCE_GRAPH_H
#define INCLUDED_ARTIFICIALINTELLIGENCE_GRAPH_H

namespace SWGE {
namespace ArtificialIntelligence {

	struct Coord 
	{
		uint32_t x{ 0 }, y{ 0 };
		bool operator==(const Coord& other) const
		{
			return x == other.x && y == other.y;
		}
	};

	enum Direction
	{

		//count
	};

	class Graph 
	{
	public:
		struct Node
		{
			Coord coord;
			bool blocked{ false };

			Node* parent{ nullptr };
			float g{ 0.0f }, h{ 0.0f };
			bool opened{ false };
			bool closed{ false };
		};

		using CostFunc = std::function<float(Coord, Coord)>;
		using HeuristicFunc = std::function<float(Coord)>;

		Graph();
		~Graph();

		void Intialize(uint32_t columns, uint32_t rows);
		void Clear();

		Node& GetNode(Coord coord);

		bool RunBFS(Coord start, Coord end);
		bool RunDFS(Coord start, Coord end);
		bool RunDijkstra(Coord start, Coord end, CostFunc costFunc);
		bool RunAStar(Coord start, Coord end, CostFunc g, HeuristicFunc h);

		std::vector<Coord> GetPath();
		std::list<Node*> GetClosedList();

		uint32_t GetColumns() const { return mColumns;}
		uint32_t GetRows() const { return mRows; }
		
	private:
		void Reset();

		std::unique_ptr<Node[]> mNodes;
		uint32_t mColumns;
		uint32_t mRows;
		std::list<Coord> mOpenList;
		std::list<Coord> mClosedList;

	};
}
}


#endif // ! INCLUDED_ARTIFICIALINTELLIGENCE_GRAPH_H


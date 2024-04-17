#pragma once

#include <GameEngine/Inc/GameEngine.h>

class QuadTree
{
public:
	QuadTree() = default;

	void Initialize(SWGE::Graphics::Mesh* mesh, uint32_t levels);

	struct Node
	{
		SWGE::Math::AABB aabb;
		Node* children[4];
		bool isLeaf{false};
		std::vector<uint32_t> indicies;

	};


	using Visitor = std::function<void(Node*)>;

	void GenerateNode(std::unique_ptr<Node>& node, SWGE::Math::AABB aabb, uint32_t levels);
	void Visit(Visitor& visitor);
	bool Intersect(SWGE::Math::Ray ray, float& distance) const;


private:

	enum Quadrant {BL, BR, TL, TR};

	void GenerateNodeRecursive(std::unique_ptr<Node>& node, SWGE::Math::AABB aabb, uint32_t levels);
	void VisitRecursive(Node* node, Visitor& visitor);
	bool IntersectRecursive(Node* node, SWGE::Math::Ray ray, float& distance);

	SWGE::Graphics::Mesh* mMesh;
	std::unique_ptr<Node> mRoot;

};
#include "QuadTree.h"

using namespace SWGE;

void QuadTree::Initialize(SWGE::Graphics::Mesh* mesh, uint32_t levels)
{
	Math::Vector3 min = mesh->GetVertex(0).position;
	Math::Vector3 max = mesh->GetVertex(0).position;
	for (uint32_t v = 0; v < mesh->GetVertexCount(); ++v)
	{
		const auto& vertex = mesh->GetVertex(v);
		min.x = Math::Min(min.x, vertex.position.x);
		min.y = Math::Min(min.y, vertex.position.y);
		min.z = Math::Min(min.z, vertex.position.z);

		max.x = Math::Min(max.x, vertex.position.x);
		max.y = Math::Min(max.y, vertex.position.y);
		max.z = Math::Min(max.z, vertex.position.z);
	}
	Math::AABB bound;
	bound.center = (min + max) * 0.5f;
	bound.extend = (max - min) * 0.5f;
	GenerateNode(mRoot, bound, levels);


// recursion for homework
// level--
// when level-- = 0| node then = leaf node
// index buffer go three at a time (triangle)
// Why should be really big and really small (aabb) 1500y -1500y so ray cast wont fail

}void QuadTree::Visit(Visitor& visitor)
{
	VisitRecursive(mRoot.get(), visitor);
}
//
//bool QuadTree::Intersect(Math::Ray ray, float& distance) const
//{
//	distance = std::numeric_limits<float>::max();
//	//return IntersectRecursive(mRoot.get)
//}


void QuadTree::GenerateNode(std::unique_ptr<Node>& node, SWGE::Math::AABB aabb, uint32_t levels)
{
	// do recurision here
	node = std::make_unique<Node>();
	node->aabb = aabb;
	Math::AABB arrayAABB[4];

	if (levels > 1)
	{
		/*

		GenerateNode(node->children[0],);
		GenerateNode(node->children[1],);
		GenerateNode(node->children[2],);
		GenerateNode(node->children[3],);
		*/

		//do recurssion
	}
	else
	{
		node->isLeaf = true;
	}

}

//void QuadTree::VisitRecursive(Node* node, )
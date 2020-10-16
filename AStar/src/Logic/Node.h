#pragma once
#include <vector>

class Node
{
public:
	bool m_IsObstacle;
	bool m_Visited;
	// Vector3 
	int m_PosX;
	int m_PosY;

	int m_GCost = 0; // distance from starting node
	int m_HCost = 0; // opposite of G cost, how far is this node from the end node
	int m_FCost = 0; // G cost + H cost

	char mark;

	Node* m_Parent = nullptr;
	//std::vector<Node> m_Neighbours;

	// Algorithm will choose the node with the lowest F cost. If the algorithm checked FCost, mark it as closed.
	// if same FCost - check the nodes with lowest H cost (which one is closest to the end node)
	// if F cost keeps increasing, it means you are not going through a straight path, it will start exploring other paths

	Node(int posX, int posY, bool isObstacle, bool visited = false)
		: m_PosX(posX), m_PosY(posY), m_IsObstacle(isObstacle), m_Visited(visited)
	{}

	void CalculateFCost(int& fCost);
	void CalculateGCost(Node startNode, int& gCost);
	int CalculateHCost(Node endNode);
	int GetDistance(Node nodeA, Node nodeB);

	std::vector<Node> GetNeighbours();
	void Print() const;

	friend bool operator== (const Node& lhs, const Node& rhs);
	friend bool operator!= (const Node& lhs, const Node& rhs);
	Node() = default;
};


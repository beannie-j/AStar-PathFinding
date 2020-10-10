#include "Node.h"

void Node::CalculateFCost(int& fCost)
{
	fCost = m_GCost + m_HCost;
}

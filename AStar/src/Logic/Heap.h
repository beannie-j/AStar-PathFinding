#pragma once
#include <vector>
#include "Node.h"

struct HeapItem {
	int index = 0;
	Node node;

	HeapItem(Node _node)
	{
		node = _node;
	}
};

class Heap
{
public:
	std::vector<HeapItem> items;
	int count = 0;

	Heap() = default;

	void Add(HeapItem item);
	void ShiftUp(HeapItem& item);
	void ShiftDown(HeapItem& item);
	void Swap(HeapItem& itemA, HeapItem& itemB);
	int Compare(HeapItem itemA, HeapItem itemB);
	bool Contains(Node node);
	HeapItem RemoveFirst();
};

void Heap::Add(HeapItem item)
{
	item.index = count;
	items[count++] = item;
	ShiftUp(item);
}

void Heap::ShiftUp(HeapItem& item)
{
	int parentIndex = (item.index - 1) / 2;

	HeapItem parentItem = items.at(parentIndex);
	while (Compare(parentItem, item) > 0) // item needs to go up.
	{
		Swap(parentItem, item);
		parentIndex = (item.index - 1) / 2;
	}
}

inline void Heap::ShiftDown(HeapItem& item)
{
	while (true) {
		int childIndexLeft = item.index * 2 + 1;
		int childIndexRight = item.index * 2 + 2;
		int swapIndex = 0;

		if (childIndexLeft < count) {
			swapIndex = childIndexLeft;

			if (childIndexRight < count) {
				if (Compare(items[childIndexLeft], items[childIndexRight]) < 0) {
					swapIndex = childIndexRight;
				}
			}

			if (Compare(item, items[swapIndex]) < 0) {
				Swap(item, items[swapIndex]);
			}
			else {
				return;
			}

		}
		else {
			return;
		}
	}
}

void Heap::Swap(HeapItem& itemA, HeapItem& itemB)
{
	HeapItem temp = itemA; 
	itemA = itemB;
	itemB = temp;
}

int Heap::Compare(HeapItem itemA, HeapItem itemB)
{
	if (itemA.node.m_FCost > itemB.node.m_FCost) return 1;
	else if (itemA.node.m_FCost == itemB.node.m_FCost) return 0;
	else return -1;
}

inline bool Heap::Contains(Node node)
{
}

inline HeapItem Heap::RemoveFirst()
{
	HeapItem firstItem = items[0];
	count--;
	items[0] = items[count];
	items[0].index = 0;
	ShiftDown(items[0]);

	return firstItem;
}

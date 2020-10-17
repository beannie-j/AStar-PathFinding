#pragma once
#include <vector>
template <typename T>
struct HeapItem {
	int index = 0;
	T item;
};

template <typename T>
class Heap
{
public:
	std::vector<HeapItem> items;
	int count;

	Heap() = default;

	void Add(HeapItem<T> item);
	void Balance(HeapItem<T> item);
};

template<typename T>
inline void Heap<T>::Add(HeapItem<T> item)
{
	item.index = count;
	items[count++] = item;
	Balance(item);
}

template<typename T>
inline void Heap<T>::Balance(HeapItem<T> item)
{
}
#pragma once
template<typename T>
struct Node
{
	T data;
	Node* next;
	Node* prev;

	Node(T data)
	{
		this->data = data;
		next = nullptr;
		prev = nullptr;
	}

};
#pragma once
#include "Node.h"
#include "Coordinates.h"

class Route
{
private:


	//Color color;

public:

	Node<Coordinates>* head;
	Node<Coordinates>* tail;
	int size;

	Route()
	{
		this->head = nullptr;
		this->tail = nullptr;
		this->size = 0;
	}

	void addNode(Coordinates data)
	{
		Node<Coordinates>* node = new Node<Coordinates>(data);
		if (this->head == nullptr)
		{
			this->head = node;
			this->tail = node;
		}
		else
		{
			this->tail->next = node;
			node->prev = this->tail;
			this->tail = node;
		}
		this->size++;
	}
};
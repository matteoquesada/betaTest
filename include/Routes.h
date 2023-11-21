#pragma once
#include "Route.h"
#include "Node.h"
#include "Coordinates.h"

class Routes {
public:

	Node<Route>* head;
	int size;

	Routes()
	{
		this->head = nullptr;
		this->size = 0;
	}

	void addRoute(Route route)
	{
		Node<Route>* node = new Node<Route>(route);
		if (this->head == nullptr)
		{
			this->head = node;
		}
		else
		{
			Node<Route>* temp = this->head;
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
			temp->next = node;
		}
		this->size++;
	}
};
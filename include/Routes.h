#pragma once
#include "Route.h"
#include "Node.h"
#include "Coordinates.h"

#include <iostream>

class Routes {
public:

	Node<Route>* head;
	int size;

	Routes()
	{
		head = nullptr;
		size = 0;
	}

	void addRoute(Route route)
	{
		if (head == nullptr) { std::cout << "head is null" << std::endl; }
		Node<Route>* node = new Node<Route>(route);
		if (head == nullptr)
		{
			head = node;
		}
		else
		{
			Node<Route>* temp = head;
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
			temp->next = node;
		}
		size++;
	}

	void draw(sf::RenderWindow& window)
	{
		Node<Route>* temp = head;
		while (temp != nullptr)
		{
			temp->data.draw(window);
			temp = temp->next;
		}
	}
};
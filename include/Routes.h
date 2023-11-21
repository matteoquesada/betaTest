#pragma once
#include "Route.h"
#include "Node.h"
#include "Coordinates.h"

#include <iostream>
using namespace std;

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
		if (head == nullptr) {
			head = new Node<Route>(route);
			size++;
		}
		else{
			Node<Route>* temp = head;
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
			temp->next = new Node<Route>(route);
			size++;
		}

		/*if (head == nullptr) { std::cout << "head is null" << std::endl; }
		Node<Route>* node = new Node<Route>(route);
		size++;
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
		size++;*/
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


	void deleteRoute(int index)
	{
		
		if (index == 0)
		{
			Node<Route>* temp = head;
			head = head->next;
			delete temp;
			size--;
		}
		else
		{
			Node<Route>* temp = head;
			for (int i = 0; i < index - 1; i++)
			{
				temp = temp->next;
			}
			Node<Route>* temp2 = temp->next;
			temp->next = temp2->next;
			delete temp2;
			size--;
		}



	}
};
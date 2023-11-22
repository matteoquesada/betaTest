#pragma once
#include "Node.h"
#include "Coordinates.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class Route
{
public:

	// PUBLIC TO ALLOW EASY ACCESS ON THE NODES AND VARIABLES
	Node<Coordinates>* head;
	Node<Coordinates>* tail;
	Color color;
	bool isDrawn;
	int size;

	// DEFAULT CONSTRUCTOR
	Route()
	{
		color = Color::White; // DEFAULT COLOR IS WHITE
		isDrawn = true;
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	// ADDS A NODE TO THE END OF THE ROUTE
	void addNode(Coordinates data)
	{
		Node<Coordinates>* node = new Node<Coordinates>(data);
		if (head == nullptr)
		{
			head = node;
			tail = node;
		}
		else
		{
			tail->next = node;
			node->prev = tail;
			tail = node;
		}
		size++;
	}

	// CHECK IF THE NODE IS WITHING 10 PIXELS OF ANOTHER NODE INSIDE THE ROUTE
	void deleteNode(Coordinates data)
	{
	Node<Coordinates>* current = head;
		while (current != nullptr) {
			if (current->data.getX() > data.getX() - 10 && current->data.getX() < data.getX() + 10 &&
				current->data.getY() > data.getY() - 10 && current->data.getY() < data.getY() + 10) 
			{
				if (current == head) {
					head = head->next;
					head->prev = nullptr;
				}
				else if (current == tail) {
					tail = tail->prev;
					tail->next = nullptr;
				}
				else {
					current->prev->next = current->next;
					current->next->prev = current->prev;
				}
				size--;
				return; // IF THE NODE IS FOUND, RETURN
			}
			current = current->next; // IF THE NODE IS NOT FOUND, CONTINUE CYCLING THROUGH THE LIST
		}

	}

	// CHANGE THE COLOR OF THE ROUTE
	void changeColor(Color color)
	{
		this->color = color;
	}

	// DRAW THE ROUTE ITSELF
	// CYCLES THROUGH THE NODES AND DRAWS A LINE BETWEEN THEM
	// THE LINE CONSISTS OF TWO VERTICES WITH THE COORDINATES OF THE NODES
	void draw(RenderWindow& window)
	{
		if (!isDrawn) return;

		Node<Coordinates>* current = head;
		while (current != nullptr) {

			// DRAWING THE NODE ITSELF WITH A BLACK BORDER
			CircleShape point(5);
			point.setFillColor(color);
			point.setPosition(current->data.getX() - 3, current->data.getY() - 3);

			CircleShape border(6);
			border.setFillColor(Color::Black);
			border.setPosition(current->data.getX() - 3, current->data.getY() - 3);

			// DRAWING THE LINE BETWEEN NODES
			if (current->next != nullptr) {
				Vertex line[] = // ARRAY OF VERTICES
				{
					Vertex(Vector2f(current->data.getX(), current->data.getY())), // FIRST VERTEX
					Vertex(Vector2f(current->next->data.getX(), current->next->data.getY())) // SECOND VERTEX
				};
				window.draw(line, 2, Lines); // DRAW THE LINE WITH THE TWO VERTICES AND THE VERTEX COUNT
			}
			window.draw(border);
			window.draw(point);
			current = current->next;
		}
	}
};
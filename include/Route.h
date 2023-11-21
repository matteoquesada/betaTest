#pragma once
#include "Node.h"
#include "Coordinates.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class Route
{
private:

public:

	Node<Coordinates>* head;
	Node<Coordinates>* tail;
	int size;

	Color color;

	bool isDrawn;

	Route()
	{
		isDrawn = true;
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

	void draw(RenderWindow& window)
	{
		if (!isDrawn) return;

		Node<Coordinates>* current = head;
		while (current != nullptr) {

			// DRAWING THE NODE ITSELF WITH A BLACK BORDER
			CircleShape circle(5);
			circle.setFillColor(color);
			circle.setPosition(current->data.getX() - 3, current->data.getY() - 3);

			CircleShape border(6);
			border.setFillColor(Color::Black);
			border.setPosition(current->data.getX() - 3, current->data.getY() - 3);

			// DRAWING THE LINE BETWEEN NODES
			if (current->next != nullptr) {
				Vertex line[] =
				{
					Vertex(Vector2f(current->data.getX(), current->data.getY())),
					Vertex(Vector2f(current->next->data.getX(), current->next->data.getY()))
				};
				window.draw(line, 2, Lines);
			}
			window.draw(border);
			window.draw(circle);
			current = current->next;
		}
	}
};
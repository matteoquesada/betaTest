#pragma once
#include "Routes.h"
#include "Node.h"
#include "Coordinates.h"
#include "Route.h"

#include <SFML/Graphics.hpp>
using namespace sf;


class MapHandler
{

	Routes allRoutes;

	public:

		MapHandler()
		{
			this->allRoutes = Routes();
		}

		void addRoute(Route route)
		{
			this->allRoutes.addRoute(route);
		}

		void draw(RenderWindow& window)
		{
			Node<Route>* temp = this->allRoutes.head;
			while (temp != nullptr)
			{
				Node<Coordinates>* temp2 = temp->data.head;
				while (temp2 != nullptr)
				{
					CircleShape circle(5);
					circle.setFillColor(Color::Red);
					circle.setPosition(temp2->data.getX(), temp2->data.getY());
					window.draw(circle);
					temp2 = temp2->next;
				}
				temp = temp->next;
			}
		}

		








};
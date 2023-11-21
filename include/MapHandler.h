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

		int selectedRoute;

		bool deleteMode;

		MapHandler()
		{
			this->allRoutes = Routes();
			selectedRoute = -1;
			deleteMode = false;
		}

		void addRoute(Route route)
		{
			
			this->allRoutes.addRoute(route);
			selectedRoute = this->allRoutes.size;
		}

		// ADDS A POINT TO THE SELECTED ROUTE TO THE END OF THE ROUTE ITSELF
		void addPointToRoute(Coordinates point)
		{
			if (this->selectedRoute != -1)
			{
				Node<Route>* temp = this->allRoutes.head;
				for (int i = 0; i < this->selectedRoute; i++)
				{
					temp = temp->next;
				}
				temp->data.addNode(point);
			}
			
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
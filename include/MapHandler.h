#pragma once
#include "Routes.h"
#include "Node.h"
#include "Coordinates.h"
#include "Route.h"

#include <SFML/Graphics.hpp>
using namespace sf;

#include <iostream>
using namespace std;


class MapHandler
{

	Routes allRoutes;

	public:

		int selectedRoute;

		bool deleteMode;

		MapHandler()
		{
			allRoutes = Routes();
			selectedRoute = -1;
			deleteMode = false;
		}

		void addRoute(Route route)
		{
			
			allRoutes.addRoute(route); 
			selectedRoute = allRoutes.size;
		}

		// ADDS A POINT TO THE SELECTED ROUTE TO THE END OF THE ROUTE ITSELF
		// BASED ON THE SELECTED ROUTE IT CYCLES UNTIL IT FINDS THE SELECTED ROUTE, THEN IT ADDS THE POINT TO THE END OF THE ROUTE
		void addPointToRoute(Coordinates point)
		{
			Node<Route>* temp = allRoutes.head;
			for (int i = 0; i < selectedRoute - 1; i++)
			{
				temp = temp->next;
			}
			temp->data.addNode(point);

			
		}

		// CALLS THE DRAW METHOD ON CLASS ROUTES, WHICH CALLS INIDIVIDUAL DRAW METHODS ON EACH ROUTE
		void draw(RenderWindow& window)
		{
			allRoutes.draw(window);
		}



		








};
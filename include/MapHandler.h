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
			allRoutes = Routes(); // INITIALIZES WITH 0 SIZE
			selectedRoute = -1; // NO ROUTE SELECTED AT THE BEGINNING
			deleteMode = false;
		}

		void addRoute(Route route)
		{
			
			allRoutes.addRoute(route);  // SIZE BECOMES 1
			selectedRoute = allRoutes.size; // SELECTED ROUTE BECOMES THE ONLY ROUTE
		}

		void deleteRoute()
		{
			allRoutes.deleteRoute(selectedRoute);
			selectedRoute = 0;
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

		void changeColor(Color color)
		{
			Node<Route>* temp = allRoutes.head;
			for (int i = 0; i < selectedRoute - 1; i++)
			{
				temp = temp->next;
			}
			temp->data.changeColor(color);
		}

		// CHANGE SELECTED ROUTE BY CYCLING THROUGH THE LIST OF ROUTES
		void changeSelectedRoute()
		{
			if (selectedRoute < allRoutes.size) {
				selectedRoute++;
			}
			else {
				selectedRoute = 1;
			}

		}

		// CHANGE THE DELETE MODE
		void changeDeleteMode()
		{
			deleteMode = !deleteMode;
		}

		// DELETE THE SELECTED POINT FROM THE SELECTED ROUTE WITHIN A RADIUS OF 10 PIXELS
		void deletePointFromRoute(Coordinates point)
		{
			Node<Route>* temp = allRoutes.head;
			for (int i = 0; i < selectedRoute - 1; i++)
			{
				temp = temp->next;
			}
			temp->data.deleteNode(point);
			
		}

		void showHide()
		{
			Node<Route>* temp = allRoutes.head;
			for (int i = 0; i < selectedRoute - 1; i++)
			{
				temp = temp->next;
			}
			temp->data.isDrawn = !temp->data.isDrawn;
		}

		void save()
		{
			allRoutes.save();
		}

		void load()
		{
			allRoutes.load();
		}

		



		








};
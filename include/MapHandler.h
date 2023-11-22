#pragma once
#include "Routes.h"
#include "Node.h"



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
			deleteMode = false; // DELETE MODE IS OFF AT THE BEGINNING
		}

		void addRoute(Route route)
		{
			
			allRoutes.addRoute(route);  // SIZE BECOMES 1
			selectedRoute = allRoutes.size; // SELECTED ROUTE BECOMES THE ONLY ROUTE
		}

		// DELETES THE SELECTED ROUTE AND SELECTS THE LAST ROUTE IN THE LIST
		// ALLOWS TO QUICKLY DELETE ROUTES IN CHAIN
		void deleteRoute()
		{
			allRoutes.deleteRoute(selectedRoute);
			if(allRoutes.size == 0) {
				selectedRoute = -1;
			}
			else if (selectedRoute > allRoutes.size) {
				selectedRoute = allRoutes.size;
			}
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
			if (selectedRoute < allRoutes.size && selectedRoute != -1) {
				selectedRoute++;
			}
			else if (selectedRoute == -1) {
				selectedRoute = allRoutes.size;
				cout << "AAASelected route: " << selectedRoute << endl;
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
			ofstream file("userdata/routes.txt");
			if (!file.is_open()) {
				cerr << "ERROR GARRAFAL: SE QUEMARON LOS FRIJOLES." << endl;
				return;
			}

			Node<Route>* temp = allRoutes.head; // MAKE A TEMPORARY POINTER TO THE HEAD OF THE LIST
			Node<Coordinates>* subTemp = nullptr; // MAKE A TEMPORARY POINTER TO THE HEAD OF THE SUB-LIST

			while (temp != nullptr) { // ITERATE THROUGH THE ROUTES

				file << "<Route>" << endl;
				file << "Color: ";
				file << static_cast<int>(temp->data.color.r) << " " // SAVE THE R CHANNEL INTO THE FILE
					<< static_cast<int>(temp->data.color.g) << " " // SAVE THE G CHANNEL INTO THE FILE
					<< static_cast<int>(temp->data.color.b) << std::endl; // SAVE THE B CHANNEL INTO THE FILE

				subTemp = temp->data.head; // MAKE A TEMPORARY POINTER TO THE HEAD OF THE SUB-LIST

				while (subTemp != nullptr) { // ITERATE THROUGH THE SUB-LIST
					file << subTemp->data.getX() << " " << subTemp->data.getY() << endl; // SAVE THE COORDINATES INTO THE FILE
					subTemp = subTemp->next; // MOVE TO THE NEXT NODE
				}
				file << "</>" << endl; // END OF THE ROUTE
				temp = temp->next; // MOVE TO THE NEXT ROUTE
			}
		}

		void load()
		{
			Node<Route>* ptrToHead = allRoutes.head;
			ifstream file("userdata/routes.txt");
			if (!file.is_open()) {
				cerr << "ERROR GARRAFAL: SE QUEMARON LOS FRIJOLES." << endl;
				return;
			}

			string line;
			while (getline(file, line)) {
				cout << line << endl;
				if (line == "<Route>") {
					// Start a new route
					Route route;
					getline(file, line); // Skip the "<Route>" line

					int r, g, b;
					line.erase(0, 7); // Remove the "Color: " part

					r = stoi(line.substr(0, line.find(" "))); // Get the R channel
					line.erase(0, line.find(" ") + 1); // Remove the R channel
					g = stoi(line.substr(0, line.find(" "))); // Get the G channel
					line.erase(0, line.find(" ") + 1); // Remove the G channel
					b = stoi(line.substr(0, line.find(" "))); // Get the B channel
					line.erase(0, line.find(" ") + 1); // Remove the B channel
					cout << "Found R: " << r << " Found G: " << g << " Found B: " << b << endl;

					Color color(r, g, b); // CREATE THE COLOR BASED ON THE VALUES WE JUST GOT
					route.color = color; // ASSIGN THE COLOR TO THE ROUTE

					// Now we need to get the coordinates
					while (getline(file, line)) {
						if (line == "</>") {
							// End of the route
							break;
						}
						else {
							// Add the coordinates to the route
							int x, y;
							x = stoi(line.substr(0, line.find(" "))); // Get the X coordinate
							line.erase(0, line.find(" ") + 1); // Remove the X coordinate
							y = stoi(line.substr(0, line.find(" "))); // Get the Y coordinate
							line.erase(0, line.find(" ") + 1); // Remove the Y coordinate
							cout << "Found X: " << x << " Found Y: " << y << endl;
							Coordinates coordinates(x, y); // CREATE THE COORDINATES BASED ON THE VALUES WE JUST GOT
							route.addNode(coordinates); // ADD THE NODE TO THE ROUTE
							// now I think we can integrate that route easly into the list
							



						}

						
					}

					allRoutes.addRoute(route);
					cout << "Route added" << endl;
					cout << "at index: " << allRoutes.size << endl;
				}
			}
			cout << selectedRoute << endl;
			selectedRoute = allRoutes.size - 1;
		}
};
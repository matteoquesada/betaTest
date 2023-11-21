#pragma once
#include "Route.h"
#include "Node.h"
#include "Coordinates.h"
#include <fstream>
#include <sstream>
#include <string>


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
	}

	void draw(RenderWindow& window)
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
        if (index == 1)
        {
            cout << "Deleting first route" << endl;
            if (head != nullptr)
            {
                Node<Route>* temp = head;
                head = head->next;
                delete temp;
                size--;
            }
            else
            {
                cout << "List is empty" << endl;
            }
        }
        else if (index > 1 && index <= size)
        {
            cout << "Deleting route at index " << index << endl;
            Node<Route>* temp = head;
            for (int i = 0; i < index - 2; i++)
            {
                if (temp == nullptr || temp->next == nullptr)
                {
                    cout << "ERROR: Invalid index or list traversal issue" << endl;
                    return;
                }
                temp = temp->next;
            }

            Node<Route>* nodeToDelete = temp->next;
            temp->next = nodeToDelete->next;
            delete nodeToDelete;

        }
        else
        {
            cout << "INVALID INDEX" << endl;
        }
    }


    void save() {

        ofstream file("userdata/routes.txt");
        if (!file.is_open()) {
            cerr << "ERROR GARRAFAL: SE QUEMARON LOS FRIJOLES." << endl;
            return;
        }

        Node<Route>* temp = head; // MAKE A TEMPORARY POINTER TO THE HEAD OF THE LIST
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

    void load(Node<Route>* routeListPTR) {
        ifstream file("userdata/routes.txt");
        if (!file.is_open()) {
            cerr << "ERROR GARRAFAL: SE QUEMARON LOS FRIJOLES." << endl;
            return;
        }

        string xxx;
        while (getline(file, xxx)) {
            if (xxx == "<Route>") {
                // Start a new route
                Route route;
                cout << "Antes del getline skipeo: " << xxx << endl;
                getline(file, xxx); // Skip the "<Route>" line
                cout << "Despues del getline skipeo: "<< xxx << endl;
                // xxx should look like "Color: 255 255 255"
                // We need to split the string into 3 substrings and convert them to integers, then assign them to the color and create a new route easy peasy
                // xxx is line
                 int r, g, b;
                 xxx.erase(0, 7); // Remove the "Color: " part
                 r = stoi(xxx.substr(0, xxx.find(" "))); // Get the R channel
                 xxx.erase(0, xxx.find(" ") + 1); // Remove the R channel
                 g = stoi(xxx.substr(0, xxx.find(" "))); // Get the G channel
                 xxx.erase(0, xxx.find(" ") + 1); // Remove the G channel
                 b = stoi(xxx.substr(0, xxx.find(" "))); // Get the B channel
                 xxx.erase(0, xxx.find(" ") + 1); // Remove the B channel
                 cout << "Found R: " << r << " Found G: " << g << " Found B: " << b << endl;

                 Color color(r, g, b); // CREATE THE COLOR BASED ON THE VALUES WE JUST GOT
                 route.color = color; // ASSIGN THE COLOR TO THE ROUTE

                // Now we need to get the coordinates
                    while (getline(file, xxx)) {
					if (xxx == "</>") {
						// End of the route
						break;
					}
					else {
						// Add the coordinates to the route
						int x, y;
						x = stoi(xxx.substr(0, xxx.find(" "))); // Get the X coordinate
						xxx.erase(0, xxx.find(" ") + 1); // Remove the X coordinate
						y = stoi(xxx.substr(0, xxx.find(" "))); // Get the Y coordinate
						xxx.erase(0, xxx.find(" ") + 1); // Remove the Y coordinate
						cout << "Found X: " << x << " Found Y: " << y << endl;
						Coordinates coordinates(x, y); // CREATE THE COORDINATES BASED ON THE VALUES WE JUST GOT
                        route.addNode(coordinates); // ADD THE NODE TO THE ROUTE
						// the thing is, how do we add that route to the list?
                        // now we have a pointer to the first route in the list
                        // we need to iterate through the list until we find the last route
                        // then we add the new route to the end of the list
						Node<Route>* temp = routeListPTR;
						while (temp->next != nullptr) {
							temp = temp->next;
						}
						temp->next = new Node<Route>(route);
						routeListPTR->data.size++;

					}
                    
				}


                
                // Add the new route to the list
            }
        }
    }

};
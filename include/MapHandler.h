#pragma once
#include "Routes.h"
#include "Node.h"

#include <SFML/Graphics.hpp>
using namespace sf;

#include <iostream>
using namespace std;

class MapHandler {
private:
    Routes allRoutes;

public:
    int selectedRoute;
    bool deleteMode;

    MapHandler() {
        allRoutes = Routes(); // INITIALIZES WITH 0 SIZE
        selectedRoute = -1; // NO ROUTE SELECTED AT THE BEGINNING
        deleteMode = false; // DELETE MODE IS OFF AT THE BEGINNING
    }

    void addRoute(Route route) {
        allRoutes.addRoute(route);  // SIZE BECOMES 1
        selectedRoute = allRoutes.size; // SELECTED ROUTE BECOMES THE ONLY ROUTE
    }

    // DELETES THE SELECTED ROUTE AND SELECTS THE LAST ROUTE IN THE LIST
    // ALLOWS TO QUICKLY DELETE ROUTES IN CHAIN
    void deleteRoute() {
        allRoutes.deleteRoute(selectedRoute);
        if (allRoutes.size == 0) selectedRoute = -1;
        else if (selectedRoute > allRoutes.size) selectedRoute = allRoutes.size;
    }

    // ADDS A POINT TO THE SELECTED ROUTE TO THE END OF THE ROUTE ITSELF
    // BASED ON THE SELECTED ROUTE IT CYCLES UNTIL IT FINDS THE SELECTED ROUTE, THEN IT ADDS THE POINT TO THE END OF THE ROUTE
    void addPoint(Coordinates point) {
        Node<Route>* temp = allRoutes.head;
        for (int i = 0; i < selectedRoute - 1; i++) temp = temp->next;
        temp->data.addNode(point);
    }

    // CALLS THE DRAW METHOD ON CLASS ROUTES, WHICH CALLS INIDIVIDUAL DRAW METHODS ON EACH ROUTE
    void draw(RenderWindow& window) {
        allRoutes.draw(window);
    }

    void changeColor(Color color) {
        if(selectedRoute == -1) return;
        Node<Route>* temp = allRoutes.head;
        for (int i = 0; i < selectedRoute - 1; i++) temp = temp->next;
        temp->data.changeColor(color);
    }

    // CHANGE SELECTED ROUTE BY CYCLING THROUGH THE LIST OF ROUTES
    void switchRoute() {
        if (selectedRoute < allRoutes.size && selectedRoute != -1) selectedRoute++;
        else if (selectedRoute == -1) {
            selectedRoute = allRoutes.size;
            cout << "AAASelected route: " << selectedRoute << endl;
        }
        else selectedRoute = 1;
    }

    // CHANGE THE DELETE MODE
    void toggleDelete() {
        deleteMode = !deleteMode;
    }

    // DELETE THE SELECTED POINT FROM THE SELECTED ROUTE WITHIN A RADIUS OF 10 PIXELS
    void deletePoint(Coordinates point) {
        Node<Route>* temp = allRoutes.head;
        for (int i = 0; i < selectedRoute - 1; i++) temp = temp->next;
        temp->data.deleteNode(point);
    }

    // TOGGLE THE DRAWING OF THE SELECTED ROUTE
    void showHide() {
        if(selectedRoute == -1) return; // IF NO ROUTE IS SELECTED
        Node<Route>* temp = allRoutes.head;
        for (int i = 0; i < selectedRoute - 1; i++) temp = temp->next;
        temp->data.isDrawn = !temp->data.isDrawn;
    }

    // SAVE THE ROUTES TO A FILE
    // FORMAT:
    // <Route>
    // Color: 255 255 255
    // 100 100
    // 200 200
    // 300 300
    // </>
    void save() {
        ofstream file("userdata/routes.txt");
        if (!file.is_open()) {
            cerr << "ERROR GARRAFAL: SE QUEMARON LOS FRIJOLES." << endl;
            return;
        }

        Node<Route>* temp = allRoutes.head;
        Node<Coordinates>* subTemp = nullptr;

        while (temp != nullptr) {
            file << "<Route>" << endl; // START OF ROUTE
            file << "Color: ";
            file << static_cast<int>(temp->data.color.r) << " " // CASTING TO INT TO AVOID PRINTING ASCII VALUES
                << static_cast<int>(temp->data.color.g) << " "
                << static_cast<int>(temp->data.color.b) << std::endl; 

            subTemp = temp->data.head; // SUBTEMP IS A POINTER TO THE HEAD OF THE LIST OF COORDINATES

            while (subTemp != nullptr) {
                file << subTemp->data.getX() << " " << subTemp->data.getY() << endl; // PRINTS THE X AND Y VALUES OF THE COORDINATES
                subTemp = subTemp->next;
            }
            file << "</>" << endl; // END OF ROUTE
            temp = temp->next;
        }
    }

    // LOAD THE ROUTES FROM A FILE FROM THE SAME FORMAT AS THE SAVE METHOD
    void load() {
        Node<Route>* ptrToHead = allRoutes.head;
        ifstream file("userdata/routes.txt");
        if (!file.is_open()) {
            cerr << "ERROR GARRAFAL: SE QUEMARON LOS FRIJOLES." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line == "<Route>") { // START OF ROUTE
                Route route;
                getline(file, line);

                int r, g, b;
                line.erase(0, 7);

                // ALLOWS TO SET CUSTOM COLORS IF WANTED
                r = stoi(line.substr(0, line.find(" "))); // R CHANNEL OF THE COLOR
                line.erase(0, line.find(" ") + 1);
                g = stoi(line.substr(0, line.find(" "))); // G CHANNEL OF THE COLOR
                line.erase(0, line.find(" ") + 1);
                b = stoi(line.substr(0, line.find(" "))); // B CHANNEL OF THE COLOR
                line.erase(0, line.find(" ") + 1);

                Color color(r, g, b);
                route.color = color; // SETS THE COLOR OF THE ROUTE

                while (getline(file, line)) {
                    if (line == "</>") break; // END OF ROUTE
                    else {
                        int x, y;
                        x = stoi(line.substr(0, line.find(" "))); // X COORDINATE
                        line.erase(0, line.find(" ") + 1);
                        y = stoi(line.substr(0, line.find(" "))); // Y COORDINATE
                        line.erase(0, line.find(" ") + 1);
                        Coordinates coordinates(x, y); // CREATES A NEW COORDINATE
                        route.addNode(coordinates); // ADDS THE COORDINATE TO THE ROUTE
                    }
                }
                allRoutes.addRoute(route); // ADDS THE ROUTE TO THE LIST OF ROUTES
            }
        }
        selectedRoute = allRoutes.size; // SELECTS THE LAST ROUTE IN THE LIST
    }
};

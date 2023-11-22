#pragma once

#include "Route.h"
#include <fstream>
#include <iostream>

using namespace std;

class Routes {
public:
    Node<Route>* head;
    int size;

    // CONSTRUCTOR THAT INITIALIZES THE LIST WITH 0 SIZE
    Routes() : head(nullptr), size(0) {}

    // DESTRUCTOR THAT CLEARS THE LIST AND RELEASES MEMORY
    ~Routes() {
        clear();
    }

    // ADDS A ROUTE TO THE END OF THE LIST
    void addRoute(Route& route) {
        if (head == nullptr) {
            head = new Node<Route>(route);
        }
        else {
            Node<Route>* temp = head;
            while (temp->next != nullptr) temp = temp->next;
            temp->next = new Node<Route>(route);
        }
        size++;
    }

    // CHANGE THE COLOR OF THE SELECTED ROUTE
    void deleteRoute(int index) {
        if (index == 1) {
            if (head != nullptr) {
                Node<Route>* temp = head;
                head = head->next;
                delete temp;
                size--;
            }
        }
        else if (index > 1 && index <= size) {
            Node<Route>* temp = head;
            for (int i = 0; i < index - 2; i++) {
                if (temp == nullptr || temp->next == nullptr) return; // INDEX OUT OF BOUNDS -TEMP BUG FIX-
                temp = temp->next;
            }
            Node<Route>* nodeToDelete = temp->next;
            temp->next = nodeToDelete->next;
            delete nodeToDelete;
            size--;
        }
        else {
            cout << "INVALID INDEX" << endl;
        }
    }

    // ADDS A ROUTE TO THE END OF THE LIST
    void draw(RenderWindow& window) {
        Node<Route>* temp = head;
        while (temp != nullptr) {
            temp->data.draw(window);
            temp = temp->next;
        }
    }

    // CLEAR THE LIST AND RELEASE MEMORY
    void clear() {
        while (head != nullptr) {
            Node<Route>* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }
};

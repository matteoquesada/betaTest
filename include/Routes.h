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
			size = 1;
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


    

};
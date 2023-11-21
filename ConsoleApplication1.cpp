// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "include/Node.h"
#include "include/Route.h"
#include "include/Routes.h"
#include "include/Coordinates.h"
#include "include/MapHandler.h"
#include "include/GUI.h"

#include <SFML/Graphics.hpp>
using namespace sf;

#include <iostream>
using namespace std;

int main() {

    RenderWindow window(VideoMode(1280, 720), "AeroMap v1.0 ALPHA");
    window.setFramerateLimit(15); // LIMIT THE FPS TO 15 TO SAVE RESOURCES 

    GUI gui(window); // GUI OBJECT - BASE OF THE ENTIRE UI AND ITS HANDLING

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    gui.handle_input(event);
                }
            }
        }

        // UPDATE CYCLE OF THE GUI
        window.clear();
        gui.draw(window);
        window.display();
    }

    return 0;
}


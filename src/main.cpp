#include "../include/GUI.h"
#include <SFML/Graphics.hpp>

using namespace sf;

// MATTEO VARGAS QUESADA - 2024 - "PROYETO DE MAPA" 
// AEROMAP v1.0 FINAL PUSH
// >>>>>0% GPT<<<<< - 100% PURE MATTEO ;) SI VOY A CAER, LO HARE CON ESPADA Y ESCUDO EN MANO
// CON BASTANTES MEDIDAS ANTI-CRASH Y ROUTE SWAP

int main() {
    RenderWindow window(VideoMode(1280, 720), "AeroMap v1.0 FINAL PUSH");
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
                    gui.inputEngine(event);
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

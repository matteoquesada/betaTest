#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

#include <iostream>
using namespace std;

#include "MapHandler.h"

class GUI {
public:
    // MAP BUTTON-SPRITE
    Texture map_texture;
    Sprite map_sprite;

    // MAP OVERLAY
    MapHandler mapUI;

    // PALLETE BUTTONS
    Texture red_texture, blue_texture, green_texture, yellow_texture, orange_texture;
    Sprite red_sprite, blue_sprite, green_sprite, yellow_sprite, orange_sprite;

    // DOCK BUTTONS
    Texture create_texture, delete_texture, delete_off_texture, delete_on_texture, save_texture, load_texture, switch_texture, hide_texture;
    Sprite create_sprite, delete_sprite, delete_off_sprite, delete_on_sprite, save_sprite, load_sprite, switch_sprite, hide_sprite;

    // CONSTRUCTORS
    GUI() {};

    GUI(RenderWindow& window) {
        // LOAD THE MAP AND THE UI
        initUI(map_texture, map_sprite, "assets/wallpaper/map.bmp", 0, 0, 1.0f, 1.0f);
        // INITIALIZE THE COLOR PALLETE
        initUI(orange_texture, orange_sprite, "assets/UI/orange.bmp", 900, 622, 1.0f, 1.0f);
        initUI(blue_texture, blue_sprite, "assets/UI/blue.bmp", 1110, 622, 1.0f, 1.0f);
        initUI(red_texture, red_sprite, "assets/UI/red.bmp", 1180, 622, 1.0f, 1.0f);
        initUI(green_texture, green_sprite, "assets/UI/green.bmp", 1040, 622, 1.0f, 1.0f);
        initUI(yellow_texture, yellow_sprite, "assets/UI/yellow.bmp", 970, 622, 1.0f, 1.0f);
        // CREATE/DELETE ROUTE BUTTONS + DELETE MODE BUTTON
        initUI(create_texture, create_sprite, "assets/UI/create_route.bmp", 15, 615, 0.35f, 0.35f);
        initUI(delete_texture, delete_sprite, "assets/UI/delete_route.bmp", 15, 660, 0.35f, 0.35f);
        initUI(delete_off_texture, delete_off_sprite, "assets/UI/delete_mode_off.bmp", 685, 615, 0.35f, 0.35f);
        initUI(delete_on_texture, delete_on_sprite, "assets/UI/delete_mode_on.bmp", 0, 0, 0.35f, 0.35f);
        // SAVE/LOAD ROUTES BUTTONS + CHANGE ROUTE BUTTON
        initUI(save_texture, save_sprite, "assets/UI/save_routes.bmp", 350, 615, 0.35f, 0.35f);
        initUI(load_texture, load_sprite, "assets/UI/load_routes.bmp", 350, 660, 0.35f, 0.35f);
        initUI(switch_texture, switch_sprite, "assets/UI/change_route.bmp", 685, 660, 0.35f, 0.35f);
        // SHOW/HIDE ROUTES BUTTON (WITHOUT APPEARANCE CHANGE)
        initUI(hide_texture, hide_sprite, "assets/UI/show_hide.png", 1215, 540, 0.35f, 0.35f);
    }

    // DRAWS THE GUI
    void draw(RenderWindow& window) {
        // MAP - UI BACKGROUND
        window.draw(map_sprite);

        // DRAW THE MAP OVERLAY WITH ALL THE ROUTES AND NODES
        mapUI.draw(window);

        // PALLETE OF COLORS
        window.draw(red_sprite); window.draw(blue_sprite);
        window.draw(green_sprite); window.draw(yellow_sprite);
        window.draw(orange_sprite);

        // DOCK OF BUTTONS
        window.draw(create_sprite);
        window.draw(delete_sprite);
        window.draw(switch_sprite);
        window.draw(save_sprite);
        window.draw(load_sprite);
        window.draw(hide_sprite);

        // DELETE MODE BEHAVIOR
        // MOVES OUT OF THE SCREEN WHEN NOT ACTIVE - MAKING IT INVISIBLE AND UNCLICKABLE
        if (mapUI.deleteMode) {
            delete_on_sprite.setPosition(685, 615);
            delete_off_sprite.setPosition(-1000, -1000);
            window.draw(delete_on_sprite);
        }
        else {
            delete_off_sprite.setPosition(685, 615);
            delete_on_sprite.setPosition(-1000, -1000);  // MOVE OUT OF THE SCREEN (BUENA TECNICA AH?) EZ PEASY
            window.draw(delete_off_sprite);
        }
    }

    // MOST OF THE IF STATEMENTS ARE SINGLE LINE BECAUSE THEY CALL A SINGLE FUNCTION
    void inputEngine(Event& event) {
        if (event.type == Event::MouseButtonPressed) {
            if (event.mouseButton.button == Mouse::Left) {

                // CHECK IF THE MOUSE CLICKED ON A PALLETE COLOR
                if (clicked(event.mouseButton.x, event.mouseButton.y, red_sprite)) mapUI.changeColor(Color::Red);
                else if (clicked(event.mouseButton.x, event.mouseButton.y, blue_sprite)) mapUI.changeColor(Color::Blue);
                else if (clicked(event.mouseButton.x, event.mouseButton.y, green_sprite)) mapUI.changeColor(Color::Green);
                else if (clicked(event.mouseButton.x, event.mouseButton.y, yellow_sprite)) mapUI.changeColor(Color::Yellow);
                else if (clicked(event.mouseButton.x, event.mouseButton.y, orange_sprite)) mapUI.changeColor(Color(255, 155, 0));

                // CHECK IF THE MOUSE IS ON A BUTTON OF THE DOCK (outside the map)
                else if (clicked(event.mouseButton.x, event.mouseButton.y, create_sprite)) mapUI.addRoute(Route());
                else if (clicked(event.mouseButton.x, event.mouseButton.y, delete_sprite)) mapUI.deleteRoute();
                else if (clicked(event.mouseButton.x, event.mouseButton.y, delete_off_sprite)) mapUI.toggleDelete();
                else if (clicked(event.mouseButton.x, event.mouseButton.y, delete_on_sprite)) mapUI.toggleDelete();
                else if (clicked(event.mouseButton.x, event.mouseButton.y, save_sprite)) mapUI.save();
                else if (clicked(event.mouseButton.x, event.mouseButton.y, load_sprite)) mapUI.load();
                else if (clicked(event.mouseButton.x, event.mouseButton.y, switch_sprite)) {
                    mapUI.switchRoute();
                    cout << "CURRENT ROUTE: " << mapUI.selectedRoute << endl;
                }
                else if (clicked(event.mouseButton.x, event.mouseButton.y, hide_sprite)) mapUI.showHide();

                // CHECK IF THE MOUSE IS ON THE MAP
                else if (clicked(event.mouseButton.x, event.mouseButton.y, map_sprite)) {
                    if (event.mouseButton.x > 0 && event.mouseButton.x < 1280 && event.mouseButton.y > 0 && event.mouseButton.y < 600) { // IF THE MOUSE IS INSIDE THE MAP
                        if (mapUI.selectedRoute == -1) cout << "NO ROUTE SELECTED" << endl;
                        else {
                            Coordinates coords(event.mouseButton.x, event.mouseButton.y); // CREATE A COORDINATE OBJECT WITH THE MOUSE POSITION
                            if (mapUI.deleteMode) mapUI.deletePoint(coords); // IF DELETE MODE IS ACTIVE, DELETE THE POINT
                            else mapUI.addPoint(coords); // IF DELETE MODE IS NOT ACTIVE, ADD THE POINT
                        }
                    }
                }
            }
        }
    };

    // INITIALIZES A TEXTURE AND A SPRITE WITH THE GIVEN PARAMETERS
    void initUI(Texture& texture, Sprite& sprite, string dir, int x, int y, float x_scale, float y_scale) {
        texture.loadFromFile(dir);
        if (!texture.loadFromFile(dir)) cout << "ERROR: HABIA CEREAL PERO NO LECHE EN " << dir << endl;
        sprite.setTexture(texture);
        sprite.setScale(x_scale, y_scale);
        sprite.setPosition(x, y);
    }

    // HANDLES THE MOUSE CLICK
    bool clicked(int x, int y, Sprite& button) {
        if (isInside(x, y, button)) return true;
		else return false;
    }

    // CHECKS IF THE MOUSE IS INSIDE A BUTTON
    bool isInside(int x, int y, Sprite& button) {
        FloatRect bounds = button.getGlobalBounds();
        return bounds.contains(static_cast<float>(x), static_cast<float>(y));
    }

    // DESTRUCTOR
    ~GUI() {
    }

};

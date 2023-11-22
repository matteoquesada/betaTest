#pragma once

// CLASS REPRESENTING COORDINATES WITH X AND Y VALUES
class Coordinates {
private:
    int x;  // X-COORDINATE
    int y;  // Y-COORDINATE

public:
    // DEFAULT CONSTRUCTOR, INITIALIZES X AND Y TO 0
    Coordinates() : x(0), y(0) {}

    // PARAMETERIZED CONSTRUCTOR, SETS X AND Y BASED ON INPUT VALUES
    Coordinates(int x, int y) : x(x), y(y) {}

    // GETTER FUNCTION FOR X
    int getX() const {
        return x;
    }

    // GETTER FUNCTION FOR Y
    int getY() const {
        return y;
    }
};

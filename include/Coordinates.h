#pragma once
class Coordinates {

	int x;
	int y;

public:

	Coordinates()
	{
		x = 0;
		y = 0;
	}

	Coordinates(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	int getX()
	{
		return x;
	}

	int getY()
	{
		return y;
	}



};
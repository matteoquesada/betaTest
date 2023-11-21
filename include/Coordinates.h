#pragma once
class Coordinates {

	int x;
	int y;

public:

	Coordinates()
	{
		this->x = 0;
		this->y = 0;
	}

	Coordinates(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	int getX()
	{
		return this->x;
	}

	int getY()
	{
		return this->y;
	}

	void setX(int x)
	{
		this->x = x;
	}

	void setY(int y)
	{
		this->y = y;
	}

};
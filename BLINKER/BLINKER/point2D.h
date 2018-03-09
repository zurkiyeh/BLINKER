#pragma once
#include "stdafx.h"

class Point2D
{
private:
	int x;
	int y;
public:
	Point2D(int x_coord = 0, int y_coord = 0): x(x_coord), y(y_coord){}
	void setX(int _x) { x = _x; }
	void setY(int _y) { x = _y; }
	int getX() { return x; }
	int getY() { return y; }


};


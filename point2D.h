#pragma once

#include "includes.h"

class Point2D{
	private:
		GLdouble x;
		GLdouble y;
	public:	
		Point2D():x(0), y(0){}
		Point2D(std::ifstream* fichier){*fichier >> x >> y;}
};
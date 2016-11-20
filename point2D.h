#pragma once

#include "includes.h"

class point2D{
	private:
		GLdouble x;
		GLdouble y;
	public:	
		point2D():x(0), y(0){}
		point2D(std::ifstream& fichier){fichier >> x >> y;}
};
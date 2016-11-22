#pragma once

#include "includes.h"
#include "Point3D.h"

class Camera{
	private:
		Point3D targetPos;
        GLdouble zNear;
        GLdouble zFar;
        Point3D camPos;
	public:
		Camera(){}

		//première définition de la caméra
		void definitionCamera(const Point3D& coordMin, const Point3D& coordMax);
		//redéfinition à chaque redimenssionnement de la fenêtre
		void definitionFrustum(const int& w, const int& h);
		
		void rotationObjet(const GLdouble& angleX, const GLdouble& angleY);
};
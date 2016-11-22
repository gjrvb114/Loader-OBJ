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
		Camera(const Camera& _cam):
			targetPos(_cam.targetPos), zNear(_cam.zNear), zFar(_cam.zFar), camPos(_cam.camPos){}
		Camera(Point3D _targetPos, GLdouble _zNear, GLdouble _zFar, Point3D _camPos):
			targetPos(_targetPos), zNear(_zNear), zFar(_zFar), camPos(_camPos){}
		
		void definitionCamera(const Point3D& coordMin, const Point3D& coordMax);
		void definitionFrustum(const int& w, const int& h);
		void rotationObjet(const GLdouble& angleX, const GLdouble& angleY);
		
		void settargetPos(const Point3D& _targetPos){targetPos=_targetPos;}
		void setzNear(const GLdouble& _zNear){zNear=_zNear;}
		void setzFar(const GLdouble& _zFar){zFar=_zFar;}
		void setcamPos(const Point3D& _camPos){camPos=_camPos;}

};
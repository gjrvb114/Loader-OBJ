#include "Camera.h"

void Camera::definitionCamera(const Point3D& coordMin, const Point3D& coordMax)
{
	//on définit le frustum de vue à partir des coordonnées extrêmes de l'objet 3D
	Point3D tailleObjet(coordMax-coordMin);
    targetPos = Point3D((coordMin+coordMax)/2.0f);
    camPos = targetPos-Point3D(0.0f, tailleObjet.gety()/2.0f + tailleObjet.maxi()*2.0, 0.0f);
    zNear = tailleObjet.maxi();
    zFar = zNear + 2*tailleObjet.maxi();
}

//Définition de la caméra
void Camera::definitionFrustum(const int& w, const int& h)
{
    gluPerspective(90.0f , w/(h*1.0f) , zNear , zFar);
	gluLookAt(camPos.getx(), camPos.gety(), camPos.getz(),
           targetPos.getx(), targetPos.gety(), targetPos.getz(),
           0.0f, 0.0f, 1.0f);
}

//rotation de l'objet de angleX et angleY
void Camera::rotationObjet(const GLdouble& angleX, const GLdouble& angleY)
{
    glTranslatef(targetPos.getx(), targetPos.gety(), targetPos.getz());
	glRotatef(angleY,1.0f,0.0f,0.0f);
	glRotatef(angleX,0.0f,0.0f,1.0f);
	glTranslatef(-targetPos.getx(), -targetPos.gety(), -targetPos.getz());
}
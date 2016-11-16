#pragma once

#include <vector>

#include "Point3D.h"

struct point2D
{
	GLdouble x;
	GLdouble y;
	point2D():x(0), y(0){}
	point2D(std::ifstream& fichier){fichier >> x >> y;}
};

struct indices
{
	GLint v;
	GLint vt;
	GLint vn;
	indices():v(0), vt(0), vn(0){}
	indices(std::ifstream& fichier){fichier >> v >> vt >> vn;}
};

class Objet
{
    public:
        Objet(){}
        void lireFace(const std::string& str_face);
        void stockerDonnees();
        void dessinerObjet();
        void definitionCamera(const int& w,const int& h);
        void rotation(const GLdouble& angleX, const GLdouble& angleY);
    private:
        std::vector<Point3D> vertices;
        std::vector<point2D> textures;
        std::vector<Point3D> normales;
        std::vector< std::vector<indices> > faces;

        Point3D targetPos;
        GLdouble zNear;
        GLdouble zFar;
        Point3D camPos;
};

int reecrire_face(std::string & face);

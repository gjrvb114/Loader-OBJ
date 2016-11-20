#pragma once

#include "includes.h"

#include "Point3D.h"
#include "Point2D.h"
#include "indices.h"

//contient la définition de l'objet et de la caméra
class Objet
{
    public:
		Objet(){}
        void stockerDonnees(const std::string& chemin_fichier_obj);
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
		
		void lireFace(const std::string& str_face);
		void lireFace(std::ifstream& fichier);
};

int reecrire_face(std::string & face);

#pragma once

#include "includes.h"

#include "Point3D.h"
#include "Point2D.h"
#include "Indices.h"

//contient la définition de l'objet et de la caméra
class Objet3D
{
	private:
        std::vector<Point3D> vertices;
        std::vector<Point2D> textures;
        std::vector<Point3D> normales;
        std::vector< std::vector<indices> > faces;
		
    public:
		Objet3D(){}
		
		void addVertex(std::ifstream* fichier, Point3D* coordMin, Point3D* coordMax);
		void addTexture(std::ifstream* fichier);
		void addNormale(std::ifstream* fichier);
		void addFace(std::ifstream* fichier);
		
        void dessinerObjet();
        void rotation(const GLdouble& angleX, const GLdouble& angleY);
};
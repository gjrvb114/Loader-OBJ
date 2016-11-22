#pragma once

#include "includes.h"
#include "Objet3D.h"
#include "Camera.h"

class Loader{
	private:
		Objet3D objet;
		Camera camera;
	public:
		Loader(){}
		void stockerDonnees(const std::string& chemin_fichier_obj);
		void dessiner();
		void rotation(const GLdouble& angleX, const GLdouble& angleY);
		void redefinitionFrustum(const int& w,const int& h);

};
#include "Loader.h"


void Loader::stockerDonnees(const std::string& chemin_fichier_obj)
{
	//ouverture du fichier
	std::ifstream fichier(chemin_fichier_obj, std::ios::in);
	if (!fichier)
	{
		std::cerr << std::endl << "Impossible d'ouvrir" << std::endl;
	}

    //on va stocker chaque début de ligne dans str_courant
	std::string str_courant;
	fichier >> str_courant;

	//On va localiser notre objet dans un cube entre coordMin et coordMax
	Point3D coordMin;
    Point3D coordMax;

	// On commence par lire le fichier jusqu'à tomber sur qqch d'intéressant
    while(!fichier.eof() && str_courant!="v" && str_courant!="f" && str_courant!="vn")
    {
        //on ne lit un mot que si on est au début d'une ligne
        if (str_courant == "_")
        {
            fichier >> str_courant;
        }
        //sinon on la saute
        else
        {
            std::getline(fichier, str_courant);
            str_courant = "_";
        }
    }
	
    // Tant qu'on est pas à la fin du fichier, 
    while(!fichier.eof())
    {
		//On ajoute le vertex, la texture, la normale ou la face
        if(str_courant=="v")
        {
            objet.addVertex(&fichier, &coordMin, &coordMax);
        }
        else if(str_courant=="vt")
        {
            objet.addTexture(&fichier);
        }
        else if(str_courant=="vn")
        {
            objet.addNormale(&fichier);
        }
        else if(str_courant=="f")
        {
			objet.addFace(&fichier);
        }
		
		//puis on attend de retomber sur une ligne intéressante
        str_courant = "_";
        while(!fichier.eof() && str_courant!="v" && str_courant!="f" && str_courant!="vn")
        {
            //on ne lit un mot que si on est au début d'une ligne
            if (str_courant == "_")
            {
                fichier >> str_courant;
            }
            //sinon on la saute
            else
            {
                std::getline(fichier, str_courant);
                str_courant = "_";
            }
        }
    }
	
	//définitions arbitraires des paramètres de la caméra
	camera.definitionCamera(coordMin, coordMax);
}

void Loader::dessiner()
{
	objet.dessinerObjet();
}

void Loader::rotation(const GLdouble& angleX, const GLdouble& angleY)
{
	camera.rotationObjet(angleX, angleY);
}

void Loader::redefinitionFrustum(const int& w,const int& h)
{
	camera.definitionFrustum(w, h);
}
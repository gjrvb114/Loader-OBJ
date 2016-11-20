#include "Objet.h"

//fonction de lecture d'une face
void Objet::lireFace(std::ifstream& fichier)
{
	//contient l'indice d'un v, vt ou vn
	int entierCourant(0);
	//permet de se situer dans la définition d'un point
	//0 -> v ; 1-> vt ; 2 -> vn 
	int cas(0);
	//la définition d'un point qu'on va ajouter à l'attribut faces
	indices defPoint;
	//la ligne de définition de la face
	std::string ligne;
	getline(fichier, ligne);
	//indice de pacours de la ligne
	unsigned int i(0);
	while(i<ligne.size())
	{
		//S'il n'y a pas d'espace on est dans la définition d'un indice d'un point
		if(ligne[i]!=' ')
        {
			//On reste dans cette définition jusque la fin, un / ou un espace
			while(i<ligne.size() && ligne[i]!='/' && ligne[i]!=' ')
            {  
				entierCourant*=10;
				entierCourant+=ligne[i]-'0';
                i++;
            }
            switch(cas)
            {
                case 0:
                    defPoint.setv(entierCourant);
                    break;
                case 1:
                    defPoint.setvt(entierCourant);
                    break;
                case 2:
                    defPoint.setvn(entierCourant);
                    faces.back().push_back(defPoint);
                    break;
            }

            entierCourant = 0;
            cas = (cas+1)%3;
        }
		i++;
	}
}


void Objet::stockerDonnees(const std::string& chemin_fichier_obj)
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

	//vector d'indices vide
	std::vector<indices> vectorPoint;

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
	
    // Tant qu'on est pas à la fin du fichier
    while(!fichier.eof())
    {
        if(str_courant=="v")
        {
            vertices.push_back(Point3D(fichier));

            //on redéfinit coordMin et coordMax si nécessaire
            coordMin = coordMin.minimum(vertices.back());
            coordMax = coordMax.maximum(vertices.back());
        }
        else if(str_courant=="vt")
        {
            textures.push_back(point2D(fichier));
        }
        else if(str_courant=="vn")
        {
            normales.push_back(Point3D(fichier));
        }
        else if(str_courant=="f")
        {
            faces.push_back(vectorPoint);
			lireFace(fichier);
        }
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
    Point3D tailleObjet(coordMax-coordMin);
    targetPos = Point3D((coordMin+coordMax)/2.0f);
    camPos = targetPos-Point3D(0.0f, tailleObjet.gety()/2.0f + tailleObjet.maxi()*2.0, 0.0f);
    zNear = tailleObjet.maxi();
    zFar = zNear + 2*tailleObjet.maxi();
}

//dessin de l'objet 3D
void Objet::dessinerObjet()
{
    for(int i=0; i<(int)faces.size(); i++)
    {
        glBegin(GL_POLYGON);
        for(int j=0; j<(int)faces[i].size(); j++)
        {
            glNormal3f(normales[faces[i][j].getvn()-1].getx(), normales[faces[i][j].getvn()-1].gety(), normales[faces[i][j].getvn()-1].getz());
            glVertex3f(vertices[faces[i][j].getv()-1].getx(), vertices[faces[i][j].getv()-1].gety(), vertices[faces[i][j].getv()-1].getz());
        }
        glEnd();
    }
}

//rotation de l'objet de angleX et angleY
void Objet::rotation(const GLdouble& angleX, const GLdouble& angleY)
{
    glTranslatef(targetPos.getx(), targetPos.gety(), targetPos.getz());
	glRotatef(angleY,1.0f,0.0f,0.0f);
	glRotatef(angleX,0.0f,0.0f,1.0f);
	glTranslatef(-targetPos.getx(), -targetPos.gety(), -targetPos.getz());
}

//Définition de la caméra
void Objet::definitionCamera(const int& w, const int& h)
{
    gluPerspective(90.0f , w/(h*1.0f) , zNear , zFar);
	gluLookAt(camPos.getx(), camPos.gety(), camPos.getz(),
           targetPos.getx(), targetPos.gety(), targetPos.getz(),
           0.0f, 0.0f, 1.0f);
}
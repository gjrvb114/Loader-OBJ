#include "Objet3D.h"


void Objet3D::addVertex(std::ifstream* fichier, Point3D* coordMin, Point3D* coordMax)
{
	//ajout d'un point � vertices
	vertices.push_back(Point3D(fichier));
	//on red�finit coordMin et coordMax si n�cessaire
	*coordMin = coordMin->minimum(vertices.back());
	*coordMax = coordMax->maximum(vertices.back());
}

void Objet3D::addTexture(std::ifstream* fichier)
{
	//ajout de coordonn�es de textures � textures
	textures.push_back(Point2D(fichier));
}
void Objet3D::addNormale(std::ifstream* fichier)
{
	//ajout d'une normale � noamrles
	normales.push_back(Point3D(fichier));
}


//fonction de lecture d'une face
void Objet3D::addFace(std::ifstream* fichier)
{
	//ajout d'une nouvelle face dans faces
	faces.push_back(std::vector<indices>());
	
	//contient l'indice d'un v, vt ou vn
	int entierCourant(0);
	//permet de se situer dans la d�finition d'un point
	//0 -> v ; 1-> vt ; 2 -> vn 
	int cas(0);
	//la d�finition d'un point qu'on va ajouter � l'attribut faces
	indices defPoint;
	//la ligne de d�finition de la face
	std::string ligne;
	getline(*fichier, ligne);
	//indice de pacours de la ligne
	unsigned int i(0);
	while(i<ligne.size())
	{
		//S'il n'y a pas d'espace on est dans la d�finition d'un indice d'un point
		if(ligne[i]!=' ')
        {
			//On reste dans cette d�finition jusque la fin de la ligne, un '/' ou un espace
			while(i<ligne.size() && ligne[i]!='/' && ligne[i]!=' ')
            {  
				//construction de l'entier courant chiffre par chiffre
				entierCourant*=10;
				entierCourant+=ligne[i]-'0';
                i++;
            }
			//l'entier courant est d�fini et correspond � l'indice d'un vertex, d'une texture ou d'une normale
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
					
					//on a r�cup�r� un vertex, une texture et une normale,
					//on ajoute la point � la face en cours de d�finition
                    faces.back().push_back(defPoint);
                    break;
            }
			//on r�initialise l'entier courant
            entierCourant = 0;
            cas = (cas+1)%3;
        }
		i++;
	}
}


//dessin de l'objet 3D
void Objet3D::dessinerObjet()
{
	//on parcourt chaque face
    for(int i=0; i<(int)faces.size(); i++)
    {
		//on cr�� un polygon � partir des points de la face
        glBegin(GL_POLYGON);
        for(int j=0; j<(int)faces[i].size(); j++)
        {
            glNormal3f(normales[faces[i][j].getvn()-1].getx(), normales[faces[i][j].getvn()-1].gety(), normales[faces[i][j].getvn()-1].getz());
            glVertex3f(vertices[faces[i][j].getv()-1].getx(), vertices[faces[i][j].getv()-1].gety(), vertices[faces[i][j].getv()-1].getz());
        }
        glEnd();
    }
}


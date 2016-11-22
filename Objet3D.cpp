#include "Objet3D.h"


void Objet3D::addVertex(std::ifstream* fichier, Point3D* coordMin, Point3D* coordMax)
{
	vertices.push_back(Point3D(fichier));
	//on redéfinit coordMin et coordMax si nécessaire
	*coordMin = coordMin->minimum(vertices.back());
	*coordMax = coordMax->maximum(vertices.back());
}

void Objet3D::addTexture(std::ifstream* fichier)
{
	textures.push_back(Point2D(fichier));
}
void Objet3D::addNormale(std::ifstream* fichier)
{
	normales.push_back(Point3D(fichier));
}


//fonction de lecture d'une face
void Objet3D::addFace(std::ifstream* fichier)
{
	//vector d'indices vide
	std::vector<indices> vectorPoint;
	
	faces.push_back(vectorPoint);
	
	//contient l'indice d'un v, vt ou vn
	int entierCourant(0);
	//permet de se situer dans la définition d'un point
	//0 -> v ; 1-> vt ; 2 -> vn 
	int cas(0);
	//la définition d'un point qu'on va ajouter à l'attribut faces
	indices defPoint;
	//la ligne de définition de la face
	std::string ligne;
	getline(*fichier, ligne);
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


//dessin de l'objet 3D
void Objet3D::dessinerObjet()
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


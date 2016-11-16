#include "Objet.h"

void Objet::lireFace(const std::string& str_face)
{
    // "cas" stocke l'état en cours c'est-à-dire :
    // 0 : v
    // 1 : vt
    // 2 : vn
    int cas = 0;

    //la position dans le string
    unsigned int i = 0;

    //l'entier courant
    std::string entierCourant = "0";

    indices defPoint;

    while(i<str_face.size())
    {
        if(str_face[i]!=' ')
        {
            while(i<str_face.size() && str_face[i]!='/' && str_face[i]!=' ')
            {
                entierCourant += str_face[i];
                i++;
            }
            switch(cas)
            {
                case 0:
                    defPoint.v = std::stoi(entierCourant);
                    break;
                case 1:
                    defPoint.vt = std::stoi(entierCourant);
                    break;
                case 2:
                    defPoint.vn = std::stoi(entierCourant);
                    faces.back().push_back(defPoint);
                    break;
            }

            entierCourant = "0";
            cas = (cas+1)%3;
        }
        i++;
    }
}

void Objet::stockerDonnees()
{
    std::string nomFichier;
	//choix du fichier OBJ à lire
	/*
	cout << "Veuillez entrer le nom du fichier OBJ a lire" << endl;
	cin >> nomFichier;
	*/
	//nomFichier="C:\\Users\\Jimmy\\Desktop\\C++\\Loader OBJ\\cube.obj";
	nomFichier="C:\\Users\\Jimmy\\Desktop\\C++\\Loader OBJ Guillaume\\Monkey.obj";

    //ouverture du fichier
	std::ifstream fichier(nomFichier, std::ios::in);
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
            std::getline(fichier, str_courant);
			lireFace(str_courant);
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

    Point3D tailleObjet(coordMax-coordMin);
    targetPos = Point3D((coordMin+coordMax)/2.0f);
    camPos = targetPos-Point3D(0.0f, tailleObjet.gety()/2.0f + tailleObjet.maxi()*2.0, 0.0f);
    zNear = tailleObjet.maxi();
    zFar = zNear + 2*tailleObjet.maxi();
}

void Objet::dessinerObjet()
{
    for(int i=0; i<(int)faces.size(); i++)
    {
        glBegin(GL_POLYGON);
        for(int j=0; j<(int)faces[i].size(); j++)
        {
            glNormal3f(normales[faces[i][j].vn-1].getx(), normales[faces[i][j].vn-1].gety(), normales[faces[i][j].vn-1].getz());
            glVertex3f(vertices[faces[i][j].v-1].getx(), vertices[faces[i][j].v-1].gety(), vertices[faces[i][j].v-1].getz());
        }
        glEnd();
    }
}

void Objet::rotation(const GLdouble& angleX, const GLdouble& angleY)
{
    glTranslatef(targetPos.getx(), targetPos.gety(), targetPos.getz());
	glRotatef(angleY,1.0f,0.0f,0.0f);
	glRotatef(angleX,0.0f,0.0f,1.0f);
	glTranslatef(-targetPos.getx(), -targetPos.gety(), -targetPos.getz());
}

void Objet::definitionCamera(const int& w,const int& h)
{
    gluPerspective(90.0f , w/(h*1.0f) , zNear , zFar);
	gluLookAt(camPos.getx(), camPos.gety(), camPos.getz(),
           targetPos.getx(), targetPos.gety(), targetPos.getz(),
           0.0f, 0.0f, 1.0f);
}



int reecrire_face(std::string & face)
{
    //on va renvoyer le nombre de point de la face
	int nb_point = 0;
	std::string s;
	int n = face.length();
	for(int i=0; i<n ;i++)
	{
		if (face[i]=='/' && s.back()==' ')
		{
			nb_point++;
			s.append("0 ");
		}
		else if(face[i]=='/')
		{
			nb_point++;
			s.push_back(' ');
		}
		else
		{
			s.push_back(face[i]);
		}
	}
	face = s;
	return nb_point/2;
}

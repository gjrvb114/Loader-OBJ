#include <Windows.h>

#include "Objet.h"

//variables utiles pour bouger l'objet
const GLdouble pasRotation = 0.866f;
const GLdouble pasTranslation = 0.01;
GLboolean boutonGauche = false;
GLboolean boutonDroit = false;
GLdouble angleX = 0.0f;
GLdouble angleY = 0.0f;
GLdouble transX = 0.0f;
GLdouble transY = 0.0f;
GLint oldXRot = 0;
GLint oldYRot = 0;
GLint oldXTrans = 0;
GLint oldYTrans = 0;

//notre objet qui va tout contenir
Objet objet;

//déclaration des callbacks
GLvoid clavier(unsigned char touche, GLint x, GLint y);
GLvoid redimensionner(int w, int h);
GLvoid souris(int bouton, int etat, int x, int y);
GLvoid mouvement(int x, int y);
GLvoid affichage();

int main(int argc, char *argv[])
{
    // Initialisation
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(800,800);
	glutCreateWindow("OBJ loader");
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glEnable(GL_DEPTH_TEST);


	// Stockage des données dans objet
    objet.stockerDonnees();

	// Définition des callbacks
	glutDisplayFunc(affichage);
	glutKeyboardFunc(clavier);
	glutReshapeFunc(redimensionner);
	glutMouseFunc(souris);
	glutMotionFunc(mouvement);

	//lancement de la boucle principale
	glutMainLoop();
}

GLvoid affichage()
{
    // Nettoyage des buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Dessin de l'objet
	objet.dessinerObjet();

    // On applique la rotation et la translation à l'objet
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(transX, 0, -transY);
	objet.rotation(angleX, angleY);

	glFlush();
}

GLvoid redimensionner(int w, int h)
{
    //matrice de projection et viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	objet.definitionCamera(w, h);
	glViewport(0, 0, w, h);
}

GLvoid clavier(unsigned char touche, GLint x, GLint y)
{
	switch(touche)
	{
	case 'p':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 'f':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 's':
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	case 'q':
	case 27:
		exit(0);
		break;
	}
	glutPostRedisplay();
}

GLvoid souris(int bouton, int etat, int x, int y)
{
	if (bouton == GLUT_LEFT_BUTTON)
	{
		oldXRot = x;
		oldYRot = y;
		if (etat == GLUT_DOWN)
		{
			boutonGauche = true;
		}
		else
		{
			boutonGauche = false;
		}
	}
	if (bouton == GLUT_RIGHT_BUTTON)
	{
		oldXTrans = x;
		oldYTrans = y;

		if (etat == GLUT_DOWN)
		{
			boutonDroit = true;
		}
		else
		{
			boutonDroit = false;
		}
	}
}

GLvoid mouvement(int x, int y)
{
	if (boutonGauche)
	{
		angleX = angleX - (oldXRot-x)*pasRotation;
		angleY = angleY - (oldYRot-y)*pasRotation;

		oldXRot = x;
		oldYRot = y;
	}
	else if (boutonDroit)
	{
		transX = transX - (oldXTrans-x)*pasTranslation;
		transY = transY - (oldYTrans-y)*pasTranslation;

		oldXTrans = x;
		oldYTrans = y;
	}

	glutPostRedisplay();
}

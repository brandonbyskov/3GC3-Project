/*	Wizard-Tower Game
*	Final project - CS 3GC3 McMaster University
*	By Eric Amshukov 1133146 and Brandon Byskov 1068517
*	December 2014
*/

#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <list>
#include <vector>

#include "gllibs.h"

#include "main.h"
#include "enemy.h"
#include "player.h"
#include "tower.h"
#include "camera.h"


using namespace std;

int main_id;

//Tower constants
const int towerSize = 5;
const int towerLayers = 30;
const float blockSize = 3.0;

int gMouseState;
int gButtonClicked;

/* Movement states */
bool hasVerticalCollision;

/* Global angle theta */
float gTheta[3];

/* Current mouse position */
float currentMouse[] = {0, 0, 0};

/* Global origin */

/* Camera */
float cameraSpeed = 0.25;
float cameraDistance = 20;
float gCamPos[3];
float gPlayerLookDirection[3];
float gPlayerPosition[3];

/* Global physics */
float gravity;
float friction;

int gMaxParticleAge;
int gMaxSpellAge;

/* Speacial Modes */
bool wireframeMode = true;
bool colorMapMode = false;

/* Light values */
float qaAmbientLight[] = {0.2, 0.2, 0.2, 1.0};
float qaDiffuseLight[] = {0.8, 0.8, 0.8, 1.0};
float qaSpecularLight[] = {1.0, 1.0, 1.0, 1.0};
float lightPosition0[] = {0.5, 0.5, 0.0, 1.0};
float lightPosition1[] = {0.5, 30, 0.0, 1.0};

/* Colours */
float blue[] = {0, 0, 1};
float red[] = {1, 0, 0};
float green[] = {0, 1, 0};
float orange[] = {1, 0.5, 0};
float purple[] = {1.0, 0.0, 0.8};
float white[] = {1.0, 1.0, 1.0};
float black[] = {0.0, 0.0, 0.0};
float grey[] = {0.4, 0.4, 0.4};
float skin[] = {0.96, 0.80, 0.69};
float wood[] = {0.52, 0.37, 0.26};


/* Set the global origin of the simulation */

void printInstructions()
{
	cout << "Commands\n";
	cout << "___________________________\n";
	cout << "Quit                                       'Q'\n";
	cout << "rotate camera:                          Cursor\n";
	cout << "Move Character:                      WASD keys\n";
	cout << "Toggle Wireframe Mode:                     'F'\n";
	cout << "Toggle Color Map Mode:                     'C'\n";
	cout << "Reset Terrain                              'R'\n";
	cout << "Change Terrain Parameters          Right Click\n";
	cout << "Note: You must reset the Terrain to use new Terrain parameters.\n";

}

/* Set the global angle theta */
void setTheta(float x, float y, float z)
{
	gTheta[0] = x;
	gTheta[1] = y;
	gTheta[2] = z;
}

/* Set the global position of the Camera */
void setCamPosition(float x, float y, float z)
{
	gCamPos[0] = x;
	gCamPos[1] = y;
	gCamPos[2] = z;
}

/* Set player look direction */
void setPlayerLookDirection(float x, float y, float z)
{
	gPlayerLookDirection[0] = x;
	gPlayerLookDirection[1] = y;
	gPlayerLookDirection[2] = z;
}


/* Returns a newly instantiated an player object */
Player createPlayer(float* o, float m)
{
	float pOrigin[3];
	for (int i = 0; i < 3; i++)
	{
		pOrigin[i] = o[i];
	}

	Player p(pOrigin, m);
	return p;
}

/* Returns a newly instantiated an enemy object */
Enemy createEnemy(float* o, float m)
{
	float eOrigin[3];
	for (int i = 0; i < 3; i++)
	{
		eOrigin[i] = o[i];
	}

	Enemy e(eOrigin, m);
	return e;
}

float gOrigin[] = {0.0, 50.0, 0};
float enemyOrigin[] = {10.0, 20.0, 10.0};

Player player1 = createPlayer(gOrigin, 0.5);
Enemy tempEnemy = createEnemy(enemyOrigin, 0.5);
Tower* tower = new Tower(gOrigin,towerSize,towerLayers,blockSize);
Camera* camera = new Camera(player1.pos, cameraDistance, 1.0);

void getPlayerPosition()
{
	gPlayerPosition[0] = player1.getX();
	gPlayerPosition[1] = player1.getY();
	gPlayerPosition[2] = player1.getZ();
}


/* Initializes all the variables for the Particle Simulation */
void init()
{
	gMaxParticleAge = 100;
	gMaxSpellAge = 1000;
	/* Disable Mouse */
	glutSetCursor(GLUT_CURSOR_NONE);

	/* Initialze physics */
	gravity = 0.003f;
	friction = 0.9;

	/* Initialize global origin, theta and camera variables */
	setTheta(1.0, 1.0, 1.0);
	setCamPosition(15.0, 15.0, 15.0);
	setPlayerLookDirection(0.0, 0.0, 0.0);


	/* Enable lighting and create a light0 with ambience, diffusion and specularity */
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	
	glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight);

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);

	
	/* Initialize OpenGL colour, Depth Test, Projection mode */
	glColor3f(1, 1, 1);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);

	/* Set a perspective */
	gluPerspective(70, 1, 1, 100);

	/* Print Instructions */
	printInstructions();

}

/* Takes user's keyboard input when they release a key */
void keyboardUp(unsigned char key, int x, int y)
{
	/* Character Movement Release*/
	if (key == ' ')
	{
		player1.cancelMovement(4);
	}

	if (key == 'w' || key == 'W')
	{
		player1.cancelMovement(1);
	}
	if (key == 's' || key == 'S')
	{
		player1.cancelMovement(0);
	}

	if (key == 'd' || key == 'D')
	{
		player1.cancelMovement(3);
	}
	if (key == 'a' || key == 'A')
	{
		player1.cancelMovement(2);
	}
}
void keyboard(unsigned char key, int x, int y)
{

	/* Quit the simulation */
	if (key =='q' || key == 'Q')
	{
		exit(1);
	}

	/* Character Movement */

	if (key == ' ')
	{
		player1.setMovement(4);
	}
	if (key == 'w' || key == 'W')
	{
		player1.setMovement(1);
	}
	if (key == 's' || key == 'S')
	{
		player1.setMovement(0);
	}

	if (key == 'd' || key == 'D')
	{
		player1.setMovement(3);
	}
	if (key == 'a' || key == 'A')
	{
		player1.setMovement(2);
	}
	if (key == 'g' || key == 'G')
	{
		player1.castSpell();
	}
}

/* Mouse click call back */
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		player1.castSpell();
	}
}

void passiveMouse(int x, int y)
{
	///* Rotate camera angle left if mouse moves left */
	//if (x - currentMouse[0] < 0)
	//{
	//	gTheta[2] -= cameraSpeed;
	//	gTheta[0] -= cameraSpeed;
	//}

	///* Rotate camera angle Right if mouse moves right */
	//if (x - currentMouse[0] > 0)
	//{
	//	gTheta[2] += cameraSpeed;
	//	gTheta[0] += cameraSpeed;
	//}
	//
	///* Rotate camera Down if mouse moves down */
	//if (y - currentMouse[1] < 0 && gTheta[1] > -2.0)
	//{
	//	gTheta[1] -= cameraSpeed;
	//}

	///* Rotate camera Up if mouse moves up */
	//if (y - currentMouse[1] > 0 && gTheta[1] < 2.0)
	//{
	//	gTheta[1] += cameraSpeed;
	//}

	camera->move(x - currentMouse[0], y - currentMouse[1]);

	/* Set current mouse to current position */
	currentMouse[0] = x;
	currentMouse[1] = y;
											  
	/* Move cursor back to position if it goes out of screen */
	if (currentMouse[0] > glutGet(GLUT_WINDOW_WIDTH) - 200)
	{
		glutWarpPointer(200, currentMouse[1]);
		currentMouse[0] = 200;
	}
	if (currentMouse[0] < 200)
	{
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) - 200, currentMouse[1]);
		currentMouse[0] = glutGet(GLUT_WINDOW_WIDTH) - 200;
	}

	if (currentMouse[1] > glutGet(GLUT_WINDOW_HEIGHT) - 200)
	{
		glutWarpPointer(currentMouse[0], 200);
		//currentMouse[1]-=1;
		currentMouse[1] = 200;

	}

	if (currentMouse[1] < 200)
	{
		glutWarpPointer(currentMouse[0], glutGet(GLUT_WINDOW_HEIGHT) - 200);
		//currentMouse[1]+=1;
		currentMouse[1] = glutGet(GLUT_WINDOW_HEIGHT) - 200;
	}


}

/* Takes the distance of each 3d parameter and constructs a unit vector */
float getUnitVector(float dX, float dY, float dZ)
{
	 return sqrt(dX*dX + dY*dY + dZ*dZ);
}

/* Takes 2 points in a line and returns the unit direction parameters */
float uD[3];
float * getUnitDirection(float x1, float y1, float z1, float x2, float y2, float z2)
{
	float dX = x2 - x1;
	float dY = y2 - y1;
	float dZ = z2 - z1;
	
	float uV = getUnitVector(dX, dY, dZ);
	
	uD[0] = dX/uV;
	uD[1] = dY/uV;
	uD[2] = dZ/uV;		//unit form

	return uD;
}

void displayStats()
{
	string text = "yo bro";
	glPushMatrix();
	glRasterPos2i(100, 100);
	glTranslatef(gCamPos[0], gCamPos[1], gCamPos[2]);
	glColor3fv(green);
	for (int i = 0; i < text.length(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	}
	glPopMatrix();

}

/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	

	camera->update();

	//gCamPos[0] = player1.getPos()[0] - cameraDistance*sin(gTheta[0]);
	//gCamPos[1] = player1.getPos()[1] + cameraDistance*sin(gTheta[1]);
	//gCamPos[2] = player1.getPos()[2] - cameraDistance*-cos(gTheta[2]);

	float t[3];

	for (int i = 0; i < 3; i++)
	{
		 t[i] = getUnitDirection((camera->position)[0], (camera->position)[1], (camera->position)[2],
									player1.getPos()[0], player1.getPos()[1], player1.getPos()[2])[i];
	}
	
	
	setPlayerLookDirection(t[0], t[1], t[2]);
										
	/* Adjust camera position and center based off of trigonometric rotation */
	gluLookAt((camera->position)[0], 
		(camera->position)[1], 
		(camera->position)[2],
		player1.getPos()[0],
		player1.getPos()[1],
		player1.getPos()[2],
		0,1,0);

	glColor3f(0.0, 0.0, 1.0);

	/* Draw Player1 onto the screen */
	player1.draw();

	/* Draws Enemy onto the screen */
	tempEnemy.draw();
	tower->draw();

	displayStats();
	/* Swap front buffer with back buffer */
	glutSwapBuffers();
}

/* Checks if projectile hits character */
void checkSpellCollision(Character *p, Character *e)
{
	float pX = p -> getX();
	float pY = p -> getY();
	float pZ = p -> getZ();

	float eX = e -> getX();
	float eY = e -> getY();
	float eZ = e -> getZ();

	vector<Projectile> playerCLS = p -> getSpellList();		//Player Current Live Spell list
	vector<Projectile> enemyCLS = e -> getSpellList();		//Enemy Current Live Spell list

	for (size_t i = 0; i < playerCLS.size(); i++)
	{
		/* Player Spell hits Enemy */
		if (playerCLS[i].getX() >= e->getX()-1 && playerCLS[i].getX() <= e->getX()+1+e->getSize()*2 &&
			playerCLS[i].getY() >= e->getY() && playerCLS[i].getY() <= e->getY()+1+e->getSize()*3 &&
			playerCLS[i].getZ() >= e->getZ()-1 && playerCLS[i].getZ() <= e->getZ()+1+e->getSize()*2)
		{
 			e -> loselife();		  //Decrement lifepoint
			p -> resolveSpell(i);	  //remove projectile
		}
	}
	for (size_t i = 0; i < enemyCLS.size(); i++)
	{
			/* Enemy Spell hits Player */
		if (enemyCLS[i].getX() >= p->getX()-1 && enemyCLS[i].getX() <= p->getX()+1+p->getSize()*2 &&
			enemyCLS[i].getY() >= p->getY() && enemyCLS[i].getY() <= p->getY()+1+p->getSize()*3 &&
			enemyCLS[i].getZ() >= p->getZ()-1 && enemyCLS[i].getZ() <= p->getZ()+1+p->getSize()*2)
		{
 			p -> loselife();		  //Decrement lifepoint
			e -> resolveSpell(i);	  //remove projectile
		}
	}
}

//void checkCollision(Terrain *t, Player *p)
//{
//	float pX = p->getX();
//	float pY = p->getY();
//	float pZ = p->getZ();
//	float pSize = p->getSize();
//
//	for (int i = max(0,(int)pX-4); i < min(t->getSize(),(int)pX+4); i++)
//	{
//		for (int j = max(0,(int)pZ-4); j < min(t->getSize(),(int)pZ+4); j++)
//		{
//			float tX = t->getSize();
//			float tZ = t->getSize();
//
//			if ((pX <= i+1 && pX >= i) && 
//				(pZ <= j+1 && pZ >= j) &&
//				pY <= t->getHeight()[i][j])
//			{
//				p->collidesVertically(100);
//				p->setY(t->getHeight()[i][j] + pSize);
//			}
//			else
//			{
//				//p->drop();
//			}
//		}
//	}
//}

/* Idle call back function which is run everytime nothing else is called back */
void idle()
{
	getPlayerPosition();
	checkSpellCollision(&player1, &tempEnemy);
	player1.update();
	tempEnemy.update();

	/* Call back display function */
	glutPostRedisplay();
}
void mainMenu(int value)
{

}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	
	glutInitWindowSize(800,800);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Tower Game");	//creates the window

	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);

	glutMouseFunc(mouse);
	glutPassiveMotionFunc(passiveMouse);
	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutIdleFunc(idle);

	init();

	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}
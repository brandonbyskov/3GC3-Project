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
//#include <glew.h>
//#include <freeglut.h>

//brandon's includes:
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>

#include "main.h"
#include "character.h"


using namespace std;

int main_id;
int terrain_size = 50;
int terrain_faults = 100;



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
float cameraSpeed;
float cameraDistance;
float gCamPos[3];
float gPlayerLookDirection[3];

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


//class Projectile
//{
//	int age;			//Life
//	float size;			//Size
//	float pos[3];		//Position
//	float dir[3];		//Direction
//	float vel[3];		//velocity
//	float colour[3];	//Colour
//
//public:
//
//	Projectile(float _size, float *_colour, float * _pos, float * _dir)
//	{
//		  size = _size;		
//		  for (int i = 0; i < 3; i++)
//		  {
//				colour[i] = _colour[i];
//				size = _size;
//				pos[i] = _pos[i];
//				dir[i] = _dir[i];
//				vel[i] = 1.01;		//initial speed
//		  }
//	}
//
//	void incrementAge()
//	{
//		age++;
//	}
//
//	int getAge()
//	{
//		return age;
//	}
//	float getX()
//	{
//		return pos[0];
//	}
//
//	float getY()
//	{
//		return pos[1];
//	}
//
//	float getZ()
//	{
//		return pos[2];
//	}
//
//	void move()
//	{
//		for (int i = 0; i < 3; i++)
//		{
//			pos[i] += dir[i] * vel[i];
//		}
//	}
//	
//	void draw()
//	{
//		glPushMatrix();
//		glTranslatef(pos[0], pos[1], pos[2]);
//		glColor3fv(colour);
//		glutSolidSphere(0.6, 10, 10);
//		glPopMatrix();
//	}
//};

//class Particle
//{
//	/* Particle states */
//	bool hasBounced;		
//	bool isFalling;
//
//	/* Age of particle (Incremented with each step of the animation) */
//	int age;
//	float rSpeed;
//
//	/* Physics characteristics */
//	float pos[3];	 //Position
//	float dir[3];	 //Direction
//	float rot[3];	 //Rotation
//	float normal[3]; //Normal vector
//
//	/* Random values generated for the direction, rotation and speed */
//	float dRandFactor[3];
//	float rRandFactor[3];
//
//	float colour[3];		//Colour of the particle
//	float oSpeed[3];		//Original particle speed
//	float speed[3];			//Particle speed
//
// 	float white[3];			//Colour white
//
//
//	
//	/* Sets the Normal vector of two coplanar vectors */
//	float * getNormal(float* v1[3], float* v2[3])
//	{
//		/*Cross product*/
//		normal[0] = (*v1[1]) * (*v2[2]) - (*v1[2]) * (*v2[1]);
//		normal[1] = (*v1[2]) * (*v2[0]) - (*v1[0]) * (*v2[2]);
//		normal[1] = (*v1[0]) * (*v2[1]) - (*v1[1]) * (*v2[0]);
//
//		/*Magnitude of the vector*/
//		float m = sqrt(normal[0]*normal[0] +
//					   normal[1]*normal[1] + 
//					   normal[2]*normal[2]);
//
//		/*Normalize the normal vector by dividing each component by magnitude*/
//		for (int i = 0; i < 3; i++)
//		{
//			normal[i] /= m;
//		}
//		
//		return normal;
//	}
//
//	public:
//		/* Constructor - Initializes a Particle with float position coordinates */
//		Particle(float* _pos)
//		{
//			hasBounced = false;
//			isFalling = true;
//			age = 0;	//Initialize the particle's life
//			rSpeed = 1;
//		
//			dRandFactor[0] = (float)((rand() % 100)/3);
//			dRandFactor[1] = (float)((rand() % 100));
//			dRandFactor[2] = (float)((rand() % 100)/3);
//
//			for (int i = 0; i < 3; i++)
//			{
//				rRandFactor[i] = (float)((rand() % 360));
//				speed[i] = 0.001f;		   //The higher the speed, the faster
//				oSpeed[i] = speed[i];
//				pos[i] = _pos[i];		
//				rot[i] = rRandFactor[i];
//				colour[i] = (float)(rand() % 100)/100;			//randomize particle colour
//				white[i] = 1.0;
//			}
//			oSpeed[1] = 0.01f;
//
//			dir[0] = 1.0f + dRandFactor[0];
//			dir[1] = -1.0f - dRandFactor[1];
//			dir[2] = 1.0f + dRandFactor[2];
//		}
//
//		/* Increments the age of the particle by one animation step */
//		void incrementAge()
//		{
//			age++;
//		}
//
//		void setBounceState(bool q)
//		{
//			hasBounced = q;
//		}
//
//		/* Modifies the direction coordinates of a particle */
//		void modDirection(float x, float y, float z)
//		{
//			dir[0] = x;
//			dir[1] = y;
//			dir[2] = z;
//		}
//
//		/* Modifies the position of a particle */
//		void modPosition();
//		{
//			/* Accelerate by a factor of gravity */
//			if (isFalling)
//			{
//				speed[1] *= gravity*0.95*360;
//			}
//
//			/* Decelerate by a factor of gravity */
//			else
//			{
//				/* Stop decelerating once the speed is below an extremely low amount */
//				if (speed[1] > 0.0005)
//				{
//					speed[1] /= gravity;
//				}
//
//				/* Change the direction once the particle has reached its max height */
//				else
//				{
//					dir[1] = -dir[1];
//					isFalling = true;
//				}
//			}
//
//			/* If a particle bounces off the ground, flip 'y' direction */
//			if (hasBounced)
//			{
//				dir[1] = -dir[1];
//				hasBounced = false;
//				isFalling = false;
//			
//				/* Reduce the speed of a particle when it bounces by a factor of 'friction' */
//				for (int i = 0; i < 3; i++)
//				{
//					speed[i] *= friction;
//				}
//			}
//
//			/* Finally, after modifying the direction and speed accordingly,
//				set the new position coordinates */
//			pos[0] += dir[0] * speed[0];
//			pos[1] += dir[1] * speed[1];
//			pos[2] += dir[2] * speed[2];
//
//		}
//
//		/* Increments the angle of a particle */
//		void rotate()
//		{
//			for (int i = 0; i < 3; i++)
//			{
//				
//				/* Reset angle back to 0 after a full cycle */
//				if (rot[i] >= 360)
//				{
//					rot[i] = 0;
//				}
//
//				/* Reduce rotation speed by a factor of friction */
//				rot[i] += rSpeed * friction;
//			}
//		}
//
//
//		int getAge()
//		{
//			return age;
//		}
//
//		/* Returns whether the particle is falling or not */
//		bool getFallingState()
//		{
//			return isFalling;
//		}
//		
//		/* Returns whether the particle has bounced or not */
//		bool getBounceState()
//		{
//			return hasBounced;
//		}
//
//		/* Returns the position coordinates of a particle */
//		float * getPosition()
//		{
//			return pos;
//		}
//		
//		float * getDirection()
//		{
//			return dir;
//		}
//
//		/* Draws a particle in a hierarchical fashion */
//		void draw()
//		{
//			glMaterialfv(GL_FRONT, GL_AMBIENT, colour);
//			glMaterialfv(GL_FRONT, GL_DIFFUSE, colour);
//			glMaterialfv(GL_FRONT, GL_SPECULAR, colour);
//			glMaterialfv(GL_FRONT, GL_SHININESS, white);
//		
//			glPushMatrix();
//			glTranslatef(pos[0], pos[1], pos[2]);
//			glRotatef(rot[0], rot[0], rot[1], rot[2]);
//			glColor3fv(colour);
//			glutSolidCube(0.08);
//			glPopMatrix();
//		}
//};


//class Character
//{
//protected:
//	int lifePoints;			//Life points of Character
//
//	int spellInterval;		//# of Spells per period
//	int spellIntervalCount;
//
//	int particleInterval;	//# of Particles per period
//	int particleIntervalCount;
//
//	float size;				//Size of character model
//	float pos[3];			//Position
//
//	vector<Projectile> spell;
//	vector<Particle> particle;
//
//	/* Create projectile at particular origin aimed at a direction */
//	Projectile createProjectile(float * _dir)
//	{
//		Projectile p(size, red, pos, _dir);
//		return p;
//	}
//
//	/* Create a particle at particular origin coordinates */
//	Particle createParticle(float* o)
//	{
//		float pOrigin[3];
//	
//		pOrigin[0] = o[0]+1.7;
//		pOrigin[1] = o[1]+3;	//5 units higher than origin
//		pOrigin[2] = o[2]+1.7;
//
//		Particle p(pOrigin);
//		return p;
//	}
//
//	/* Update spell parameters */
//	void updateSpells()
//	{
//		for (size_t i = 0; i < spell.size(); i++)
//		{
//			/* Increment age */
//			spell[i].incrementAge();
//
//			/* Increment the particle's position and rotate */
//			spell[i].move();
//
//			/* Delete particle if it is over the max age */
//			if (spell[i].getAge() > gMaxSpellAge)
//			{
//				spell.erase(spell.begin() + i);
//			}
//		}
//	}
//			
//	/* Update particle parameters */
//	void updateParticles()
//	{
//		for (size_t i = 0; i < particle.size(); i++)
//		{
//			/* Increment age */
//			particle[i].incrementAge();
//			/* Increment the particle's position and rotate */
//			particle[i].modPosition();
//			particle[i].rotate();
//
//			/* Delete particle if it is over the max age */
//			if (particle[i].getAge() > gMaxParticleAge)
//			{
//				particle.pop_back();
//			}
//		}
//	}
//
//	/* Draws all visible spells */
//	void drawSpells()
//	{
//		for (size_t i = 0; i < spell.size(); i++)
//		{
//			/* Draw each spell projectile */
//			spell[i].draw();
//		}
//	}
//	
//	/* Draws all particles */
//	void drawParticles()
//	{
//		particleIntervalCount++;
//		if (particleIntervalCount % particleInterval == 0)
//		{
//			/* Insert a new Particle at the back of the Particle vector list */
//			particle.push_back(createParticle(pos));
//			particleIntervalCount = 1;
//		}
//		for (size_t i = 0; i < particle.size(); i++)
//		{
//			/* Draw each particle */
//			particle[i].draw();
//		}
//	}
//
//	/* Draws the character model figure */
//	virtual void drawFigure() = 0;
//
//public:
//
//	Character (float * _pos, float _size)
//	{
//		lifePoints = 3;
//		size = _size;
//
//		particleIntervalCount = 0;
//		particleInterval = 10;
//
//		spellIntervalCount = 0;
//		spellInterval = 10;
//				
//		for (int i = 0; i < 3; i++)
//		{
//			pos[i] = _pos[i];
//		}
//	}
//
//	/* Returns the position coordinates of a character */
//	float * getPos()
//	{
//		return pos;
//	}
//
//	/* Returns X coordinate of player */
//	float getX()
//	{
//		return pos[0];
//	}
//
//	/* Returns Y coordinate of player */
//	float getY()
//	{
//		return pos[1];
//	}
//
//	/* Returns Z coordinate of player */
//	float getZ()
//	{
//		return pos[2];
//	}
//
//	/* Returns size of Character Model */
//	float getSize()
//	{
//		return size;
//	}
//
//	/* Updates movement, spells, particle parameters...ect. */
//	virtual void update() = 0;
//
//	/* Draw's character model, spells, particles */
//	void draw()
//	{
//		drawFigure();
//		drawParticles();
//		drawSpells();
//	}
//};

class Enemy : public Character
{
	void drawFigure()
	{
		//Body
		glMaterialfv(GL_FRONT, GL_AMBIENT, blue);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
		glMaterialfv(GL_FRONT, GL_SPECULAR, blue);
		glMaterialfv(GL_FRONT, GL_SHININESS, white);

		glPushMatrix();
		glTranslatef(pos[0]+2, pos[1]+2, pos[2]+2);
		glRotatef(-90,1,0,0);
		glRotatef(-90,0,0,1);
		glutSolidCylinder(size, size*2, 10, 10);

			//Head
			glMaterialfv(GL_FRONT, GL_AMBIENT, skin);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, skin);
			glMaterialfv(GL_FRONT, GL_SPECULAR, skin);
			glMaterialfv(GL_FRONT, GL_SHININESS, skin);
			glColor3fv(skin);
			glPushMatrix();
			glTranslatef(0.0, 0.0, size*2);
			glutSolidSphere(size, 10, 10);

				//HatBase
				glMaterialfv(GL_FRONT, GL_AMBIENT, blue);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
				glMaterialfv(GL_FRONT, GL_SPECULAR, black);
				glMaterialfv(GL_FRONT, GL_SHININESS, white);
				glColor3fv(purple);
				glPushMatrix();
				glTranslatef(0.0, 0.0, size * 0.8);
				glutSolidCone(size*2, size*0.8, 10, 10);

					//HatTop
					glMaterialfv(GL_FRONT, GL_AMBIENT, blue);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
					glMaterialfv(GL_FRONT, GL_SPECULAR, black);
					glMaterialfv(GL_FRONT, GL_SHININESS, white);
					glColor3fv(purple);
					glPushMatrix();
					//glTranslatef(0.0, 0.0, size);
					glRotatef(30, 1.0, 0.0, 0.0);
					glutSolidCone(size, size*3, 10, 10);

					glPopMatrix();
				glPopMatrix();

				//Left Eye
				glMaterialfv(GL_FRONT, GL_AMBIENT, black);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
				glMaterialfv(GL_FRONT, GL_SPECULAR, black);
				glMaterialfv(GL_FRONT, GL_SHININESS, white);
				glColor3fv(black);
				glPushMatrix();
				glTranslatef(size*0.3, size*0.7, size*0.5);
				glutSolidSphere(size*0.2, 10, 10);
				glPopMatrix();

				//Right Eye
				glPushMatrix();
				glTranslatef(-size*0.3, size*0.8, size*0.5);
				glutSolidSphere(size*0.2, 10, 10);
				glPopMatrix();

				//Beard
				glMaterialfv(GL_FRONT, GL_AMBIENT, grey);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
				glMaterialfv(GL_FRONT, GL_SPECULAR, grey);
				glMaterialfv(GL_FRONT, GL_SHININESS, grey);
				glColor3fv(white);
				glPushMatrix();
				glTranslatef(0.0, size*0.6, -size*0.2);
				glRotatef(-150, 1.0, 0.0, 0.0);
				glutSolidCone(size/2, size*2, 10, 10);
				glPopMatrix();

			glPopMatrix();	//Head

			//Arms
			glMaterialfv(GL_FRONT, GL_AMBIENT, blue);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
			glMaterialfv(GL_FRONT, GL_SPECULAR, blue);
			glMaterialfv(GL_FRONT, GL_SHININESS, white);
			glColor3fv(purple);

			//right
			glPushMatrix();
			glTranslatef(1.1*size, 0.0 , 0.3);
			glRotatef(150, -0.5, 1.0, 0.8);
			glRotatef(60, 1.0, 1.0, 0.0);
			glutSolidCylinder(size/2, size*2, 10, 10);
			glPopMatrix();

			//left
			glPushMatrix();
			glTranslatef(-1.1*size, 0.0, 0.3);
			glRotatef(150, -0.5, 1.0, 0.8);
			glRotatef(60, 1.0, 1.0, 0.0);
			glutSolidCylinder(size/2, size*2, 10, 10);

				//staffBase
				glMaterialfv(GL_FRONT, GL_AMBIENT, wood);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, wood);
				glMaterialfv(GL_FRONT, GL_SPECULAR, wood);
				glMaterialfv(GL_FRONT, GL_SHININESS, black);
				glColor3fv(wood);
				glPushMatrix();
				glTranslatef(0.0, 0.0, size*1.4);
				glRotatef(-60, 1.0, 1.0, 0.0);
				glutSolidCylinder(size/6, size*4, 10, 10);

					//staffTop
					glMaterialfv(GL_FRONT, GL_AMBIENT, red);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
					glMaterialfv(GL_FRONT, GL_SPECULAR, red);
					glMaterialfv(GL_FRONT, GL_SHININESS, black);
					glColor3fv(red);
					glPushMatrix();
					glTranslatef(0.0, 0.0, size*4);
					glRotatef(0.0, 1.0, 1.0, 0.0);
					glutSolidSphere(size/3, size*4, 10);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();

			//Bottom
			glMaterialfv(GL_FRONT, GL_AMBIENT, black);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
			glMaterialfv(GL_FRONT, GL_SPECULAR, blue);
			glMaterialfv(GL_FRONT, GL_SHININESS, black);
			glColor3fv(purple);
			glPushMatrix();
			glTranslatef(0.0, 0.0, -1.0);
			glutSolidCone(size*1.5, size*4, 10, 10);
			glPopMatrix();

		glPopMatrix();
	}

public:
	Enemy(float* _o, float _size) : Character(_o, _size)
	{
	}

	void update()
	{
		updateParticles();
		updateSpells();
	}
};

class Player : public Character
{
		bool hasVerticalCollision;
		bool hasHorizontalCollision;
		bool movingForward, movingBackward, movingLeft, movingRight, falling, levitating;

		float dir[3];		//Direction of travel
		float rot[3];		//Orientation
		float velocity[3];		//velocity of movement
		float armRotFactor; //arm Rotation

		void modDirection()
		{
			for (int i = 0; i < 3; i++)
			{
				dir[i] = gPlayerLookDirection[i];
			}
		}

		/* Increments a player's position appropriate to the direction they are moving in */
		void move()
		{

			/* Moves player up */
			if (levitating && !falling)
			{
				particleInterval = 2;
				velocity[1] += gravity*5;
				pos[1] += velocity[1];
			}

			/* Moves player down */
			if (falling && !levitating)
			{
				particleInterval = 20;
				velocity[1] += gravity;
				pos[1] -= velocity[1];
			}
				
			/* Moves player FORWARDS at a set speed */
			if (movingForward)
			{
				armRotFactor += 0.1;
				velocity[0] = 0.1;		
	   			pos[0] += velocity[0];
			}

			/* Moves player BACKWARDS at a set speed */
			if (movingBackward)
			{
				armRotFactor += 0.1;
				velocity[0] = -0.1;
	   			pos[0] += velocity[0];
			}

			/* Strafes player to the RIGHT at a set speed */
			if (movingRight)
			{
				armRotFactor += 0.1;
				velocity[2] = 0.1;
	   			pos[2] += 1.0 * velocity[2];
			}

			/* Strafes player to the LEFT at a set speed */
			if (movingLeft)
			{
				armRotFactor += 0.1;
				velocity[2] = -0.1;
	   			pos[2] += 1.0 * velocity[2];
			}

			/* DECELERATES velocity of player when they are not moving forward/backward */
			if (!movingBackward && !movingForward)
			{
				pos[0] += velocity[0];
				if (velocity[0] < -0.0001 || velocity[0] > 0.0001)	//limit
				{
					velocity[0] *= friction;
				}
				else
				{
					velocity[0] = 0;
				}
			}

			/* DECELERATES velocity of player when they are not moving side to side */
			if (!movingRight && !movingLeft)
			{
				pos[2] += velocity[2];
				if (velocity[2] < -0.0001 || velocity[2] > 0.0001) //limit
				{
					velocity[2] *= friction;
				}
				else
				{
					velocity[2] = 0;
				}
			}
				
			/* Decelerate player when they activate levitation */
			if (falling && levitating)
			{
				pos[1] -= velocity[1];
				if (velocity[1] < -0.1 || velocity[1] > 0.1) //limit
				{
					velocity[1] *= friction*1.03;
				}
				else
				{
						
					falling = false;
				}
				particleInterval = 20;

			}

			/* Decelerate player when they deactivate levitation */
			if (!falling && !levitating)
			{
				pos[1] += velocity[1];
				if (velocity[1] < -0.1 || velocity[1] > 0.1) //limit
				{
					velocity[1] *= friction*1.03;
				}
				else
				{
					falling = true;
				}
				particleInterval = 2;
			}
		}
		void drawFigure()
		{
			//Body
			glMaterialfv(GL_FRONT, GL_AMBIENT, blue);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
			glMaterialfv(GL_FRONT, GL_SPECULAR, blue);
			glMaterialfv(GL_FRONT, GL_SHININESS, white);

			glPushMatrix();
			glTranslatef(pos[0]+2, pos[1]+2, pos[2]+2);
			glRotatef(-90,1,0,0);
			glRotatef(-90,0,0,1);
			glutSolidCylinder(size, size*2, 10, 10);

				//Head
				glMaterialfv(GL_FRONT, GL_AMBIENT, skin);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, skin);
				glMaterialfv(GL_FRONT, GL_SPECULAR, skin);
				glMaterialfv(GL_FRONT, GL_SHININESS, skin);
				glColor3fv(skin);
				glPushMatrix();
				glTranslatef(0.0, 0.0, size*2);
				glutSolidSphere(size, 10, 10);

					//HatBase
					glMaterialfv(GL_FRONT, GL_AMBIENT, blue);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
					glMaterialfv(GL_FRONT, GL_SPECULAR, black);
					glMaterialfv(GL_FRONT, GL_SHININESS, white);
					glColor3fv(blue);
					glPushMatrix();
					glTranslatef(0.0, 0.0, size * 0.8);
					glutSolidCone(size*2, size*0.8, 10, 10);

						//HatTop
						glMaterialfv(GL_FRONT, GL_AMBIENT, blue);
						glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
						glMaterialfv(GL_FRONT, GL_SPECULAR, black);
						glMaterialfv(GL_FRONT, GL_SHININESS, white);
						glColor3fv(blue);
						glPushMatrix();
						//glTranslatef(0.0, 0.0, size);
						glRotatef(30, 1.0, 0.0, 0.0);
						glutSolidCone(size, size*3, 10, 10);

						glPopMatrix();
					glPopMatrix();

					//Left Eye
					glMaterialfv(GL_FRONT, GL_AMBIENT, black);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
					glMaterialfv(GL_FRONT, GL_SPECULAR, black);
					glMaterialfv(GL_FRONT, GL_SHININESS, white);
					glColor3fv(black);
					glPushMatrix();
					glTranslatef(size*0.3, size*0.7, size*0.5);
					glutSolidSphere(size*0.2, 10, 10);
					glPopMatrix();

					//Right Eye
					glPushMatrix();
					glTranslatef(-size*0.3, size*0.8, size*0.5);
					glutSolidSphere(size*0.2, 10, 10);
					glPopMatrix();

					//Beard
					glMaterialfv(GL_FRONT, GL_AMBIENT, grey);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
					glMaterialfv(GL_FRONT, GL_SPECULAR, grey);
					glMaterialfv(GL_FRONT, GL_SHININESS, grey);
					glColor3fv(grey);
					glPushMatrix();
					glTranslatef(0.0, size*0.6, -size*0.2);
					glRotatef(-150, 1.0, 0.0, 0.0);
					glutSolidCone(size/2, size*2, 10, 10);
					glPopMatrix();

				glPopMatrix();	//Head

				//Arms
				glMaterialfv(GL_FRONT, GL_AMBIENT, blue);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
				glMaterialfv(GL_FRONT, GL_SPECULAR, blue);
				glMaterialfv(GL_FRONT, GL_SHININESS, white);
				glColor3fv(blue);

				//right
				glPushMatrix();
				glTranslatef(1.1*size, 0.0 , 0.3);
				glRotatef(150, -0.5, 1.0, 0.8);
				glRotatef(60*sin(-armRotFactor), 1.0, 1.0, 0.0);
				glutSolidCylinder(size/2, size*2, 10, 10);
				glPopMatrix();

				//left
				glPushMatrix();
				glTranslatef(-1.1*size, 0.0, 0.3);
				glRotatef(150, -0.5, 1.0, 0.8);
				glRotatef(60*sin(armRotFactor), 1.0, 1.0, 0.0);
				glutSolidCylinder(size/2, size*2, 10, 10);

					//staffBase
					glMaterialfv(GL_FRONT, GL_AMBIENT, wood);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, wood);
					glMaterialfv(GL_FRONT, GL_SPECULAR, wood);
					glMaterialfv(GL_FRONT, GL_SHININESS, black);
					glColor3fv(wood);
					glPushMatrix();
					glTranslatef(0.0, 0.0, size*1.4);
					glRotatef(-60, 1.0, 1.0, 0.0);
					glutSolidCylinder(size/6, size*4, 10, 10);

						//staffTop
						glMaterialfv(GL_FRONT, GL_AMBIENT, red);
						glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
						glMaterialfv(GL_FRONT, GL_SPECULAR, red);
						glMaterialfv(GL_FRONT, GL_SHININESS, black);
						glColor3fv(red);
						glPushMatrix();
						glTranslatef(0.0, 0.0, size*4);
						glRotatef(0.0, 1.0, 1.0, 0.0);
						glutSolidSphere(size/3, size*4, 10);
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();

				//Bottom
				glMaterialfv(GL_FRONT, GL_AMBIENT, black);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
				glMaterialfv(GL_FRONT, GL_SPECULAR, blue);
				glMaterialfv(GL_FRONT, GL_SHININESS, black);
				glColor3fv(blue);
				glPushMatrix();
				glTranslatef(0.0, 0.0, -1.0);
				glutSolidCone(size*1.5, size*4, 10, 10);
				glPopMatrix();

			glPopMatrix();
		}

		public:
			Player(float* _o, float _size): Character(_o, _size)
			{
				hasHorizontalCollision = false;
				movingForward = false;
				movingBackward = false;
				movingLeft = false;
				movingRight = false;
				falling = true;
				levitating = false;
				armRotFactor = 1.0;
				
				for (int i = 0; i < 3; i++)
				{
					rot[i] = 1.0;
					dir[i] = 1.0;
					velocity[i] = 0.0;		//Player is initially not moving
				}
			}

			void collidesVertically(float y)
			{
				falling = false;
			}

			void drop()
			{
				falling = true;
			}

			void setY(float _y)
			{
				pos[1] = _y;
			}

			void setMovement(int v)
			{
				switch (v)
				{
					case 0:
						movingBackward = true;
						break;
					case 1:
						movingForward = true;
						break;
					case 2:
						movingLeft = true;
						break;
					case 3:
						movingRight = true;
						break;
					case 4:
						levitating = true;
						break;
					default:
						break;
				}
			}

			void cancelMovement(int v)
			{
				switch (v)
				{
					case 0:
						movingBackward = false;
						break;
					case 1:
						movingForward = false;
						break;
					case 2:
						movingLeft = false;
						break;
					case 3:
						movingRight = false;
						break;
					case 4:
						levitating = false;
						break;
					default:
						break;
				}
			}

			void castSpell()
			{
				/* Insert a new Particle at the back of the Particle vector list */
				spell.push_back(createProjectile(gPlayerLookDirection));
			}

			void update()
			{
				updateParticles();
				updateSpells();
				move();
			}
};



/* Platform class - Design for a 6 sided rectangular prism */
class Platform
{
	float origin[3];

	/* Depth, width and height, respectively */
	float d;
	float w;
	float h;

	/* Two toned colour of platform */
	float colour[3];
	float colour2[3];

	/* cube - takes an array of 8 vertices, and draws 6 faces
	 *  with drawPolygon, making up a box
	 */
	void cube(float v[8][3])
	{
		//side
		glColor3f(1.0,1.0,0.8);
		drawPolygon(0, 3, 2, 1, v);

		//side
		drawPolygon(1, 0, 4, 5, v);

		//top
		glColor3f(1.0,1.0,1.0);
		drawPolygon(5, 1, 2, 6, v);

		glColor3f(1.0,1.0,0.8);
		drawPolygon(2, 3, 7, 6, v);
		drawPolygon(6, 5, 4, 7, v);
		drawPolygon(4, 0, 3, 7, v);
	}

	/* Draws a side of the cube */
	void drawPolygon(int a, int b, int c, int d, float v[8][3])
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, colour2);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, colour2);
		glMaterialfv(GL_FRONT, GL_SPECULAR, colour2);
		glMaterialfv(GL_FRONT, GL_SHININESS, colour);

		glNormal3f(0.0, 1.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex3fv(v[a]);
			glVertex3fv(v[b]);
			glVertex3fv(v[c]);
			glVertex3fv(v[d]);
		glEnd();
	}

	public:
		/* Constructor - Initializes a platform with specified by the origin coordinates, depth, width and height, respectively*/
		Platform(float* o, float _d, float _w, float _h)
		{
			d = _d;
			w = _w;
			h = _h;

			for (int i = 0; i < 3; i++)
			{
				origin[i] = o[i];
				colour[i] = 1.0;
			}
			colour2[0] = 1.0; 
			colour2[1] = 1.0;
			colour2[2] = 0.8;
		}

		/* Draws the platform using a center origin */
		void drawPlatform()
		{
			float vertices[8][3] = { {origin[0]-w/2, origin[1]-h/2, origin[2]+d/2},
									 {origin[0]-w/2, origin[1]+h/2, origin[2]+d/2},
									 {origin[0]+w/2, origin[1]+h/2, origin[2]+d/2},
									 {origin[0]+w/2, origin[1]-h/2, origin[2]+d/2}, 
									 {origin[0]-w/2, origin[1]-h/2, origin[2]-d/2}, 
									 {origin[0]-w/2, origin[1]+h/2, origin[2]-d/2}, 
									 {origin[0]+w/2, origin[1]+h/2, origin[2]-d/2},
									 {origin[0]+w/2, origin[1]-h/2, origin[2]-d/2} };

			cube(vertices);
		}

		/* Returns the origin coordinates of the platform */
		float * getOrigin()
		{
			return origin;
		}

		/* Returns the depth of the platform */
		float getDepth()
		{
			return d; 
		}
		
		/* Returns the height of the platform */
		float getHeight()
		{
			return h;
		}

		/* Returns the width of the platform */
		float getWidth()
		{
			return w;
		}

};

vector<Platform> platform;


class Terrain {

	int** heightmap;
	int size;
	int maxHeight;
	int minHeight;
public:

	Terrain() {
		size = terrain_size;
		int fault_iterations = terrain_faults;
		maxHeight = 0;

		heightmap = new int*[size];
		for(int i = 0; i < size; i++) {
			heightmap[i] = new int[size];
		}

		for(int i = 0;i<size;i++) {
			for(int j = 0;j<size;j++) {
				heightmap[i][j] = 0;
			}
		}
		this->build(fault_iterations);

		for(int i = 0;i<size;i++) {
			for(int j = 0;j<size;j++) {
				maxHeight = max(heightmap[i][j], maxHeight);
				minHeight = min(heightmap[i][j], minHeight);
			}
		}
	};

	//faults the terrain once
	void fault() {
		float v = rand();
		float a = sin(v);
		float b = cos(v);
		float d = sqrt(2*size*size);
		// rand() / RAND_MAX gives a random number between 0 and 1.
		// therefore c will be a random number between -d/2 and d/2
		float c = ((double)rand() / RAND_MAX) * d - d/2;

		//int displacement = (((double)rand() / RAND_MAX)>.5)?1:-1;


		for(int i = 0;i<size;i++) {
			for(int j = 0;j<size;j++) {
				if (a*i + b*j - c > 0) {
					(heightmap[i][j]) += 1;
				}
				else {
					(heightmap[i][j]) -= 1;
				}
			}
		}
		
	}

	//builds a terrain by fualting it several times
	void build(int iterations) {
		if (iterations > 0) {
			for (int i = 1; i<=iterations;i++) {
				this->fault();
			}
		}
	}

	//resets the array using global size and fault parameters.
	void reset()
	{
		//delete old heightmap
		for (int i=0; i < size; i++)
		{
			delete [] heightmap[i];
		}
		delete [] heightmap;

		size = terrain_size;
		int fault_iterations = terrain_faults;

		heightmap = new int*[size];
		for(int i = 0; i < size; i++) {
			heightmap[i] = new int[size];
		}

		for(int i = 0;i<size;i++) {
			for(int j = 0;j<size;j++) {
				heightmap[i][j] = 0;
			}
		}
		this->build(fault_iterations);
	}


	int ** getHeight()
	{
		return heightmap;
	}

	int getSize()
	{
		return size;
	}

	int getX(float _x)
	{
		
	}


	//displays the terrain
	void display() {
		
		if (wireframeMode)
		{
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		}
		for(int i = 0;i<size-1;i++) {
			for(int j = 0;j<size-1;j++) {
				glBegin(GL_POLYGON);
					float avgHeight;
					if (colorMapMode)
					{
						avgHeight = heightmap[i][j] + heightmap[i+1][j] + heightmap[i+1][j+1] + heightmap[i][j+1];

						glColor3f(.5*avgHeight/(float)maxHeight-minHeight,1-(avgHeight/(float)maxHeight-minHeight),0);
					}
					else
					{
						glColor3ub(0,255,0);
					}
						
					glMaterialfv(GL_FRONT, GL_AMBIENT, black);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
					glMaterialfv(GL_FRONT, GL_SPECULAR, black);
					glMaterialfv(GL_FRONT, GL_SHININESS, green);

					glVertex3f(i, heightmap[i][j], j);
					glVertex3f(i+1, heightmap[i+1][j], j);
					glVertex3f(i+1, heightmap[i+1][j+1], j+1);
					glVertex3f(i, heightmap[i][j+1], j+1);

					
				glEnd();
			}
		}
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	}

};

Terrain *terrain;

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

/* Create a particle at particular origin coordinates */

/* Creates a platform at the particular origin coordinates with a specified width and heigth, respectively */
Platform createPlatform(float* o, float d, float w, float h)
{
	float pOrigin[3];
	for (int i = 0; i < 3; i++)
	{
		pOrigin[i] = o[i];
	}

	Platform p(pOrigin, d, w, h);
	return p;
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
	cameraSpeed = 0.08;
	cameraDistance = 20;

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

	/* Create a platform */
	platform.push_back(createPlatform(gOrigin, 15, 15, 1));
	terrain = new Terrain();
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
	//Wireframe mode
	if (key == 'f' || key == 'F')
	{
		wireframeMode = !wireframeMode;
	}
	if (key == 'c' || key == 'C')
	{
		colorMapMode = !colorMapMode;
	}


	//Rebuild Terrain
	if (key == 'r' || key == 'R')
	{
		terrain->reset();
	}

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
	/* Rotate camera angle left if mouse moves left */
	if (x - currentMouse[0] < 0)
	{
		gTheta[2] -= cameraSpeed;
		gTheta[0] -= cameraSpeed;
	}

	/* Rotate camera angle Right if mouse moves right */
	if (x - currentMouse[0] > 0)
	{
		gTheta[2] += cameraSpeed;
		gTheta[0] += cameraSpeed;
	}
	
	/* Rotate camera Down if mouse moves down */
	if (y - currentMouse[1] < 0 && gTheta[1] > -2.0)
	{
		gTheta[1] -= cameraSpeed;
	}

	/* Rotate camera Up if mouse moves up */
	if (y - currentMouse[1] > 0 && gTheta[1] < 2.0)
	{
		gTheta[1] += cameraSpeed;
	}

	/* Set current mouse to current position */
	currentMouse[0] = x;
	currentMouse[1] = y;
											  
	/* Move cursor back to position if it goes out of screen */
	if (currentMouse[0] > glutGet(GLUT_WINDOW_WIDTH) - 400)
	{
		glutWarpPointer(200, currentMouse[1]);
		currentMouse[0]--;
	}
	if (currentMouse[0] < 200)
	{
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) - 400, currentMouse[1]);
		currentMouse[0]++;
	}

	if (currentMouse[1] > glutGet(GLUT_WINDOW_HEIGHT) - 200)
	{
		glutWarpPointer(currentMouse[0], 100);
		currentMouse[1]--;
	}

	if (currentMouse[1] < 100)
	{
		glutWarpPointer(currentMouse[0], glutGet(GLUT_WINDOW_HEIGHT) - 200);
		currentMouse[1]++;
	}
}

/* Takes the distance of each 3d parameter and constructs a unit vector */
float getUnitVector(float dX, float dY, float dZ)
{
	 return sqrt(dX*dX + dY*dY + dZ*dZ);
}

/* Takes 2 points in a line and returns the unit direction parameters */
float * getUnitDirection(float x1, float y1, float z1, float x2, float y2, float z2)
{
	float dX = x2 - x1;
	float dY = y2 - y1;
	float dZ = z2 - z1;
	
	float uV = getUnitVector(dX, dY, dZ);
	float uD[] = {dX/uV, dY/uV, dZ/uV};		//unit form

	return uD;
}


/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gCamPos[0] = player1.getPos()[0] - cameraDistance*sin(gTheta[0]);
	gCamPos[1] = player1.getPos()[1] + cameraDistance*sin(gTheta[1]);
	gCamPos[2] = player1.getPos()[2] - cameraDistance*-cos(gTheta[2]);

	float t[3];

	for (int i = 0; i < 3; i++)
	{
		 t[i] = getUnitDirection(gCamPos[0], gCamPos[1], gCamPos[2],
									player1.getPos()[0], player1.getPos()[1], player1.getPos()[2])[i];
	}
	
	
	setPlayerLookDirection(t[0], t[1], t[2]);
										
	/* Adjust camera position and center based off of trigonometric rotation */
	gluLookAt(gCamPos[0], 
		gCamPos[1], 
		gCamPos[2],
		player1.getPos()[0],
		player1.getPos()[1],
		player1.getPos()[2],
		0,1,0);

	glColor3f(0.2,0.2,0.2);

	//platform.front().drawPlatform();
	terrain->display();

	glColor3f(0.0, 0.0, 1.0);

	/* Draw Player1 onto the screen */
	player1.draw();

	/* Draws Enemy onto the screen */
	tempEnemy.draw();

	/* Swap front buffer with back buffer */
	glutSwapBuffers();
}

void checkCollision(Terrain *t, Player *p)
{
	float pX = p->getX();
	float pY = p->getY();
	float pZ = p->getZ();
	float pSize = p->getSize();

	for (int i = max(0,(int)pX-4); i < min(t->getSize(),(int)pX+4); i++)
	{
		for (int j = max(0,(int)pZ-4); j < min(t->getSize(),(int)pZ+4); j++)
		{
			float tX = t->getSize();
			float tZ = t->getSize();

			if ((pX <= i+1 && pX >= i) && 
				(pZ <= j+1 && pZ >= j) &&
				pY <= t->getHeight()[i][j])
			{
				p->collidesVertically(100);
				p->setY(t->getHeight()[i][j] + pSize);
			}
			else
			{
				//p->drop();
			}
		}
	}
}

/* Idle call back function which is run everytime nothing else is called back */
void idle()
{
	checkCollision(terrain, &player1);
	player1.update();
	tempEnemy.update();

	/* Call back display function */
	glutPostRedisplay();
}
void mainMenu(int value)
{
	if (value == 1)
		colorMapMode = !colorMapMode;
	if (value == 2)
		terrain->reset();
}

void adjustTerrainSize(int value){
	terrain_size = value;
}

void adjustTerrainFaults(int value){
	terrain_faults = value;
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Terrain");	//creates the window

	//int terrain_size_submenu = glutCreateMenu(adjustTerrainSize);
	//	glutAddMenuEntry("50", 50);
	//	glutAddMenuEntry("100", 100);
	//	glutAddMenuEntry("200", 200);
	//	glutAddMenuEntry("300", 300);
	//int faults_submenu = glutCreateMenu(adjustTerrainFaults);
	//	glutAddMenuEntry("50", 50);
	//	glutAddMenuEntry("100", 100);
	//	glutAddMenuEntry("200", 200);
	//	glutAddMenuEntry("400", 400);
	//main_id = glutCreateMenu(mainMenu);
	//	glutAddSubMenu("Terrain Size", terrain_size_submenu);
	//	glutAddSubMenu("Fault Iterations", faults_submenu);
	//	glutAddMenuEntry("Toggle Color Map   'C'", 1);
	//	glutAddMenuEntry("Reset              'R'", 2);
	//glutAttachMenu(GLUT_RIGHT_BUTTON);

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
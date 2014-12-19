// functions for Core

#include <math.h>
#include <stdlib.h>

#include "particle.h"
#include "main.h"
#include "gllibs.h"

/* Constructor - Initializes a Particle with float position coordinates */
Particle::Particle(float* _pos)
{
	hasBounced = false;
	isFalling = true;
	age = 0;	//Initialize the particle's life
	rSpeed = 1;
		
	dRandFactor[0] = (float)((rand() % 100)/3);
	dRandFactor[1] = (float)((rand() % 100));
	dRandFactor[2] = (float)((rand() % 100)/3);

	for (int i = 0; i < 3; i++)
	{
		rRandFactor[i] = (float)((rand() % 360));
		speed[i] = 0.001f;		   //The higher the speed, the faster
		oSpeed[i] = speed[i];
		pos[i] = _pos[i];		
		rot[i] = rRandFactor[i];
		colour[i] = (float)(rand() % 100)/100;			//randomize particle colour
		white[i] = 1.0;
	}
	oSpeed[1] = 0.01f;

	dir[0] = 1.0f + dRandFactor[0];
	dir[1] = -1.0f - dRandFactor[1];
	dir[2] = 1.0f + dRandFactor[2];
}

Particle::~Particle() {
}

/* Increments the age of the particle by one animation step */
void Particle::incrementAge()
{
	age++;
}

void Particle::setBounceState(bool q)
{
	hasBounced = q;
}

/* Modifies the direction coordinates of a particle */
void Particle::modDirection(float x, float y, float z)
{
	dir[0] = x;
	dir[1] = y;
	dir[2] = z;
}

/* Modifies the position of a particle */
void Particle::modPosition()
{
	/* Accelerate by a factor of gravity */
	if (isFalling)
	{
		speed[1] *= gravity*0.95*360;
	}

	/* Decelerate by a factor of gravity */
	else
	{
		/* Stop decelerating once the speed is below an extremely low amount */
		if (speed[1] > 0.0005)
		{
			speed[1] /= gravity;
		}

		/* Change the direction once the particle has reached its max height */
		else
		{
			dir[1] = -dir[1];
			isFalling = true;
		}
	}

	/* If a particle bounces off the ground, flip 'y' direction */
	if (hasBounced)
	{
		dir[1] = -dir[1];
		hasBounced = false;
		isFalling = false;
			
		/* Reduce the speed of a particle when it bounces by a factor of 'friction' */
		for (int i = 0; i < 3; i++)
		{
			speed[i] *= friction;
		}
	}

	/* Finally, after modifying the direction and speed accordingly,
		set the new position coordinates */
	pos[0] += dir[0] * speed[0];
	pos[1] += dir[1] * speed[1];
	pos[2] += dir[2] * speed[2];

}

/* Increments the angle of a particle */
void Particle::rotate()
{
	for (int i = 0; i < 3; i++)
	{
				
		/* Reset angle back to 0 after a full cycle */
		if (rot[i] >= 360)
		{
			rot[i] = 0;
		}

		/* Reduce rotation speed by a factor of friction */
		rot[i] += rSpeed * friction;
	}
}


int Particle::getAge()
{
	return age;
}

/* Returns whether the particle is falling or not */
bool Particle::getFallingState()
{
	return isFalling;
}
		
/* Returns whether the particle has bounced or not */
bool Particle::getBounceState()
{
	return hasBounced;
}

/* Returns the position coordinates of a particle */
float * Particle::getPosition()
{
	return pos;
}
		
float * Particle::getDirection()
{
	return dir;
}

/* Draws a particle in a hierarchical fashion */
void Particle::draw()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, colour);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, colour);
	glMaterialfv(GL_FRONT, GL_SPECULAR, colour);
	glMaterialfv(GL_FRONT, GL_SHININESS, white);
		
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(rot[0], rot[0], rot[1], rot[2]);
	glColor3fv(colour);
	glutSolidCube(0.08);
	glPopMatrix();
}

/* Sets the Normal vector of two coplanar vectors */
float * Particle::getNormal(float* v1[3], float* v2[3])
{
	/*Cross product*/
	normal[0] = (*v1[1]) * (*v2[2]) - (*v1[2]) * (*v2[1]);
	normal[1] = (*v1[2]) * (*v2[0]) - (*v1[0]) * (*v2[2]);
	normal[1] = (*v1[0]) * (*v2[1]) - (*v1[1]) * (*v2[0]);

	/*Magnitude of the vector*/
	float m = sqrt(normal[0]*normal[0] +
					normal[1]*normal[1] + 
					normal[2]*normal[2]);

	/*Normalize the normal vector by dividing each component by magnitude*/
	for (int i = 0; i < 3; i++)
	{
		normal[i] /= m;
	}
		
	return normal;
}
// functions for Core

#include "projectile.h"
#include "gllibs.h"

Projectile::Projectile(float _size, float *_colour, float * _pos, float * _dir)
{
	size = _size;		
	for (int i = 0; i < 3; i++)
	{
		colour[i] = _colour[i];
		size = _size;
		pos[i] = _pos[i];
		dir[i] = _dir[i];
		vel[i] = 1.01;		//initial speed
	}
}

Projectile::~Projectile() {
}

void Projectile::incrementAge()
{
	age++;
}

int Projectile::getAge()
{
	return age;
}
float Projectile::getX()
{
	return pos[0];
}

float Projectile::getY()
{
	return pos[1];
}

float Projectile::getZ()
{
	return pos[2];
}

void Projectile::move()
{
	for (int i = 0; i < 3; i++)
	{
		pos[i] += dir[i] * vel[i];
	}
}
	
void Projectile::draw()
{
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	glColor3fv(colour);
	glutSolidSphere(0.6, 10, 10);
	glPopMatrix();
}


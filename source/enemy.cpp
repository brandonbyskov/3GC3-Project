#include "enemy.h"
#include "main.h"

#include "gllibs.h"

Enemy::Enemy(float* _o, float _size) : Character(_o, _size) {
}

Enemy::~Enemy() {
	isVisible = true;
	for (int i = 0; i < 3; i++)
	{
		directionTowardsPlayer[i] = 0.0;
	}
}

/* Takes the distance of each 3d parameter and constructs a unit vector */
float Enemy::AIGetUnitVector(float dX, float dY, float dZ)
{
	 return sqrt(dX*dX + dY*dY + dZ*dZ);
}

/* Takes 2 points in a line and returns the unit direction parameters */

float * Enemy::AIGetUnitDirection(float x1, float y1, float z1, float x2, float y2, float z2)
{
	float dX = x2 - x1;
	float dY = y2 - y1;
	float dZ = z2 - z1;
	
	float uV = AIGetUnitVector(dX, dY, dZ);
	float uD[3];
	uD[0] = dX/uV;
	uD[1] = dY/uV;
	uD[2] = dZ/uV;		//unit form

	return uD;
}

void Enemy::autoFire()
{
	spellIntervalCount++;
	if (spellIntervalCount % spellInterval == 0)
	{
		float fireDirection[3];
		for (int i = 0; i < 3; i++)
		{
			fireDirection[i] = AIGetUnitDirection(getX(), getY(), getZ(), gPlayerPosition[0], gPlayerPosition[1], gPlayerPosition[2])[i];
		}

		spell.push_back(createProjectile(purple, fireDirection));
		if (spellIntervalCount == 100)
		{
			spellIntervalCount = 0;
		}
	}
}

void Enemy::update()
{
	updateParticles();
	updateSpells();
	updateDamage();
	autoFire();
}

void Enemy::drawFigure()
{
	
	//Body
	glMaterialfv(GL_FRONT, GL_AMBIENT, blue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, blue);
	glMaterialfv(GL_FRONT, GL_SHININESS, white);

	if (takingDamage)
	{
		glColor3fv(red);
	}
	glPushMatrix();
	glTranslatef(pos[0]+2, pos[1]+2, pos[2]+2);
	if (!takingDamage)
	{
		glColor3fv(purple);
	}
	glRotatef(-90,1,0,0);
	glRotatef(-90,0,0,1);
	glutSolidCylinder(size, size*2, 10, 10);

		//Head
		glMaterialfv(GL_FRONT, GL_AMBIENT, skin);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, skin);
		glMaterialfv(GL_FRONT, GL_SPECULAR, skin);
		glMaterialfv(GL_FRONT, GL_SHININESS, skin);
		if (!takingDamage)
		{
			glColor3fv(skin);
		}
		glPushMatrix();
		glTranslatef(0.0, 0.0, size*2);
		glutSolidSphere(size, 10, 10);

			//HatBase
			glMaterialfv(GL_FRONT, GL_AMBIENT, blue);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
			glMaterialfv(GL_FRONT, GL_SPECULAR, black);
			glMaterialfv(GL_FRONT, GL_SHININESS, white);
			if (!takingDamage)
			{
				glColor3fv(purple);
			}
			glPushMatrix();
			glTranslatef(0.0, 0.0, size * 0.8);
			glutSolidCone(size*2, size*0.8, 10, 10);

				//HatTop
				glMaterialfv(GL_FRONT, GL_AMBIENT, blue);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
				glMaterialfv(GL_FRONT, GL_SPECULAR, black);
				glMaterialfv(GL_FRONT, GL_SHININESS, white);
				if (!takingDamage)
				{
					glColor3fv(purple);
				}
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
			if (!takingDamage)
			{
				glColor3fv(black);
			}
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
			if (!takingDamage)
			{
				glColor3fv(white);
			}
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
		if (!takingDamage)
		{
			glColor3fv(purple);
		}

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
			if (!takingDamage)
			{
				glColor3fv(wood);
			}
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
		if (!takingDamage)
		{
			glColor3fv(purple);
		}
		glPushMatrix();
		glTranslatef(0.0, 0.0, -1.0);
		glutSolidCone(size*1.5, size*4, 10, 10);
		glPopMatrix();

	glPopMatrix();
}
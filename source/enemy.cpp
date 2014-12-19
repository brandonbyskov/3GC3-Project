#include "enemy.h"
#include "main.h"

#include "gllibs.h"

Enemy::Enemy(float* _o, float _size) : Character(_o, _size) {
}

Enemy::~Enemy() {
}

void Enemy::update()
{
	updateParticles();
	updateSpells();
}

void Enemy::drawFigure()
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
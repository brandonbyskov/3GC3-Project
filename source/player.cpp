#include "player.h"
#include "main.h"
#include "math.h"

#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>

Player::Player(float* _o, float _size) : Character(_o, _size)
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

Player::~Player() {
}

void Player::collidesVertically(float y)
{
	falling = false;
}

void Player::drop()
{
	falling = true;
}

void Player::setY(float _y)
{
	pos[1] = _y;
}

void Player::setMovement(int v)
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

void Player::cancelMovement(int v)
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

void Player::castSpell()
{
	/* Insert a new Particle at the back of the Particle vector list */
	spell.push_back(createProjectile(gPlayerLookDirection));
}

void Player::update()
{
	updateParticles();
	updateSpells();
	move();
}

void Player::modDirection()
{
	for (int i = 0; i < 3; i++)
	{
		dir[i] = gPlayerLookDirection[i];
	}
}

/* Increments a player's position appropriate to the direction they are moving in */
void Player::move()
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
void Player::drawFigure()
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
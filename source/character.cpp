#include <stdlib.h>
#include "character.h"
#include "main.h"
using namespace std;

Character::Character(float * _pos, float _size) {
	
	takingDamage = false;
	damageDuration = 0;
	size = _size;

	particleIntervalCount = 0;
	particleInterval = 10;

	spellIntervalCount = 0;
	spellInterval = 100;
				
	for (int i = 0; i < 3; i++)
	{
		pos[i] = _pos[i];
	}
}

Character::~Character() {
}

/* Create projectile at particular origin aimed at a direction */

vector<Projectile> Character::getSpellList()
{
	return spell;
}

float * Character::getPos()
{
	return pos;
}

/* Returns X coordinate of player */
float Character::getX()
{
	return pos[0];
}

/* Returns Y coordinate of player */
float Character::getY()
{
	return pos[1];
}

/* Returns Z coordinate of player */
float Character::getZ()
{
	return pos[2];
}

/* Returns size of Character Model */
float Character::getSize()
{
	return size;
}

/* Decrement lifepoints from hit */
void Character::loselife()
{
	takingDamage = true;
	lifePoints--;
}

/* Deletes projectile of spell that hits */
void Character::resolveSpell(int i)
{
	if (spell.size() != 0)
	{
		spell.erase(spell.begin()+i);
	}
}

/* Updates movement, spells, particle parameters...ect. */
void Character::update() {}//= 0;

/* Draw's character model, spells, particles */
void Character::draw()
{
	drawFigure();
	drawParticles();
	drawSpells();
}

Projectile Character::createProjectile(float * _colour, float * _dir)
{
	Projectile p(size, _colour, pos, _dir);
	return p;
}

/* Create a particle at particular origin coordinates */
Particle Character::createParticle(float* o)
{
	float pOrigin[3];
	
	pOrigin[0] = o[0]+1.7;
	pOrigin[1] = o[1]+3;	//5 units higher than origin
	pOrigin[2] = o[2]+1.7;

	Particle p(pOrigin);
	return p;
}

/* Update spell parameters */
void Character::updateSpells()
{
	for (size_t i = 0; i < spell.size(); i++)
	{
		/* Increment age */
		spell[i].incrementAge();

		/* Increment the particle's position and rotate */
		spell[i].move();

		/* Delete particle if it is over the max age */
		if (spell[i].getAge() > gMaxSpellAge)
		{
			spell.erase(spell.begin() + i);
		}
	}
}
			
/* Update particle parameters */
void Character::updateParticles()
{
	for (size_t i = 0; i < particle.size(); i++)
	{
		/* Increment age */
		particle[i].incrementAge();
		/* Increment the particle's position and rotate */
		particle[i].modPosition();
		particle[i].rotate();

		/* Delete particle if it is over the max age */
		if (particle[i].getAge() > gMaxParticleAge)
		{
			particle.pop_back();

		}
	}
}

/* Update Damage step parameters */
void Character::updateDamage()
{
	if (takingDamage)
	{
		damageDuration++;
		if (damageDuration >= 30)
		{
			takingDamage = false;
			damageDuration = 0;
		}
	}
}

/* Draws all visible spells */
void Character::drawSpells()
{
	for (size_t i = 0; i < spell.size(); i++)
	{
		/* Draw each spell projectile */
		spell[i].draw();
	}
}
	
/* Draws all particles */
void Character::drawParticles()
{
	particleIntervalCount++;
	if (particleIntervalCount % particleInterval == 0)
	{
		/* Insert a new Particle at the back of the Particle vector list */
		particle.push_back(createParticle(pos));
		particleIntervalCount = 1;
	}
	for (size_t i = 0; i < particle.size(); i++)
	{
		/* Draw each particle */
		particle[i].draw();
	}
}

void Character::drawFigure() {}

#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include "projectile.h"
#include "particle.h"
using namespace std;

class Character {
public:

	//methods
	Character(float * _pos, float _size);
	~Character();

	float * getPos();
	float getX();
	float getY();
	float getZ();
	float getSize();
	virtual void update(); // = 0
	void draw();

protected:
	int lifePoints;			//Life points of Character

	int spellInterval;		//# of Spells per period
	int spellIntervalCount;

	int particleInterval;	//# of Particles per period
	int particleIntervalCount;

	float size;				//Size of character model
	float pos[3];			//Position

	vector<Projectile> spell;
	vector<Particle> particle;

	//methods
	Projectile createProjectile(float * _dir);
	Particle createParticle(float* o);
	void updateSpells();
	void updateParticles();
	void drawSpells();
	void drawParticles();
	virtual void drawFigure(); // = 0

private:



};

#endif // CHARACTER_H
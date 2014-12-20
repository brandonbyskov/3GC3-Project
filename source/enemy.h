#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include "gllibs.h"

class Enemy : public Character {
public:
	Enemy(float* _o, float _size);
	~Enemy();
	bool isVisible;
	float directionTowardsPlayer[3];

	void autoFire();
	void update();

private:
	void drawFigure();
	void findDirectionTowardsPlayer();
	float * AIGetUnitDirection(float x1, float y1, float z1, float x2, float y2, float z2);
	float AIGetUnitVector(float dX, float dY, float dZ);

};

#endif // ENEMY_H
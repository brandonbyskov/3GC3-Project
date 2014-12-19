#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include "gllibs.h"

class Enemy : public Character {
public:
	Enemy(float* _o, float _size);
	~Enemy();

	void update();

private:
	void drawFigure();

};

#endif // ENEMY_H
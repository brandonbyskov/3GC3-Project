#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"

class Player : public Character{
public:
	Player(float* _o, float _size);
	~Player();

	void collidesVertically(float y);
	void drop();
	void setY(float _y);
	void setMovement(int v);
	void cancelMovement(int v);
	void castSpell();
	void update();


private:
	bool hasVerticalCollision;
	bool hasHorizontalCollision;
	bool movingForward, movingBackward, movingLeft, movingRight, falling, levitating;

	float dir[3];		//Direction of travel
	float rot[3];		//Orientation
	float velocity[3];	//velocity of movement
	float armRotFactor; //arm Rotation

	//methods
	void modDirection();
	void move();
	void drawFigure();
};

#endif // PLAYER_H
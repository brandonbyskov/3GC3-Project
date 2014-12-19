/* projectile.h
 * 
 * Global functions and variables that will be
 * used by the game.
 *
 * Most variables are kept public for global acess
 */

#ifndef PROJECTILE_H
#define PROJECTILE_H



class Projectile {
public:
	int test;

	Projectile(float _size, float *_colour, float * _pos, float * _dir);
	~Projectile();

	void incrementAge();
	int getAge();
	float getX();
	float getY();
	float getZ();
	void move();
	void draw();

private:
	int age;			//Life
	float size;			//Size
	float pos[3];		//Position
	float dir[3];		//Direction
	float vel[3];		//velocity
	float colour[3];	//Colour

};

#endif // PROJECTILE_H

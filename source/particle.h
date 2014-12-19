/* particle.h
 * 
 * Global functions and variables that will be
 * used by the game.
 *
 * Most variables are kept public for global acess
 */

#ifndef PARTICLE_H
#define PARTICLE_H



class Particle {
public:

	Particle(float* _pos);
	~Particle();

	void incrementAge();
	void setBounceState(bool q);
	void modDirection(float x, float y, float z);
	void modPosition();
	void rotate();
	int getAge();
	bool getFallingState();
	bool getBounceState();
	float * getPosition();
	float * getDirection();
	void draw();

private:
	/* Particle states */
	bool hasBounced;		
	bool isFalling;

	/* Age of particle (Incremented with each step of the animation) */
	int age;
	float rSpeed;

	/* Physics characteristics */
	float pos[3];	 //Position
	float dir[3];	 //Direction
	float rot[3];	 //Rotation
	float normal[3]; //Normal vector

	/* Random values generated for the direction, rotation and speed */
	float dRandFactor[3];
	float rRandFactor[3];

	float colour[3];		//Colour of the particle
	float oSpeed[3];		//Original particle speed
	float speed[3];			//Particle speed

 	float white[3];			//Colour white

	//methods
	float * getNormal(float* v1[3], float* v2[3]);

};

#endif // PARTICLE_H

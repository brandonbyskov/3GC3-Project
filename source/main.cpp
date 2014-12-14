/*	Terrain Simulation
*	Assignment 3 - CS 3GC3 McMaster University
*	By Eric Amshukov 1133146 and Brandon Byskov 1068517
*	November Friday 27th, 2014
*/

#define WIN32_LEAN_AND_MEAN
#include "main.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <list>
#include <vector>
//#include <GL/glew.h>
//#include <freeglut.h>

//brandon's includes:
//#  include <GL/gl.h>
//#  include <GL/glu.h>
//#  include <GL/freeglut.h>

#include "main.h"

using namespace std;

//global variables
Core* core;


int main(int argc, char** argv)
{
	core = new Core();
	cout << "test;";
	cout << core->test;
	return 0;
}

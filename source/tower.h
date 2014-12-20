#ifndef TOWER_H
#define TOWER_H

#include <stdlib.h>
#include <list>
#include <vector>

#include "block.h"



class Tower {
public:
	float origin[3];
	float d;
	float w;
	float h;

	int size;
	int layers;
	float blockSize;

	float vertices[8][3];

	Block*** * block;

	float colour[4];
	float colour2[4];

	Tower(float* o, int towerSize, int towerLayers, float _blockSize);//float _d, float _w, float _h);
	~Tower();

	void drawPolygon(int a, int b, int c, int d, float v[8][3]);
	void drawPolygonFrame(int a, int b, int c, int d, float v[8][3]);
	void draw();

private:


};

#endif // TOWER_H
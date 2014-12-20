#include "tower.h"

#include "gllibs.h"
using namespace std;

Tower::Tower(float* o, int towerSize, int towerLayers, float _blockSize)
{
	size = towerSize;
	layers = towerLayers;
	blockSize = _blockSize;

	d = size * blockSize;
	w = size * blockSize;
	h = layers * blockSize + 10; 

	for (int i = 0; i < 3; i++)
	{
		origin[i] = o[i];
	}
	origin[1] = origin[1] - h/2;

	colour[0] = 1.0;
	colour[1] = 1.0;
	colour[2] = 1.0;
	colour[3] = 1.0;
	
	colour2[0] = 1.0; 
	colour2[1] = 1.0;
	colour2[2] = 0.8;
	colour2[3] = 1.0;

	//initialize Blocks
	float b_origin[3];
	b_origin[0] = origin[0]-d/2 + blockSize/2;
	b_origin[1] = origin[1]+h/2 - blockSize/2 - 10;
	b_origin[2] = origin[2]-w/2 + blockSize/2;


	block = new Block** *[layers];
	b_origin[1] = origin[1]+h/2 - blockSize/2 - 10;

	for (int i = 0; i < layers ; i++, b_origin[1] -= blockSize) {
		
		block[i] = new Block* *[size];
		b_origin[0] = origin[0]-d/2 + blockSize/2;

		for (int j = 0; j < size ; j++, b_origin[0] +=  blockSize) {
			
			block[i][j] = new Block *[size];
			b_origin[2] = origin[2]-w/2 + blockSize/2;

			for (int k = 0; k < size ; k++, b_origin[2] += blockSize) {
				
				block[i][j][k] = new Block(b_origin, blockSize);
			}
		}
	}

}

Tower::~Tower() {
}

void Tower::drawPolygon(int a, int b, int c, int d, float v[8][3]) {
	glMaterialfv(GL_FRONT, GL_AMBIENT, colour2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, colour2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, colour2);
	glMaterialfv(GL_FRONT, GL_SHININESS, colour);
	
	glNormal3f(0.0, 1.0, 0.0);
	glPolygonOffset(1.0,  1.0);
	glBegin(GL_POLYGON);
		
		glVertex3fv(v[a]);
		glVertex3fv(v[b]);
		glVertex3fv(v[c]);
		glVertex3fv(v[d]);
	glEnd();

}

void Tower::drawPolygonFrame(int a, int b, int c, int d, float v[8][3]) {
	glMaterialfv(GL_FRONT, GL_AMBIENT, colour2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, colour2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, colour2);
	glMaterialfv(GL_FRONT, GL_SHININESS, colour);

	glNormal3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
		glVertex3fv(v[a]);
		glVertex3fv(v[b]);
		glVertex3fv(v[c]);
		glVertex3fv(v[d]);
	glEnd();
}

void Tower::draw() {

	//draw blocks
	for (int i = 0; i < layers ; i++) {
		for (int j = 0; j < size ; j++) {
			for (int k = 0; k < size ; k++) {
				
				(block[i][j][k])->draw();
			}
		}
	}

	float v[8][3] = { {origin[0]-w/2, origin[1]-h/2, origin[2]+d/2},
						{origin[0]-w/2, origin[1]+h/2, origin[2]+d/2},
						{origin[0]+w/2, origin[1]+h/2, origin[2]+d/2},
						{origin[0]+w/2, origin[1]-h/2, origin[2]+d/2}, 
						{origin[0]-w/2, origin[1]-h/2, origin[2]-d/2}, 
						{origin[0]-w/2, origin[1]+h/2, origin[2]-d/2}, 
						{origin[0]+w/2, origin[1]+h/2, origin[2]-d/2},
						{origin[0]+w/2, origin[1]-h/2, origin[2]-d/2} };

	//side
	//glEnable(GL_POLYGON_STIPPLE);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//Frames
	glColor4f(1.0,1.0,0.8,0.8);
	drawPolygonFrame(0, 3, 2, 1, v);

	//side
	drawPolygonFrame(1, 0, 4, 5, v);

	//top
	glColor4f(1.0,1.0,1.0,0.8);
	drawPolygonFrame(5, 1, 2, 6, v);

	glColor4f(1.0,1.0,0.8,0.8);
	drawPolygonFrame(2, 3, 7, 6, v);
	drawPolygonFrame(6, 5, 4, 7, v);
	drawPolygonFrame(4, 0, 3, 7, v);


	//Faces
	glColor4f(1.0,1.0,0.8,0.2);
	drawPolygon(0, 3, 2, 1, v);

	//side
	drawPolygon(1, 0, 4, 5, v);

	//top
	//glColor4f(1.0,1.0,1.0,0.2);
	//drawPolygon(5, 1, 2, 6, v);

	glColor4f(1.0,1.0,0.8,0.2);
	drawPolygon(2, 3, 7, 6, v);
	drawPolygon(6, 5, 4, 7, v);
	drawPolygon(4, 0, 3, 7, v);

	glDisable(GL_POLYGON_OFFSET_FILL);
}
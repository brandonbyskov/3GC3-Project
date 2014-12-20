#include "block.h"

#include "gllibs.h"

Block::Block(float* o, float blockSize) {
	
	size = blockSize;
	d = w = h = size;
	is_active = true;

	for (int i = 0; i < 3; i++)
	{
		origin[i] = o[i];
	}

	color[0] = 0.25;
	color[1] = 1.0;
	color[2] = 0.25;
	color[3] = 1.0;

	color2[0] = 0.25; 
	color2[1] = 1.0;
	color2[2] = 0.25;
	color2[3] = 1.0;

	v[0][0] = origin[0]-w/2;
	v[1][0] = origin[0]-w/2;
	v[2][0] = origin[0]+w/2;
	v[3][0] = origin[0]+w/2; 
	v[4][0] = origin[0]-w/2; 
	v[5][0] = origin[0]-w/2; 
	v[6][0] = origin[0]+w/2;
	v[7][0] = origin[0]+w/2;

	v[0][1] = origin[1]-h/2;
	v[1][1] = origin[1]+h/2;
	v[2][1] = origin[1]+h/2;
	v[3][1] = origin[1]-h/2; 
	v[4][1] = origin[1]-h/2; 
	v[5][1] = origin[1]+h/2; 
	v[6][1] = origin[1]+h/2;
	v[7][1] = origin[1]-h/2;

	v[0][2] = origin[2]+d/2;
	v[1][2] = origin[2]+d/2;
	v[2][2] = origin[2]+d/2;
	v[3][2] = origin[2]+d/2;
	v[4][2] = origin[2]-d/2; 
	v[5][2] = origin[2]-d/2; 
	v[6][2] = origin[2]-d/2;
	v[7][2] = origin[2]-d/2;
}

Block::~Block() {
}

void Block::drawFace(int a, int b, int c, int d, float v[8][3]) {
	glMaterialfv(GL_FRONT, GL_AMBIENT, color2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color2);
	glMaterialfv(GL_FRONT, GL_SHININESS, color);

	glNormal3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex3fv(v[a]);
		glVertex3fv(v[b]);
		glVertex3fv(v[c]);
		glVertex3fv(v[d]);
	glEnd();
}


void Block::draw() {

	glColor4f(0.25,0.8,0.25,1.0);
	drawFace(0, 3, 2, 1, v);

	//side
	drawFace(1, 0, 4, 5, v);

	//top
	drawFace(5, 1, 2, 6, v);

	drawFace(2, 3, 7, 6, v);
	drawFace(6, 5, 4, 7, v);
	//don't render bottom
	//glColor4f(0.25,.25,1.0,1.0);
	//drawFace(4, 0, 3, 7, v);

}
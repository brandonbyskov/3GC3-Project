#ifndef BLOCK_H
#define BLOCK_H

class Block {
public:
	bool is_active;

	Block(float* o, float blockSize);
	~Block();



	void drawFace(int a, int b, int c, int d, float v[8][3]);
	void draw();

private:
	float origin[3];
	float w, d, h;
	float v[8][3];

	float size;
	float color[4];
	float color2[4];

};

#endif // BLOCK_H
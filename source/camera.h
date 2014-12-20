#ifndef CAMERA_H
#define CAMERA_H



class Camera {
public:
	float* origin;
	float position[3];


	Camera(float* _o, float d, float s);
	~Camera();

	void move(int x, int y);
	void update();

private:

	float distance;
	float speed;

	float theta;
	float beta;

};

#endif // CAMERA_H
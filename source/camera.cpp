#include "camera.h"
#include "math.h"
#include <algorithm>
using namespace std;

#define PI 3.14159265


Camera::Camera(float* _o, float d, float s) {
	origin = _o;
	theta = 0;
	beta = 270;
	distance = d;
	speed = s;

	update();
}

Camera::~Camera() {
}

void Camera::move(int x, int y) {

	theta += y*speed;
	
	//bounds theta to between 0 and 85 degrees
	theta = min((int)theta, 85);
	theta = max((int)theta, 0);

	beta -= x *speed;//*180 * (distance * sin((speed)*PI/180)) / (2*PI*distance*sin((90-theta)*PI/180));

	//bounds beta to between 0 and 360 degrees
	if (beta<0)
		beta = 360 - fmod(fabs(beta),360);
	else
		beta = fmod(beta, 360);
}

void Camera::update() {
	float height = distance*cos((90-theta)*PI/180);
	float a = distance*sin((90-theta)*PI/180);

	position[1] = origin[1] + height;
	position[0] = origin[0] + a*sin(beta*PI/180);
	position[2] = origin[2] + a*cos(beta*PI/180);

}
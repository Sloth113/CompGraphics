#pragma once
#include "Camera.h"
class FlyCamera : public Camera
{
public:
	FlyCamera();
	~FlyCamera();
	virtual void update(float deltaTime);
private:
	float m_speed;
	vec3 m_up;
};


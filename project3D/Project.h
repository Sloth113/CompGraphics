#pragma once

#include "Application.h"
#include "FlyCamera.h"
#include <glm/mat4x4.hpp>

class Project : public aie::Application {
public:

	Project();
	virtual ~Project();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	FlyCamera *	m_myCamera;
};
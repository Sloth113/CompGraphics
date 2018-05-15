#include "FlyCamera.h"

#include "Input.h"


FlyCamera::FlyCamera():Camera()
{
	m_speed = 10;
	m_up = vec3(0, 1, 0);
	m_oldMousePos = glm::vec2(-1,-1);
}


FlyCamera::~FlyCamera()
{
}

void FlyCamera::update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
	vec3 newPos = vec3(m_worldTransform[3][0], m_worldTransform[3][1], m_worldTransform[3][2]);
	if (input->isKeyDown(aie::INPUT_KEY_W)) {
		//move forward
		glm::vec4 forward = glm::vec4(0, 0, -1, 0);
		forward = m_worldTransform * forward;
		newPos += vec3(forward) * m_speed * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_S)) {
		//move forward
		glm::vec4 back = glm::vec4(0, 0, 1, 0);
		back = m_worldTransform * back;
		newPos += vec3(back) * m_speed * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_A)) {
		glm::vec4 left = glm::vec4(-1, 0, 0, 0);
		left = m_worldTransform * left;
		newPos += vec3(left) * m_speed * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_D)) {
		glm::vec4 right = glm::vec4(1, 0, 0, 0);
		right = m_worldTransform * right;
		newPos += vec3(right) * m_speed * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_SPACE)) {
		newPos += vec3(0, m_speed * deltaTime, 0);
	}
	if (input->isKeyDown(aie::INPUT_KEY_LEFT_CONTROL)) {
		newPos += vec3(0, -m_speed * deltaTime, 0);
	}

	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT)) {
		glm::vec2 newMPos = glm::vec2(input->getMouseX(), input->getMouseY());
		if (m_oldMousePos != glm::vec2(-1, -1)) {
			glm::vec2 change =   newMPos- m_oldMousePos;
			m_worldTransform = glm::rotate(m_worldTransform, (-change.x * deltaTime)/180 * glm::pi<float>() * m_speed, vec3(0, 1, 0));
			m_worldTransform = glm::rotate(m_worldTransform, (change.y * deltaTime) /180 * glm::pi<float>() * m_speed, vec3(1, 0, 0));
		}
		m_oldMousePos = newMPos;

	}
	else {
		m_oldMousePos = glm::vec2(-1, -1);
	}

	setPosition(newPos); //this updates view transform and projection

	

}

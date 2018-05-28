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
	//up and down
	if (input->isKeyDown(aie::INPUT_KEY_SPACE)) {

		glm::vec4 up = glm::vec4(0, 1, 0, 0);
		up = m_worldTransform * up;
		newPos += vec3(up) * m_speed * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_LEFT_CONTROL)) {
		glm::vec4 down = glm::vec4(0, -1, 0, 0);
		down = m_worldTransform * down;
		newPos += vec3(down) * m_speed * deltaTime;
	}

	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT)) {
		glm::vec2 newMPos = glm::vec2(input->getMouseX(), input->getMouseY());
		if (m_oldMousePos != glm::vec2(-1, -1)) {
			glm::vec2 change =   newMPos- m_oldMousePos;
			float xangle = (change.y * deltaTime) / 180 * glm::pi<float>() * m_speed;
			float yangle = -(change.x * deltaTime) / 180 * glm::pi<float>() * m_speed;
			//Fine ill do it myself 
			//Rotate world y
			glm::mat4 rotYMat = {
				glm::cos(yangle),	0.f,	-glm::sin(yangle),	0.f,
				0.f,				1.f,	0.f,				0.f,
				glm::sin(yangle),	0.f,	glm::cos(yangle),	0.f,
				0.f,				0.f,	0.f,				1.f
			};
			m_worldTransform = rotYMat * m_worldTransform;

			m_worldTransform = glm::rotate(m_worldTransform, xangle, vec3(1, 0, 0));
			
		}
		m_oldMousePos = newMPos;

	}
	else {
		m_oldMousePos = glm::vec2(-1, -1);
	}

	setPosition(newPos); //this updates view transform and projection

	

}

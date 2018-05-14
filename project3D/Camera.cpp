#include "Camera.h"

Camera::Camera()
{
	m_worldTransform = mat4(0);
	m_viewTransform = mat4(0);
	m_projectionTransform = mat4(0);
	m_projectionViewTransform = mat4(0);
}

Camera::~Camera()
{
}

void Camera::setPerspective(float fieldOfView, float aspectRatio, float near, float far)
{
	m_projectionTransform = mat4(
		{ {	1 / (aspectRatio * tanf(fieldOfView / 2)),	0,	0,	0},
			{0, 	1 / (tanf(fieldOfView / 2)), 0,	0 },
			{0,	0,	-(far + near) / (far - near), -(2 * far * near) / (far - near) },
			{0,	0,	-1,	0} });
}

void Camera::setLookAt(vec3 from, vec3 to, vec3 up)
{
	m_worldTransform = glm::lookAt(from, to, up);
	m_viewTransform = glm::inverse(m_worldTransform);
	m_projectionViewTransform = m_viewTransform * m_projectionTransform;
}

void Camera::setPosition(vec3 position)
{
}

mat4 Camera::getWorldTransform()
{
	return m_worldTransform;
}

mat4 Camera::getProjection()
{
	return m_projectionTransform;
}

mat4 Camera::getProjectionView()
{
	return m_projectionViewTransform;
}

void Camera::updateProjectionViewTransform()
{
}
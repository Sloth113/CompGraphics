#pragma once

#include "Shader.h"
#include "Application.h"
#include "FlyCamera.h"
#include "Mesh.h"
#include "Texture.h"
#include "OBJMesh.h"
#include "Object.h"
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

	Object ** m_scene;

	aie::ShaderProgram m_quadShader;
	Mesh m_quadMesh;
	glm::mat4 m_quadTransform;

	aie::ShaderProgram m_objShader;
	aie::OBJMesh m_objMesh;
	glm::mat4 m_objTransform;
};
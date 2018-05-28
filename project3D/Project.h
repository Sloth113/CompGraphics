#pragma once

#include "Shader.h"
#include "Application.h"
//#include "FlyCamera.h"
#include "Mesh.h"
#include "Texture.h"
#include "OBJMesh.h"
#include "Object.h"
#include <glm/mat4x4.hpp>
#include <vector>
#include <../dependencies/imgui/imgui.h>

class Project : public aie::Application {
public:

	Project();
	virtual ~Project();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();
	bool LoadShader(aie::ShaderProgram * shader,  aie::eShaderStage stage, char* path);

protected:

	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	FlyCamera *	m_myCamera;

	std::vector<Object *> m_scene;
	std::vector<aie::OBJMesh *> m_meshs;
	std::vector<Mesh *> m_shapes;
	std::vector<aie::Texture *> m_textures;
	std::vector<aie::ShaderProgram *> m_shaders;

	SceneData m_data;

	bool m_test;
	float m_float;
	//Light m_light;
};
#pragma once
#include "Shader.h"
#include "OBJMesh.h"
class Object
{
public:
	Object(glm::mat4 transform);
	~Object();
	bool LoadShader(aie::eShaderStage stage, char* path);
	bool LoadMesh(char* path);

	void Draw(glm::mat4 cameraProjectionView);

private:
	aie::ShaderProgram m_shader;
	aie::OBJMesh m_mesh;
	glm::mat4 m_transform;
};


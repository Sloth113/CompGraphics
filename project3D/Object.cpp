#include "Object.h"



Object::Object(glm::mat4 transform)
{
	m_transform = transform;
}


Object::~Object()
{
}

bool Object::LoadShader(aie::eShaderStage stage, char * path)
{
	m_shader.loadShader(stage, path);
	if (m_shader.link() == false) {
		printf("Shader Error: %s\n", m_shader.getLastError());
		return false;
	}
	return true;
		
}


bool Object::LoadMesh(char * path)
{
	if (m_mesh.load(path) == false) {
		printf("Mesh load Error!\n");
		return false;
	}
	return true;
}

void Object::Draw(glm::mat4 cameraProjectionView)
{
	m_shader.bind();
	glm::mat4 pvm = cameraProjectionView * m_transform;
	m_shader.bindUniform("ProjectionViewModel", pvm);
	m_mesh.draw();
}

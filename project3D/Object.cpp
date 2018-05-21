#include "Object.h"



Object::Object(glm::mat4 transform)
{
	m_transform = transform;
	m_shape = nullptr;
	m_mesh = nullptr;
	m_texture = nullptr;
}


Object::~Object()
{
}

bool Object::SetShader(aie::ShaderProgram * shader)
{
	m_shader = shader;
	return true;
}


bool Object::SetMesh(aie::OBJMesh * mesh)
{
	m_mesh = mesh;
	return true;
}

bool Object::SetMesh(Mesh * mesh)
{
	m_shape = mesh;
	return true;
}

bool Object::SetTexture(aie::Texture * texture)
{
	m_texture = texture;
	return true;
}

void Object::Draw(glm::mat4 cameraProjectionView)
{

	m_shader->bind();
	glm::mat4 pvm = cameraProjectionView * m_transform;
	m_shader->bindUniform("ProjectionViewModel", pvm);

	if (m_shader->getUniform("diffuseTexture") != -1 && m_texture != nullptr) {

		m_shader->bindUniform("diffuseTexture", 0);
		m_texture->bind(0);
	}

	if (m_shader->getUniform("lightDirection") != -1) {
		printf("PHONG?");
	}
	
	if (m_texture != nullptr) {
	}
	

	if (m_shape != nullptr) {
		m_shape->draw();
	}
	else if (m_mesh != nullptr) {
		m_mesh->draw();
	}
}

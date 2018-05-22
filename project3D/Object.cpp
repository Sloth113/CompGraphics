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
	if (m_shader->getUniform("NormalMatrix") != -1) {
		m_shader->bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_transform)));
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

void Object::Draw(SceneData scene)
{
	m_shader->bind();
	glm::mat4 pvm = scene.camera->getProjectionView() * m_transform;
	m_shader->bindUniform("ProjectionViewModel", pvm);

	if (m_shader->getUniform("diffuseTexture") != -1 && m_texture != nullptr) {

		m_shader->bindUniform("diffuseTexture", 0);
		m_texture->bind(0);
	}
	else if (m_shader->getUniform("diffuseTexture") != -1 ){
		//m_shader->bindUniform("diffuseTexture", -1);
	}
	if (m_shader->getUniform("specularTexture") != -1 && m_texture != nullptr) {

		m_shader->bindUniform("specularTexture", 0);
		m_texture->bind(0);
		
	}
	else if(m_shader->getUniform("specularTexture") != -1 ){
		//m_shader->bindUniform("specularTexture", -1);
	}

	if (m_shader->getUniform("NormalMatrix") != -1) {
		m_shader->bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_transform)));
	}
	if (m_shader->getUniform("LightDirection") != -1) {
		m_shader->bindUniform("LightDirection", scene.light.direction);
	}
	if (m_shader->getUniform("Ia") != -1){
		m_shader->bindUniform("Ia", scene.ambLight);
	}
	if (m_shader->getUniform("Id") != -1) {
		m_shader->bindUniform("Id", scene.light.diffuse);
	}
	if (m_shader->getUniform("Is") != -1) {
		m_shader->bindUniform("Is", scene.light.specular);
	}

	if (m_shader->getUniform("Ka") != -1 && m_texture == nullptr) {
		m_shader->bindUniform("Ka", vec3(1,1,1));
	}
	if (m_shader->getUniform("Kd") != -1 && m_texture == nullptr) {
		m_shader->bindUniform("Kd", scene.light.diffuse);
	}
	if (m_shader->getUniform("Ks") != -1 && m_texture == nullptr) {
		m_shader->bindUniform("Ks", scene.light.specular);
	}
	if (m_shader->getUniform("specularPower") != -1) {
		//m_shader->bindUniform("specularPower", 0.0f); //does nothing??
	}
	
	if (m_shader->getUniform("cameraPosition") != -1) {
		m_shader->bindUniform("cameraPosition", scene.camera->getPosition());
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

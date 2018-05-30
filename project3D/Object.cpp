#include "Object.h"



Object::Object(glm::mat4 transform, float roughness, float reflectCoef)
{
	m_transform = transform;
	m_shape = nullptr;
	m_mesh = nullptr;
	m_texture = nullptr;
	m_ambLight = vec3(1.0f, 1.0f, 1.0f);
	m_specPower = 0.5f;
	m_specular = vec3(0.5f, 0.5f, 0.5f);
	m_diffuse = vec3(1, 1, 1);
	m_roughness = roughness;
	m_reflectionCoef = reflectCoef;
		
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

float * Object::GetRoughness()
{
	return &m_roughness;
}

float * Object::GetReflection()
{
	return &m_reflectionCoef;
}

bool Object::SetTexture(aie::Texture * texture)
{
	m_texture = texture;
	return true;
}

void Object::Draw(glm::mat4 cameraProjectionView)
{
	//OLD
	
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

void Object::Draw(SceneData * scene)
{
	m_shader->bind();
	glm::mat4 pvm = scene->camera->getProjectionView() * m_transform;
	m_shader->bindUniform("ProjectionViewModel", pvm);

	if (m_shader->getUniform("diffuseTexture") != -1 && m_texture != nullptr) {

		m_shader->bindUniform("diffuseTexture", 0);
		m_texture->bind(0);
	}
	else if (m_shader->getUniform("diffuseTexture") != -1){
		m_shader->bindUniform("diffuseTexture", 0);
	}

	if (m_shader->getUniform("specularTexture") != -1 && m_texture != nullptr) {

		m_shader->bindUniform("specularTexture", 0);
		m_texture->bind(0);
		
	}
	else if(m_shader->getUniform("specularTexture") != -1 ){
		m_shader->bindUniform("specularTexture", 0);
	}

	if (m_shader->getUniform("NormalMatrix") != -1) {
		m_shader->bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_transform)));
	}

	if (m_shader->getUniform("Ia") != -1) {
		m_shader->bindUniform("Ia", scene->ambLight);
	}
	//Multilight
	if (m_shader->getUniform("LightDirections") != -1) {
		//m_shader->bindUniform("LightDirections",  scene->direction[0]);
		glUniform3fv(m_shader->getUniform("LightDirections"), 4, &scene->direction[0].x);
	}
	if (m_shader->getUniform("Ids") != -1) {
		glUniform3fv(m_shader->getUniform("Ids"), 4, &scene->diffuse[0].x);
	}
	if (m_shader->getUniform("Iss") != -1) {
		glUniform3fv(m_shader->getUniform("Iss"), 4, &scene->specular[0].x);
	}

	//Single light
	if (m_shader->getUniform("LightDirection") != -1) {
		m_shader->bindUniform("LightDirection", scene->direction[0]);
	}
	if (m_shader->getUniform("Id") != -1) {
		m_shader->bindUniform("Id", scene->diffuse[0]);
	}
	if (m_shader->getUniform("Is") != -1) {
		m_shader->bindUniform("Is", scene->specular[0]);
	}

	if (m_shader->getUniform("Ka") != -1) {
		m_shader->bindUniform("Ka", m_ambLight);
	}
	if (m_shader->getUniform("Kd") != -1 ) {
		m_shader->bindUniform("Kd", m_diffuse);
	}
	if (m_shader->getUniform("Ks") != -1) {
		m_shader->bindUniform("Ks", m_specular);
	}
	if (m_shader->getUniform("specularPower") != -1) {
		m_shader->bindUniform("specularPower", m_specPower); 
	}
	
	if (m_shader->getUniform("cameraPosition") != -1) {
		m_shader->bindUniform("cameraPosition", scene->camera->getPosition());
	}

	if (m_shader->getUniform("roughness") != -1) {
		m_shader->bindUniform("roughness", m_roughness);
	}
	if (m_shader->getUniform("reflectionCoefficient") != -1) {
		m_shader->bindUniform("reflectionCoefficient", m_reflectionCoef);
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

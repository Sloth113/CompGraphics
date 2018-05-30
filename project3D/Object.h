#pragma once
#include "Shader.h"
#include "OBJMesh.h"
#include "Mesh.h"
#include "FlyCamera.h"

class SceneData {
public:
	glm::vec3 * direction;
	glm::vec3 * diffuse;
	glm::vec3 * specular;

	glm::vec3 ambLight;
	FlyCamera * camera;

};

class Object
{
public:
	Object(glm::mat4 transform, float roughness = 0, float reflectCoef = 1);
	~Object();
	bool SetShader(aie::ShaderProgram * shader);
	bool SetMesh(aie::OBJMesh * mesh);
	bool SetMesh(Mesh * mesh);
	float* GetRoughness();
	float* GetReflection();
	bool SetTexture(aie::Texture * texture);
	void Draw(glm::mat4 cameraProjectionView);
	void Draw(SceneData * scene);

private:
	
	aie::ShaderProgram * m_shader;
	aie::OBJMesh * m_mesh;
	Mesh * m_shape;
	glm::mat4 m_transform;
	aie::Texture * m_texture;

	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	float m_specPower;
	glm::vec3 m_ambLight;
	float m_roughness;
	float m_reflectionCoef;

};


#pragma once
#include "Shader.h"
#include "OBJMesh.h"
#include "Mesh.h"
#include "FlyCamera.h"

struct Light {
	glm::vec3 direction;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct SceneData {
	Light light;
	glm::vec3 ambLight;
	FlyCamera * camera;
};

class Object
{
public:
	Object(glm::mat4 transform);
	~Object();
	bool SetShader(aie::ShaderProgram * shader);
	bool SetMesh(aie::OBJMesh * mesh);
	bool SetMesh(Mesh * mesh);
	bool SetTexture(aie::Texture * texture);
	void Draw(glm::mat4 cameraProjectionView);
	void Draw(SceneData scene);

private:
	
	aie::ShaderProgram * m_shader;
	aie::OBJMesh * m_mesh;
	Mesh * m_shape;
	glm::mat4 m_transform;
	aie::Texture * m_texture;
};


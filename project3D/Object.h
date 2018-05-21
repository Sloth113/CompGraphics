#pragma once
#include "Shader.h"
#include "OBJMesh.h"
#include "Mesh.h"
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

private:
	
	aie::ShaderProgram * m_shader;
	aie::OBJMesh * m_mesh;
	Mesh * m_shape;
	glm::mat4 m_transform;
	aie::Texture * m_texture;
};


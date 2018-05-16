#include "Project.h"
#include "Gizmos.h"
#include "Input.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

Project::Project() {

}

Project::~Project() {

}

bool Project::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);


	m_myCamera = new FlyCamera();
	m_myCamera->setPerspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f);
	m_myCamera->setLookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	/*printf("Mat\n %f,\t%f,\t%f,\t%f\n%f,\t%f,\t%f,\t%f\n%f,\t%f,\t%f,\t%f\n%f,\t%f,\t%f,\t%f\n",
		m_myCamera->getWorldTransform()[0][0], m_myCamera->getWorldTransform()[0][1], m_myCamera->getWorldTransform()[0][2], m_myCamera->getWorldTransform()[0][3], 
		m_myCamera->getWorldTransform()[1][0], m_myCamera->getWorldTransform()[1][1], m_myCamera->getWorldTransform()[1][2], m_myCamera->getWorldTransform()[1][3], 
		m_myCamera->getWorldTransform()[2][0], m_myCamera->getWorldTransform()[2][1], m_myCamera->getWorldTransform()[2][2], m_myCamera->getWorldTransform()[2][3], 
		m_myCamera->getWorldTransform()[3][0], m_myCamera->getWorldTransform()[3][1], m_myCamera->getWorldTransform()[3][2], m_myCamera->getWorldTransform()[3][3] );*/
	
	/*	
	m_quadShader.loadShader(aie::eShaderStage::VERTEX,	"./shaders/simple.vert");
	m_quadShader.loadShader(aie::eShaderStage::FRAGMENT,"./shaders/simple.frag");
	if (m_quadShader.link() == false) {
		printf("Shader Error: %s\n", m_quadShader.getLastError());
		return false;
	}
	
	
	//m_quadMesh.initialiseQuad();
	/*
	// define 6 vertices for 2 triangles
	Mesh::Vertex vertices[6];
	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };
	vertices[3].position = { -0.5f, 0, -0.5f, 1 };
	vertices[4].position = { 0.5f, 0, 0.5f, 1 };
	vertices[5].position = { 0.5f, 0, -0.5f, 1 };
	m_quadMesh.initialise(6, vertices);
	*/
	
	/*/
	// define 4 vertices for 2 triangles
	Mesh::Vertex vertices[4];
	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };
	vertices[3].position = { 0.5f, 0, -0.5f, 1 };
	unsigned int indices[6] = { 0, 1, 2, 2, 1, 3 };
	m_quadMesh.initialise(4, vertices, 6, indices);


	m_quadTransform = {
		10,0,0,0,
		0,10,0,0,
		0,0,10,0,
		0,0,0,1 
	};
	*/

	/*
	m_objShader.loadShader(aie::eShaderStage::VERTEX,"./shaders/simple.vert");
	m_objShader.loadShader(aie::eShaderStage::FRAGMENT,"./shaders/simple.frag");
	
	if (m_objShader.link() == false) {
		printf("Shader Error: %s\n", m_objShader.getLastError());
		return false;
	}
	if (m_objMesh.load("./models/Bunny.obj") == false) {
		printf("Bunny Mesh Error!\n");
		return false;
	}

	m_objTransform = {
		0.5f,0,0,0,
		0,0.5f,0,0,
		0,0,0.5f,0,
		0,0,0,1
	};
	*/

	m_scene = new Object*[3];


	mat4 transform = {
		0.5f,0,0,0,
		0,0.5f,0,0,
		0,0,0.5f,0,
		0,0,0,1
	};

	m_scene[0] = new Object(transform);
	transform = glm::translate(transform, glm::vec3(3, 0, 0));
	m_scene[1] = new Object(transform);
	transform = glm::translate(transform, glm::vec3(3, 0, 0));
	m_scene[2] = new Object(transform);

	//m_scene[1]->SetMesh(m_scene[0]->GetMesh());
	//m_scene[2]->SetMesh(m_scene[0]->GetMesh());


	for (int i = 0; i < 3; i++) {
		if (m_scene[i]->LoadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert") == false) {
			return false;
		}
		if (m_scene[i]->LoadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag") == false) {
			return false;
		}
		printf("Loading Mesh\n");
		if (m_scene[i]->LoadMesh("./models/Bunny.obj") == false) {
			return false;
		}
	}
	


	return true;
}

void Project::shutdown() {
	delete m_myCamera;
	delete[] m_scene;
	Gizmos::destroy();
}

void Project::update(float deltaTime) {

	// query time since application started
	float time = getTime();

	// rotate camera
	m_viewMatrix = glm::lookAt(vec3(glm::sin(time) * 10, 10, glm::cos(time) * 10),
							   vec3(0), vec3(0, 1, 0));

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
						vec3(-10 + i, 0, -10),
						i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
						vec3(-10, 0, -10 + i),
						i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));

	// demonstrate a few shapes
	Gizmos::addAABBFilled(vec3(0), vec3(1), vec4(0, 0.5f, 1, 0.25f));
	Gizmos::addSphere(vec3(5, 0, 5), 1, 8, 8, vec4(1, 0, 0, 0.5f));
	Gizmos::addRing(vec3(5, 0, -5), 1, 1.5f, 8, vec4(0, 1, 0, 1));
	Gizmos::addDisk(vec3(-5, 0, 5), 1, 16, vec4(1, 1, 0, 1));
	Gizmos::addArc(vec3(-5, 0, -5), 0, 2, 1, 8, vec4(1, 0, 1, 1));

	mat4 t = glm::rotate(mat4(1), time, glm::normalize(vec3(1, 1, 1)));
	t[3] = vec4(-2, 0, 0, 1);
	Gizmos::addCylinderFilled(vec3(0), 0.5f, 1, 5, vec4(0, 1, 1, 1), &t);

	// demonstrate 2D gizmos
	Gizmos::add2DAABB(glm::vec2(getWindowWidth() / 2, 100),
					  glm::vec2(getWindowWidth() / 2 * (fmod(getTime(), 3.f) / 3), 20),
					  vec4(0, 1, 1, 1));


	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();
	
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	m_myCamera->update(deltaTime);
}

void Project::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective in case window resized
	//m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f);
	m_myCamera->setPerspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f);

	/*
	// bind shader
	m_quadShader.bind();
	auto pvm = m_myCamera->getProjectionView() * m_quadTransform;//m_projectionMatrix * m_viewMatrix * m_quadTransform;
	m_quadShader.bindUniform("ProjectionViewModel", pvm);
	// draw quad
	m_quadMesh.draw();
	*/
	/*
	// bind shader
	m_objShader.bind();
	// bind transform
	auto objPvm = m_myCamera->getProjectionView() * m_objTransform;
	m_objShader.bindUniform("ProjectionViewModel", objPvm);

	m_objMesh.draw();
	*/
	for(int i = 0; i < 3; i++)
		m_scene[i]->Draw(m_myCamera->getProjectionView());

	Gizmos::draw(m_myCamera->getProjectionView());
	// draw 3D gizmos
	//Gizmos::draw(m_projectionMatrix * m_viewMatrix);

	// draw 2D gizmos using an orthogonal projection matrix (or screen dimensions)
	Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());
}
#include <glm/ext.hpp>
using glm::mat4;
using glm::vec3;

class Camera {
	protected:
		mat4 m_worldTransform;
		mat4 m_viewTransform;
		mat4 m_projectionTransform;
		mat4 m_projectionViewTransform;
		
		void updateProjectionViewTransform();
	public:
		Camera();
		~Camera();
		virtual void update(float deltaTime) = 0;
		void setPerspective(float fieldOfView, float aspectRatio, float near, float far);
		void setLookAt(vec3 from, vec3 to, vec3 up);
		void setPosition(vec3 position);
		vec3 getPosition();
		mat4 getWorldTransform();
		mat4 getProjection();
		mat4 getProjectionView();
};
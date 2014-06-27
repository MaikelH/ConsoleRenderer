#pragma once
#include <glm\glm.hpp>

class Camera
{
public:
	Camera(void);
	~Camera(void);
	void SetTarget(glm::vec3 target);
	glm::vec3 GetTarget();

	void SetPosition(glm::vec3 position);
	glm::vec3 GetPosition(glm::vec3 position);

	void Move(glm::vec3 vector);

	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewMatrix();

protected:
	glm::vec3 _target;
	glm::vec3 _position;

	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;
};


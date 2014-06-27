#include "StdAfx.h"
#include "Camera.h"
#include <glm\gtc\matrix_transform.hpp>

Camera::Camera(void)
{
	_projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
	_viewMatrix = glm::lookAt(
			glm::vec3(0, 0, -5),
			glm::vec3(-10, -10, 0),
			glm::vec3(0, 1, 0)
		);
}


Camera::~Camera(void)
{
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return _projectionMatrix;
}

glm::mat4 Camera::GetViewMatrix()
{
	return _viewMatrix;
}

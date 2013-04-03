#include "StdAfx.h"
#include "Camera.h"
#include <glm\gtc\matrix_transform.hpp>

Camera::Camera(void)
{
	_projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
}


Camera::~Camera(void)
{
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return _projectionMatrix;
}

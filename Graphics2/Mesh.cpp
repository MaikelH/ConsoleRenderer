#include "StdAfx.h"
#include "Mesh.h"
#include <glm\gtc\matrix_transform.hpp>


Mesh::Mesh(void) : _worldCoordinate(glm::vec3(0,0,0))
{
}


Mesh::~Mesh(void)
{
}

void Mesh::setWorldCoordinate(glm::vec3 vector)
{
	_worldCoordinate = vector;
	_transLateMatrix = glm::translate(glm::mat4(1.0f), vector);
}

glm::vec3 Mesh::getWorldCoordinate()
{
	return _worldCoordinate;
}

std::vector<glm::vec4> Mesh::GetProjectedVertices()
{
	std::vector<glm::vec4> returnVector;
	
		for(std::vector<glm::vec4>::size_type i = 0; i != _vertexList.size(); i++)
	{
		returnVector.push_back(_transLateMatrix * _vertexList[i]);	
	}

	return returnVector;
}

std::vector<glm::vec4> Mesh::GetProjectedVertices(Camera* camera) 
{
	std::vector<glm::vec4> returnVector;
	glm::mat4 _projectionMatrix = camera->GetProjectionMatrix();
	glm::mat4 _viewMatrix = camera->GetViewMatrix();
	
	for(std::vector<glm::vec4>::size_type i = 0; i != _vertexList.size(); i++)
	{
		returnVector.push_back((_projectionMatrix * _viewMatrix * _transLateMatrix) * _vertexList[i]);	
	}

	return returnVector;
}


std::vector<boost::tuple<int, int> > Mesh::GetIndexList()
{
	return _indexList;
}

void Mesh::Rotate(float angle, const glm::vec3& axis)
{
	_transLateMatrix = glm::rotate(_transLateMatrix, angle, axis);
}
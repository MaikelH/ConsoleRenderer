#pragma once
#include <vector>
#include <glm\glm.hpp>
#include <boost\tuple\tuple.hpp>
#include <vector>
#include "Camera.h"

class Mesh
{
public:
	typedef std::vector<boost::tuple<int, int> > IndexList;

	Mesh(void);
	~Mesh(void);

	glm::vec3 getWorldCoordinate();
	void setWorldCoordinate(glm::vec3 vector);
	std::vector<glm::vec4> GetProjectedVertices();
	std::vector<glm::vec4> GetProjectedVertices(Camera* camera);
	IndexList GetIndexList();
	void Rotate(float angle, const glm::vec3& axis);

protected:
	std::vector<glm::vec4> _vertexList;
	IndexList _indexList;

	glm::vec3 _worldCoordinate;
	glm::mat4 _transLateMatrix;
};


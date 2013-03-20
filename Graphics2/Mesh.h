#pragma once
#include <vector>
#include <glm\glm.hpp>
#include <boost\tuple\tuple.hpp>
#include <vector>

class Mesh
{
public:
	Mesh(void);
	~Mesh(void);

	glm::vec3 getWorldCoordinate();
	void setWorldCoordinate(glm::vec3 vector);
	std::vector<glm::vec4> GetProjectedVertices();

protected:
	std::vector<glm::vec4> _vertexList;
	std::vector<boost::tuple<int, int> > _indexList;

	glm::vec3 _worldCoordinate;
	glm::mat4 _transLateMatrix;
};


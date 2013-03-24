#include "StdAfx.h"
#include "Cube.h"
#include <glm\glm.hpp>

Cube::Cube(void)
{
	// Added vertex to list
	this->_vertexList.push_back( glm::vec4(0,0,0,1));
	this->_vertexList.push_back( glm::vec4(5,0,0,1));
	this->_vertexList.push_back( glm::vec4(5,5,0,1));
	this->_vertexList.push_back( glm::vec4(0,5,0,1));

	// Set index to draw lines
	this->_indexList.push_back(boost::make_tuple(0, 1));
	this->_indexList.push_back(boost::make_tuple(1, 2));
	this->_indexList.push_back(boost::make_tuple(2, 3));
	this->_indexList.push_back(boost::make_tuple(3, 0));
}


Cube::~Cube(void)
{
}

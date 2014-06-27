#include "StdAfx.h"
#include "Cube.h"
#include <glm\glm.hpp>

Cube::Cube(void)
{
	// Added vertex to list
	// Front
	this->_vertexList.push_back( glm::vec4(0,0,0,1));
	this->_vertexList.push_back( glm::vec4(4,0,0,1));
	this->_vertexList.push_back( glm::vec4(4,4,0,1));
	this->_vertexList.push_back( glm::vec4(0,4,0,1));
	
	// Back
	this->_vertexList.push_back( glm::vec4(0,0,4,1));
	this->_vertexList.push_back( glm::vec4(4,0,4,1));
	this->_vertexList.push_back( glm::vec4(4,4,4,1));
	this->_vertexList.push_back( glm::vec4(0,4,4,1));

	// Set index to draw lines
	this->_indexList.push_back(boost::make_tuple(0, 1));
	this->_indexList.push_back(boost::make_tuple(1, 2));
	this->_indexList.push_back(boost::make_tuple(2, 3));
	this->_indexList.push_back(boost::make_tuple(3, 0));

	this->_indexList.push_back(boost::make_tuple(4, 5));
	this->_indexList.push_back(boost::make_tuple(5, 6));
	this->_indexList.push_back(boost::make_tuple(6, 7));
	this->_indexList.push_back(boost::make_tuple(7, 4));

	this->_indexList.push_back(boost::make_tuple(0, 4));
	this->_indexList.push_back(boost::make_tuple(1, 5));
	this->_indexList.push_back(boost::make_tuple(2, 6));
	this->_indexList.push_back(boost::make_tuple(3, 7));
}


Cube::~Cube(void)
{
}

#include "StdAfx.h"
#include "RenderSystem.h"
#include <time.h>
#include <boost\tuple\tuple.hpp>

RenderSystem::RenderSystem(void) : _stop(false),
	_bColor(BACK_BLUE)
{
	// Get the size of the standard console window
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	this->columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	this->rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	// Create buffer the size of the window
	this->buffer = new CHAR_INFO[rows * columns];

	assert(this->buffer != NULL);
}

RenderSystem::~RenderSystem(void)
{
	free(this->buffer);
}

void RenderSystem::SetDisplayCallback(boost::function<void ()> function)
{
	_displayCallback = function;
}

void RenderSystem::StartRender()
{
	_hOUT = GetStdHandle(STD_OUTPUT_HANDLE);
	_renderFunction();
}

void RenderSystem::_renderFunction()
{
	while(!_stop)
	{
		this->buffer = new CHAR_INFO[rows * columns];
		
		// Fill with stars
		for (int y = 0; y < rows ; ++y) {
			for (int x = 0; x < columns; ++x) {
				buffer[x+columns*y].Char.AsciiChar = ' ';
				buffer[x+columns*y].Attributes = this->_bColor | WHITE;
			   }	
		}

		std::vector<glm::vec4> vertices = _processMeshes();

		for(std::vector<glm::vec4>::size_type i = 0; i != vertices.size(); i++)
		{
			buffer[(int)(vertices[i].y * columns + vertices[i].x)].Char.AsciiChar = '*';
		}
		
		if(!_displayCallback.empty())
		{
			_displayCallback();
		}

		COORD start = {0,0};
		SMALL_RECT SBRegion = { 0, 0, columns, rows };
		COORD size = { 80, 25 };
		COORD startC = {0, 0};
		WriteConsoleOutputA(_hOUT, buffer, size, startC, &SBRegion);

		// Clear the buffer
		free(this->buffer);
	}
}

void RenderSystem::StopRender()
{
	_stop = false;
}

void RenderSystem::SetRenderList(std::vector<Mesh*> const &meshList)
{
	_renderList = meshList;
}

std::vector<glm::vec4> RenderSystem::_processMeshes()
{
	std::vector<glm::vec4> returnVector;
	
	for(std::vector<Mesh*>::size_type i = 0; i != _renderList.size(); i++)
	{
		std::vector<glm::vec4> temp = _renderList[i]->GetProjectedVertices();
		Mesh::IndexList indexes = _renderList[i]->GetIndexList();

		// Process all the different line segments
		for(Mesh::IndexList::size_type i = 0; i != indexes.size(); i++)
		{
			std::vector<glm::vec4> pixels = _connectVertex(temp[boost::get<0>(indexes[i])], temp[boost::get<1>(indexes[i])]);
			returnVector.insert(returnVector.end(), pixels.begin(), pixels.end());
		}
	}

	return returnVector;
}

std::vector<glm::vec4> RenderSystem::_connectVertex(glm::vec4 point1, glm::vec4 point2)
{
	// Implementation of simple bresenham algorithm
	std::vector<glm::vec4> coords;
	if(point2.x < point1.x)
	{
		glm::vec4 tempPoint = point1;
		point1 = point2;
		point2 = tempPoint;
	}
	int deltax = (int) (point2.x - point1.x);
	int deltay = (int) (point2.y - point1.y);

	float error = 0;
	float deltaError = 0;
	if(!deltax == 0) 
	{ 	
		deltaError = (float) abs(deltay/deltax);
	}

	int y = (int) point1.y;

	for(int x = (int)point1.x; x <= point2.x; x++)
	{
		coords.push_back(glm::vec4(x, y, 0, 1));

		error += deltaError;
		if(error >= 0.5) 
		{
			y += 1;
			error -= 1.0;
		}
	}

	return coords;
}
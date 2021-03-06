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
		// Create new empty buffer;
		this->buffer = new CHAR_INFO[rows * columns];
		
		// Create Background
		for (int y = 0; y < rows ; ++y) {
			for (int x = 0; x < columns; ++x) {
				buffer[x+columns*y].Char.AsciiChar = ' ';
				buffer[x+columns*y].Attributes = this->_bColor | WHITE;
			   }	
		}

		// Process everything that should be drawn at the screen
		std::vector<glm::vec4> vertices = _processMeshes();

		// Create all the lines on the display
		for(std::vector<glm::vec4>::size_type i = 0; i != vertices.size(); i++)
		{
			buffer[(int)(vertices[i].y * columns + vertices[i].x)].Char.AsciiChar = '*';
		}
		
		// Write to console buffer
		COORD start = {0,0};
		SMALL_RECT SBRegion = { 0, 0, columns, rows };
		COORD size = { 80, 25 };
		COORD startC = {0, 0};
		WriteConsoleOutputA(_hOUT, buffer, size, startC, &SBRegion);
		
		if(!_displayCallback.empty())
		{
			_displayCallback();
		}

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
	
	// Loop through all the meshes in the renderlist
	for(std::vector<Mesh*>::size_type i = 0; i != _renderList.size(); i++)
	{
		// Retrieve vertexes and index numbers for every mesh
		std::vector<glm::vec4> temp = _renderList[i]->GetProjectedVertices(this->_camera );
		Mesh::IndexList indexes = _renderList[i]->GetIndexList();

		// Process all the different line segments and connect them together
		for(Mesh::IndexList::size_type i = 0; i != indexes.size(); i++)
		{
			std::vector<glm::vec4> pixels = _connectVertex(temp[boost::get<0>(indexes[i])], temp[boost::get<1>(indexes[i])]);
			returnVector.insert(returnVector.end(), pixels.begin(), pixels.end());
		}
	}

	return returnVector;
}

/**
  *
  */
std::vector<glm::vec4> RenderSystem::_connectVertex(glm::vec4 point1, glm::vec4 point2)
{
	// Implementation of simple bresenham algorithm
	std::vector<glm::vec4> coords;
	
	// Swap points so that we can draw from the left through right
	if(point2.x < point1.x)
	{
		glm::vec4 tempPoint = point1;	
		point1 = point2;
		point2 = tempPoint;
	}
	if(point2.y < point1.y)
	{
		glm::vec4 tempPoint = point1;
		point1 = point2;
		point2 = tempPoint;
	}

	int deltax = (int) (point2.x - point1.x);
	int deltay = (int) (point2.y - point1.y);

	// If deltax = 0 -> vertical line
	if(deltax == 0)
	{
		for(int y = point1.y; y <= point2.y; y++)
		{
			coords.push_back(glm::vec4(point1.x,y,0,1));
		}
	}
	else
	{
		float error = 0;
		float deltaError = 0;
		deltaError = (float) abs((float)deltay/deltax);

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
	}

	return coords;
}

void RenderSystem::SetCamera(Camera *camera) 
{
	this->_camera = camera;
}
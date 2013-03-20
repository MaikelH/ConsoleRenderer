// Graphics2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RenderSystem.h"
#include "Mesh.h"
#include "Cube.h"
#include <glm\gtc\matrix_transform.hpp>
#include <vector>

void displayCallback();
void InitResources();

RenderSystem* renderer;
std::vector<Mesh*> _meshList;
bool startup = false;


int _tmain(int argc, _TCHAR* argv[])
{
	renderer = new RenderSystem();
	renderer->SetDisplayCallback(&displayCallback);
	InitResources();
	renderer->SetRenderList(_meshList);
	renderer->StartRender();
	

	return 0;
}

void displayCallback()
{
	_meshList[0]->setWorldCoordinate(_meshList[0]->getWorldCoordinate() + glm::vec3(0,0,0));
}

void InitResources()
{
	_meshList.push_back(new Cube());
}
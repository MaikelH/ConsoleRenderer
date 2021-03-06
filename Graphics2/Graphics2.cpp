// Graphics2.cpp : Defines the entry point for the console application.
//
//

#include "stdafx.h"
#include "RenderSystem.h"
#include "Mesh.h"
#include "Cube.h"
#include <glm\gtc\matrix_transform.hpp>
#include <time.h>
#include <vector>
#include <boost\date_time\posix_time\posix_time.hpp>
#include <boost\thread.hpp>

void displayCallback();
void InitResources();

RenderSystem* renderer;
std::vector<Mesh*> _meshList;
bool startup = false;
clock_t endTime;
Camera* camera;

int _tmain(int argc, _TCHAR* argv[])
{
	renderer = new RenderSystem();
	camera = new Camera();

	renderer->SetDisplayCallback(&displayCallback);
	renderer->SetCamera(camera);
	InitResources();
	renderer->SetRenderList(_meshList);
	renderer->StartRender();


	_meshList[0]->Rotate(45, glm::vec3(0, 0, 1));
	return 0;
}

void displayCallback()
{
	clock_t start = clock();
	double duration = (start - endTime) / ((double) CLOCKS_PER_SEC/1000);

	double angle = 1.0 * duration;

	_meshList[0]->Rotate( 0.5 , glm::vec3(0,1,0));
	
	endTime = clock();
	boost::this_thread::sleep(boost::posix_time::milliseconds(10));
}

void InitResources()
{
	_meshList.push_back(new Cube());
	_meshList[0]->setWorldCoordinate(glm::vec3(15,15,0));
}
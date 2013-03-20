// Graphics2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RenderSystem.h"


int _tmain(int argc, _TCHAR* argv[])
{
	RenderSystem* renderer =  new RenderSystem();
	renderer->StartRender();

	return 0;
}


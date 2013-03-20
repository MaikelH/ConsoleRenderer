#pragma once
#include <boost/function.hpp>
#include <Windows.h>
#include <vector>
#include "Mesh.h"

enum ForegroundColor {
	RED = FOREGROUND_RED,
	BLUE = FOREGROUND_BLUE,
	GREEN = FOREGROUND_GREEN,
	WHITE = RED | GREEN | BLUE
};

enum BackgroundColor {
	BACK_BLUE = BACKGROUND_BLUE,
	BACK_RED  = BACKGROUND_RED,
	BACK_BLACK = 0x0
};

class RenderSystem
{
public:
	RenderSystem(void);
	~RenderSystem(void);

	void StartRender();
	void StopRender();
	void SetDisplayCallback(boost::function<void ()> function);
	void SetBackgroundColor(BackgroundColor color);
	void SetRenderList(std::vector<Mesh*> const &meshList);

private:
	boost::function<void ()> _displayCallback;
	int columns;
	int rows;
	CHAR_INFO* buffer;
	bool _stop;
	HANDLE _hOUT;
	BackgroundColor _bColor;
	std::vector<Mesh*> _renderList;

	void _renderFunction();
	std::vector<glm::vec4> _processMesh();
};


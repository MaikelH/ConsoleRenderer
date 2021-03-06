#pragma once
#include <boost/function.hpp>
#include <Windows.h>
#include <vector>
#include "Mesh.h"
#include "Camera.h"

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
	void SetCamera(Camera *camera);

private:
	boost::function<void ()> _displayCallback;
	int columns;
	int rows;
	CHAR_INFO* buffer;
	bool _stop;
	HANDLE _hOUT;
	BackgroundColor _bColor;
	std::vector<Mesh*> _renderList;
	Camera* _camera;

	void _renderFunction();
	std::vector<glm::vec4> _processMeshes();
	std::vector<glm::vec4> _connectVertex(glm::vec4 point1, glm::vec4 point2);
};


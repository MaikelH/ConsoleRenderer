#pragma once
#include <boost/function.hpp>
#include <Windows.h>


class RenderSystem
{
public:
	RenderSystem(void);
	~RenderSystem(void);

	void StartRender();
	void SetDisplayCallback(boost::function<void ()> function);
	void StopRender();

private:
	boost::function<void ()> _displayCallback;
	int columns;
	int rows;
	CHAR_INFO* buffer;
	bool _stop;
	HANDLE _hOUT;

	void _renderFunction();
};


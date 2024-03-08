#pragma once

#include "IETThread.h"
#include "IExecutionEvent.h"
#include "IWorkerAction.h"
#include <semaphore>

class IconLoader :    public IETThread, public IWorkerAction
{
private:
	typedef std::string String;
public:
	IconLoader(String path);
	IconLoader(String path, IExecutionEvent* event);
	~IconLoader();
	void setPath(String path);
	void setStreaming(bool stream);
	void onStartTask() override;
	void setSemaphore(std::counting_semaphore<10>* semaphore);

	bool isRunning = false;

private:
	void run() override;

	String path;

	bool isStreaming = true;

	IExecutionEvent* event;

	std::counting_semaphore<10>* sem;

};


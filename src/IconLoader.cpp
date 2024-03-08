#include "IconLoader.h"
#include <iostream>
#include <random>
#include "GameObjectManager.h"
#include "IconSpawner.h"
#include "TextureManager.h"
#include "StringUtils.h"
#include "IExecutionEvent.h"

IconLoader::IconLoader(String path)
{
	this->path = path;
}

IconLoader::IconLoader(String path, IExecutionEvent* event)
{
	this->path = path;
	this->event = event;
}

IconLoader::~IconLoader()
{
}

void IconLoader::setPath(String path)
{
	this->path = path;
}

void IconLoader::setStreaming(bool stream)
{
	this->isStreaming = stream;
}

void IconLoader::onStartTask()
{
	this->run();
}

void IconLoader::setSemaphore(std::counting_semaphore<10> *semaphore)
{
	this->sem = semaphore;
}

void IconLoader::run()
{

	this->sem->acquire();
	IETThread::sleep(5000);

	std::vector<String> tokens = StringUtils::split(path, '/');
	String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];

	TextureManager::getInstance()->instantiateAsTexture(path, assetName, isStreaming);

	std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;

	TextureManager::getInstance()->mutex.lock();
	this->event->onFinishedExecution();
	TextureManager::getInstance()->mutex.unlock();

	this->sem->release();
	delete this;

}

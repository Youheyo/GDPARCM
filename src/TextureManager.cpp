#include <fstream>
#include <iostream>
#include <filesystem>
#include "TextureManager.h"
#include "StringUtils.h"
#include "IETThread.h"
#include <string>
#include "IconLoader.h"
#include "BaseRunner.h"
#include "ThreadPool.h"
#include <semaphore>

std::counting_semaphore<10> texSem(10);

//a singleton class
TextureManager* TextureManager::sharedInstance = NULL;

TextureManager* TextureManager::getInstance() {
	if (sharedInstance == NULL) {
		//initialize
		sharedInstance = new TextureManager();
	}

	return sharedInstance;
}

TextureManager::TextureManager()
{
	this->countStreamingAssets();
	this->pool = new ThreadPool("TexPool", 5);
	this->pool->startScheduler();
}

void TextureManager::loadFromAssetList()
{
	std::cout << "[TextureManager] Reading from asset list" << std::endl;
	std::ifstream stream("Media/assets.txt");
	String path;

	while(std::getline(stream, path))
	{
		std::vector<String> tokens = StringUtils::split(path, '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		this->instantiateAsTexture(path, assetName, false);
		std::cout << "[TextureManager] Loaded texture: " << assetName << std::endl;
	}

}

void TextureManager::loadSingleStreamAsset(int index)
{
	int fileNum = 0;	
	
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		if(index == fileNum)
		{

			String path = entry.path().generic_string();
			IconLoader* iconLoad = new IconLoader(path);
			iconLoad->start();

			break;
			
		}

		fileNum++;
	}
}

void TextureManager::loadMultipleStreamAssets(IExecutionEvent* spwn)
{

	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)){


		String path = entry.path().generic_string();

		IconLoader* il = new IconLoader(path, spwn);
		this->pool->scheduleTask(il);

		
	}
}

void TextureManager::loadAssetsFromDirectory(IExecutionEvent* event)
{

	for (const auto& entry : std::filesystem::directory_iterator(DATA_PATH)){

		String path = entry.path().generic_string();

		IconLoader* il = new IconLoader(path, event);
		il->setSemaphore(&texSem);
		this->pool->scheduleTask(il);
		
	}
}

sf::Texture* TextureManager::getFromTextureMap(const String assetName, int frameIndex)
{
	if (!this->textureMap[assetName].empty()) {
		return this->textureMap[assetName][frameIndex];
	}
	else {
		std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
		return NULL;
	}
}

sf::Texture *TextureManager::getBaseTextureFromList(const int index)
{
    return this->baseTextureList[index];
}

int TextureManager::getNumFrames(const String assetName)
{
	if (!this->textureMap[assetName].empty()) {
		return this->textureMap[assetName].size();
	}
	else {
		std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
		return 0;
	}
}

sf::Texture* TextureManager::getStreamTextureFromList(const int index)
{
	return this->streamTextureList[index];
}

int TextureManager::getNumLoadedStreamTextures() const
{
	return this->streamTextureList.size();
}

int TextureManager::getNumTotalStreamTextures() const
{
	return this->streamingAssetCount;
}

void TextureManager::countStreamingAssets()
{
	this->streamingAssetCount = 0;
	for (const auto& entry : std::filesystem::directory_iterator(DATA_PATH)) {
		this->streamingAssetCount++;
	}
	std::cout << "[TextureManager] Number of streaming assets: " << this->streamingAssetCount << std::endl;
}

void TextureManager::instantiateAsTexture(String path, String assetName, bool isStreaming)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	this->textureMap[assetName].push_back(texture);

	if(isStreaming)
	{
		this->streamTextureList.push_back(texture);
	}
	else
	{
		this->baseTextureList.push_back(texture);
	}
	
}

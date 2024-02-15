#include "IconLoader.h"
#include <iostream>
#include <random>
#include "GameObjectManager.h"
#include "IconSpawner.h"
#include "TextureManager.h"
#include "StringUtils.h"

IconLoader::IconLoader(String path)
{
	this->path = path;
}

IconLoader::~IconLoader()
{

}

void IconLoader::run()
{

	std::vector<String> tokens = StringUtils::split(path, '/');
	String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];

	TextureManager::getInstance()->instantiateAsTexture(path, assetName, true);

	std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;

	GameObjectManager* manager = GameObjectManager::getInstance();
	IconSpawner* spwn = (IconSpawner*)manager->findObjectByName("IconSpawner");

	spwn->spawnIcons();

	delete this;
}

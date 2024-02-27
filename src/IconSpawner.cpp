#include "IconSpawner.h"
#include "GameObjectManager.h"
#include "TextureManager.h"
#include "BaseRunner.h"
#include <iostream>
#include "IExecutionEvent.h"

IconSpawner::IconSpawner() : AGameObject("IconSpawner") {
    
}

IconSpawner::~IconSpawner() {
    AGameObject::~AGameObject();
}

void IconSpawner::initialize() {
    progress = 0;
    // iconAmt = TextureManager::getInstance()->getNumLoadedStreamTextures();
    // xOffset = TextureManager::getInstance()->getStreamTextureFromList(0)->getSize().x;
    // yOffset = TextureManager::getInstance()->getStreamTextureFromList(0)->getSize().y;

    max_per_row = BaseRunner::WINDOW_WIDTH / xOffset;
}

void IconSpawner::processInput(sf::Event event)
{
}


void IconSpawner::update(sf::Time deltaTime) {

    // TextureManager::getInstance()->loadSingleStreamAsset(this->progress);
    // this->progress++;
    if(batch){
        TextureManager::getInstance()->loadMultipleStreamAssets(this);
        batch = false;
    }


}
void IconSpawner::spawnIcons()
{

    IconObject* icon = new IconObject("Icon" + std::to_string(IconList.size()), IconList.size());
    IconList.push_back(icon);

    icon->setPosition(posX * xOffset, currRow * yOffset);

    posX++;
    if(posX >= max_per_row){
        posX = 0;
        currRow++;
    }

    GameObjectManager::getInstance()->addObject(icon);

}

void IconSpawner::onFinishedExecution()
{
    spawnIcons();
}

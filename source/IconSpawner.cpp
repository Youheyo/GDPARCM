#include "IconSpawner.h"
#include "GameObjectManager.h"
#include "TextureManager.h"
#include "BaseRunner.h"
#include <iostream>

IconSpawner::IconSpawner() : AGameObject("IconSpawner") {
    
}

IconSpawner::~IconSpawner() {
    AGameObject::~AGameObject();
}

void IconSpawner::initialize() {
    progress = 0;
    iconAmt = TextureManager::getInstance()->getNumLoadedStreamTextures();
    xOffset = TextureManager::getInstance()->getStreamTextureFromList(0)->getSize().x;
    yOffset = TextureManager::getInstance()->getStreamTextureFromList(0)->getSize().y;

    max_per_row = BaseRunner::WINDOW_WIDTH / xOffset;
}

void IconSpawner::processInput(sf::Event event)
{
}

void IconSpawner::update(sf::Time deltaTime) {

    if(progress < this->iconAmt){

        IconObject* icon = new IconObject("Icon" + std::to_string(progress), progress);

        if(posX >= max_per_row){
            posX = 0;
            currRow++;
        }

        icon->setPosition(posX * xOffset, currRow * yOffset);
        icon->setScale(1,1);
        GameObjectManager::getInstance()->addObject(icon);
        progress++;
        posX++;
    }

}

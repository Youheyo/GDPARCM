#include "ImageViewer.h"
#include "TextureManager.h"
#include "BaseRunner.h"
#include "GameObjectManager.h"

ImageViewer::ImageViewer(bool *finishFlag) : AGameObject("ImageViewer") {
    this->loadFinish = finishFlag;
}

ImageViewer::~ImageViewer() {
    
}

void ImageViewer::initialize() {

    *loadFinish = false;

    // this->setPosition(BaseRunner::WINDOW_WIDTH / 2, BaseRunner::WINDOW_HEIGHT / 2);
	
    cropX = BaseRunner::WINDOW_WIDTH;
    cropY = BaseRunner::WINDOW_HEIGHT;

}

void ImageViewer::processInput(sf::Event event) {

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){ // * Speed up scrolling
        speed_multiplier = 5;
    }


}

void ImageViewer::update(sf::Time deltaTime) {
    if(!started){ // * Start loading assets
        started = true;
        TextureManager::getInstance()->loadAssetsFromDirectory(this);
        // TextureManager::getInstance()->loadMultipleStreamAssets(this);
    }


    if(*loadFinish){
        ticks += deltaTime.asSeconds();

        for(int i = 0; i < ImgGallery.size(); i++){
            int revVal = 1;
            if(reverse) revVal = -1;
            ImgGallery[i]->setPosition( 0, ImgGallery[i]->getPosition().y - ticks * revVal * speed_multiplier);
        }
        if(ImgGallery[ImgGallery.size() - 1]->getPosition().y < BaseRunner::WINDOW_HEIGHT || // * Last Image goes to left side
        ImgGallery[0]->getPosition().y > BaseRunner::WINDOW_HEIGHT / 2){                         // * First Image goes to right side
            ticks == 0;
            reverse = !reverse;
        }

        speed_multiplier = 1;
    }
}

void ImageViewer::onFinishedExecution()
{
    IconObject* obj = new IconObject("Art" +  std::to_string(this->ImgGallery.size()), this->ImgGallery.size());
    ImgGallery.push_back(obj);
    
    if(this->ImgGallery.size() >= TextureManager::getInstance()->getNumTotalStreamTextures()){

        for(int i = 0 ; i < ImgGallery.size(); i++){
            GameObjectManager::getInstance()->addObject(ImgGallery[i]);
            ImgGallery[i]->setPosition(0 ,BaseRunner::WINDOW_HEIGHT * i);
        }
        *loadFinish = true;
    }

}

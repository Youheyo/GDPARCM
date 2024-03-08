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
    }

    // * Starts Scrolling through gallery
    if(ScrollGallery){

        ticks += deltaTime.asSeconds();

        // * Verticallly Move 
        for(int i = 0; i < ImgGallery.size(); i++){
            int revVal = 1;
            if(reverse) revVal = -1;

            ImgGallery[i]->setPosition( 0, ImgGallery[i]->getPosition().y  - ticks * revVal * speed_multiplier );
        }

        // * Flip
        if(ImgGallery[ImgGallery.size() - 1]->getPosition().y < BaseRunner::WINDOW_HEIGHT || // * Last Image reaches bottom
            ImgGallery[0]->getPosition().y > BaseRunner::WINDOW_HEIGHT * normalize ){            // * First Image reaches top
            
            normalize = .5;
            reverse = !reverse;

        }

        speed_multiplier = 1;
    }
}

// * For Threads: Instantiates the Icon Object and adds it to the vector
// * Flags the bool as finished loading to be used by BaseRunner and LoadingScreen
void ImageViewer::onFinishedExecution()
{
    IconObject* obj = new IconObject("Art" +  std::to_string(this->ImgGallery.size()), this->ImgGallery.size());
    ImgGallery.push_back(obj);
    
    // * Flag finish loading if done
    if(this->ImgGallery.size() >= TextureManager::getInstance()->getNumTotalStreamTextures()){

        *loadFinish = true;
    }

}

// * Called from BaseRunner
// * Places the images on screen and starts the scroll
void ImageViewer::TransitionAction()
{
    ScrollGallery = true;   
    for(int i = 0 ; i < ImgGallery.size(); i++){
        GameObjectManager::getInstance()->addObject(ImgGallery[i]);
        ImgGallery[i]->setPosition(0 ,BaseRunner::WINDOW_HEIGHT * i );
    }
}

#include "ImageViewer.h"
#include "TextureManager.h"
#include "BaseRunner.h"

ImageViewer::ImageViewer(bool *finishFlag) : AGameObject("ImageViewer") {
    this->loadFinish = finishFlag;
}

ImageViewer::~ImageViewer() {
    
}

void ImageViewer::addTexture(sf::Texture image) {
    // this->ImgGallery.push_back(image);
}

void ImageViewer::initialize() {
    this->sprite = new sf::Sprite();

    // this->setPosition(BaseRunner::WINDOW_WIDTH / 2, BaseRunner::WINDOW_HEIGHT / 2);
	
    cropX = BaseRunner::WINDOW_WIDTH;
    cropY = BaseRunner::WINDOW_HEIGHT;

    this->sprite->setTextureRect(sf::IntRect(0,0,cropX, cropY)); 


}

void ImageViewer::processInput(sf::Event event) {

    if(!loadFinish) return;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        index--;
        if(index < 0) index = this->ImgGallery.size() - 1;

        this->sprite->setTexture(*this->ImgGallery[index]);

    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        index++;
        if(index > this->ImgGallery.size() - 1) index = 0;

        this->sprite->setTexture(*this->ImgGallery[index]);

    }

    float speed = 1;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        speed = 5;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        this->setPosition(this->posX - 1 * speed, posY);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->setPosition(this->posX + 1 * speed, posY);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        this->setPosition(this->posX, posY - 1 * speed);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        this->setPosition(this->posX, posY + 1 * speed);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
        cropX += 1 * speed;
        cropY += 1 * speed;
        this->sprite->setTextureRect(sf::IntRect(0, 0, cropX , cropY)); 
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
        cropX -= 1 * speed;
        cropY -= 1 * speed;
        this->sprite->setTextureRect(sf::IntRect(0, 0, cropX, cropY)); 
    }

}

void ImageViewer::update(sf::Time deltaTime) {
    if(!started){
        started = true;
        TextureManager::getInstance()->loadAssetsFromDirectory(this);
        // TextureManager::getInstance()->loadMultipleStreamAssets(this);

    }
}

void ImageViewer::onFinishedExecution()
{

    sf::Texture* tl = TextureManager::getInstance()->getStreamTextureFromList(this->ImgGallery.size());
    
    this->ImgGallery.push_back(tl);


    // if(this->ImgGallery.size() - 1 == 0){
    //     this->sprite->setTexture(*this->ImgGallery[0]);
    // }

    // this->setScale(0.1f, 0.1f);
    if(this->ImgGallery.size() >= TextureManager::getInstance()->getNumTotalStreamTextures()){
        this->loadFinish = true;
        this->sprite->setTexture(*this->ImgGallery[0]);

    }
}

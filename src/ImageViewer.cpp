#include "ImageViewer.h"
#include "TextureManager.h"
#include "BaseRunner.h"

ImageViewer::ImageViewer() : AGameObject("ImageViewer") {
    
}

ImageViewer::~ImageViewer() {
    
}

void ImageViewer::addTexture(sf::Texture image) {
    // this->ImgGallery.push_back(image);
}

void ImageViewer::initialize() {
    this->sprite = new sf::Sprite();

    // this->setPosition(BaseRunner::WINDOW_WIDTH / 2, BaseRunner::WINDOW_HEIGHT / 2);
    this->setPosition(0,0);
	this->sprite->setTextureRect(sf::IntRect(0,0,BaseRunner::WINDOW_WIDTH, BaseRunner::WINDOW_HEIGHT)); 


}

void ImageViewer::processInput(sf::Event event) {

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

    if(this->ImgGallery.size() - 1 == 0){
        this->sprite->setTexture(*this->ImgGallery[0]);
    }
}

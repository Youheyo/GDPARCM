#pragma once
#include "AGameObject.h"
#include "IExecutionEvent.h"

class ImageViewer : public AGameObject, public IExecutionEvent{

public:
    ImageViewer(bool *loadFinish);
    ~ImageViewer();

    void initialize() override;
    void processInput(sf::Event event) override;
    void update(sf::Time deltaTime) override;

    void onFinishedExecution() override;

    void addTexture(sf::Texture image);


private:

    bool started = false;
    bool loadFinish;

    int index = 0;
    std::vector<sf::Texture*> ImgGallery;

    sf::IntRect spriteRect;

    int cropX = 0; 
    int cropY = 0;

};
#pragma once
#include "AGameObject.h"
#include "IExecutionEvent.h"

class ImageViewer : public AGameObject, public IExecutionEvent{

public:
    ImageViewer();
    ~ImageViewer();

    void initialize() override;
    void processInput(sf::Event event) override;
    void update(sf::Time deltaTime) override;

    void onFinishedExecution() override;

    void addTexture(sf::Texture image);


private:

    bool started = false;

    int index = 0;
    std::vector<sf::Texture*> ImgGallery;

};
#pragma once
#include "AGameObject.h"
#include "IExecutionEvent.h"
#include "IconObject.h"

class ImageViewer : public AGameObject, public IExecutionEvent{

public:
    ImageViewer(bool *loadFinish);
    ~ImageViewer();

    void initialize() override;
    void processInput(sf::Event event) override;
    void update(sf::Time deltaTime) override;

    void onFinishedExecution() override;

private:

    bool started = false;
    bool* loadFinish;

    int index = 0;

    float ticks;
    bool reverse = false;
    bool speedFlag = false;
    float speed_multiplier = 1.0f; 

    std::vector<IconObject*> ImgGallery;

    sf::IntRect spriteRect;

    int cropX = 0; 
    int cropY = 0;

};
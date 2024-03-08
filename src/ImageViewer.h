#pragma once
#include "AGameObject.h"
#include "IExecutionEvent.h"
#include "IconObject.h"
#include "ITransitionEvent.h"

class ImageViewer : public AGameObject, public IExecutionEvent, public ITransitionEvent{

public:
    ImageViewer(bool *loadFinish);
    ~ImageViewer();

    void initialize() override;
    void processInput(sf::Event event) override;
    void update(sf::Time deltaTime) override;

    void onFinishedExecution() override;
    void TransitionAction() override;

private:

    bool ScrollGallery = false;

    bool started = false;
    bool* loadFinish;

    int normalize = 2;

    float ticks;
    bool reverse = false;
    bool speedFlag = false;
    float speed_multiplier = 1.0f; 

    std::vector<IconObject*> ImgGallery;

};
#include "BaseRunner.h"
#include  "GameObjectManager.h"
#include "BGObject.h"
#include "TextureManager.h"
#include "FPSCounter.h"
#include "IconSpawner.h"
#include "IconObject.h"
#include "ImageViewer.h"
#include "LoadingScreen.h"
#include "ProgressTrack.h"

/// <summary>
/// This demonstrates a running parallax background where after X seconds, a batch of assets will be streamed and loaded.
/// </summary>
const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

BaseRunner::BaseRunner() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "HO: Entity Component", sf::Style::Close) {
	//load initial textures
	TextureManager::getInstance()->loadFromAssetList();

	//load objects
	BGObject* bgObject = new BGObject("BGObject");
	GameObjectManager::getInstance()->addObject(bgObject);

	
	// IconSpawner* iSpawn = new IconSpawner();
	// GameObjectManager::getInstance()->addObject(iSpawn);
	
	ImageViewer* viewer = new ImageViewer(&loadingScreenFinished);
	GameObjectManager::getInstance()->addObject(viewer);

	LoadingScreen* ls = new LoadingScreen(&loadingScreenFinished);
	GameObjectManager::getInstance()->addObject(ls);

	// * Loadscreen transition set up
	this->fadeRect = new sf::RectangleShape(sf::Vector2f(BaseRunner::WINDOW_WIDTH, BaseRunner::WINDOW_HEIGHT));
	this->fadeRect->setFillColor(sf::Color::White);
	fadeRect->setPosition(0,0);

	
	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fpsCounter);

	ProgressTrack* tracker = new ProgressTrack();
	GameObjectManager::getInstance()->addObject(tracker);

}

void BaseRunner::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (this->window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;

			processEvents();
			//update(TIME_PER_FRAME);
			update(elapsedTime);
		}

		render();
	}
}

void BaseRunner::processEvents()
{
	sf::Event event;
	if (this->window.pollEvent(event)) {
		switch (event.type) {
		
		default: GameObjectManager::getInstance()->processInput(event); break;
		case sf::Event::Closed:
			this->window.close();
			break;
		}
	}

	// * Start the transition when loading is finished
	if(loadingScreenFinished && !startTransition){
		startTransition = true;
		transition = true;
	}

}

void BaseRunner::update(sf::Time elapsedTime) {
	GameObjectManager::getInstance()->update(elapsedTime);

	// * Fades in to a white screen then fades out
	if(transition){

   		transitionAlphaVal += elapsedTime.asSeconds() * fadeDir * 255;

		// * When Alpha reaches peak, initiate transition actions and fade out
		if(transitionAlphaVal >= 255){
			fadeDir *= -1;
			static_cast<ImageViewer*>(GameObjectManager::getInstance()->findObjectByName("ImageViewer"))->TransitionAction();
			static_cast<LoadingScreen*>(GameObjectManager::getInstance()->findObjectByName("LoadingScreen"))->TransitionAction();
			GameObjectManager::getInstance()->deleteObjectByName("ProgressTrack");

		}

		fadeRect->setFillColor(sf::Color(255,255,255, transitionAlphaVal));

		if(transitionAlphaVal < 0){
			transition = false;	
		}
	}
}

void BaseRunner::render() {
	this->window.clear();
	GameObjectManager::getInstance()->draw(&this->window);

	// * Draw Transition Last to be drawn over the rest
	if(transition){
		this->window.draw(*fadeRect);
	}
	this->window.display();
}
#include "LoadingScreen.h"
#include "TextureManager.h"
#include "IconObject.h"
#include "GameObjectManager.h"

LoadingScreen::LoadingScreen(bool *finishState) : AGameObject("LoadingScreen"){
	this->finishState = finishState;
}

LoadingScreen::~LoadingScreen() {
    
}

void LoadingScreen::initialize() {

	mode = static_cast<MiniGameMode>(rand() % 2);

	TextureManager* tm = TextureManager::getInstance();
    sf::Texture* pawTex = tm->getFromTextureMap("PawPrint", 0);

	// * PreLoad all paw objects
	for (int i = 0; i < maxCount; i++)
	{
		IconObject* icon = new IconObject("Paw" + i, i);
		GameObjectManager::getInstance()->addObject(icon);		

		// * Set Texture, bounds, and rotation
		// TODO Use both left and right paws respectively
		icon->getSprite()->setTexture(*pawTex);
		icon->getSprite()->setTextureRect(sf::IntRect(0,0, pawTex->getSize().x / 2, pawTex->getSize().y));
		icon->getSprite()->setRotation(90);

		this->pawList.push_back(icon);

	}
	

}

void LoadingScreen::processInput(sf::Event Event) {

	// * Rhythm Button

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		switch (mode)
		{
		case MiniGameMode::rhythm :
			time_check = ticks;
			if(time_check > interval - ok_range && time_check <= interval){
				// * Bigger Paw
				good++;
				goodFlag = true;
			}
			break;
		case MiniGameMode::mash :
				// * Add a random Paw
			break;
		
		default:
			break;
		}
	}

}

void LoadingScreen::update(sf::Time deltaTime) {
    
	TextureManager* tm = TextureManager::getInstance();

	currProg = tm->getNumLoadedStreamTextures() / tm->getNumTotalStreamTextures();

	ticks += deltaTime.asMicroseconds();


	// * Increments count for interactive loading screen
	if(ticks > interval){

		ticks = 0;
		count++;

		if( count >= maxCount){ // * Count reaches max

			count = 0;

			if(good >= maxCount){ // * Add Score When all good
				// * Reward
				score++;
			}

		}

		// * Spawn Sprite

		this->sprite;

		goodFlag = false;
	}

}

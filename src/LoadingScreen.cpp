#include "LoadingScreen.h"
#include "TextureManager.h"
#include "IconObject.h"
#include "GameObjectManager.h"
#include "MathUtils.h"
#include <random>
#include "BaseRunner.h"

LoadingScreen::LoadingScreen(bool *finishState) : AGameObject("LoadingScreen"){
	this->finishState = finishState;
}

LoadingScreen::~LoadingScreen() {
    
}

void LoadingScreen::initialize() {

	// ! Rhythm Mode not implemented
	// mode = static_cast<MiniGameMode>(rand() % 2);
	mode = mash;

	TextureManager* tm = TextureManager::getInstance();

	tm->mutex.lock();
    pawTex = tm->getFromTextureMap("PawPrint", 0);

	fangTex = tm->getFromTextureMap("Fang",0);

	// * PreLoad all paw objects
	for (int i = 0; i < maxCount; i++)
	{
		IconObject* icon = new IconObject("Paw" + std::to_string(i) , 0);
		icon->getFromStream = false;
		GameObjectManager::getInstance()->addObject(icon);		

		// * Set Texture, bounds, and rotation
		icon->getSprite()->setTexture(*pawTex);
		if(i % 2 == 0){
			icon->getSprite()->setTextureRect(sf::IntRect(0,0, pawTex->getSize().x / 2, pawTex->getSize().y));
		}
		else
		icon->getSprite()->setTextureRect(sf::IntRect(pawTex->getSize().x / 2,0, pawTex->getSize().x / 2, pawTex->getSize().y));
		icon->getSprite()->setRotation(90);
		icon->setScale(0.5,0.5);
		this->pawList.push_back(icon);

	}
	tm->mutex.unlock();

}

void LoadingScreen::processInput(sf::Event Event) {

	// * Rhythm Button

    if(Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Space){

		if(keyCheck) return;
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
			{
				TextureManager::getInstance()->mutex.lock();

				std::random_device rd; 
				std::mt19937 gen(rd());

				std::uniform_int_distribution<int> wBorder(0, BaseRunner::WINDOW_WIDTH);
				std::uniform_int_distribution<int> hBorder(0, BaseRunner::WINDOW_HEIGHT);
				std::uniform_int_distribution<int> rollBounds(0, 100);

				int roll = rollBounds(gen);
				if(roll < 5 ){ 		// * Place a fang
					IconObject* fang = new IconObject("Fang" + std::to_string(score),0);
					fang->getFromStream = false;
					GameObjectManager::getInstance()->addObject(fang);
					fang->getSprite()->setScale(0.5, 0.5);
					fang->getSprite()->setTexture(*fangTex);
					fang->getSprite()->setRotation(rand());
					fang->setPosition(wBorder(gen), hBorder(gen));
					score++;

				}
				else{ 				// * Place a paw
					// * Add a random Paw
					count++;
					if(count >= this->pawList.size()){ // * Spawn new if no more preloaded paws
						
						IconObject* icon = new IconObject("Paw" + std::to_string(count), 0);
						icon->getFromStream = false;	
						GameObjectManager::getInstance()->addObject(icon);		

						// * Set Texture, bounds, and rotation
						icon->getSprite()->setTexture(*pawTex);
						if(count % 2 == 0){
							icon->getSprite()->setTextureRect(sf::IntRect(0,0, pawTex->getSize().x / 2, pawTex->getSize().y));
						}
						else{
							icon->getSprite()->setTextureRect(sf::IntRect(pawTex->getSize().x / 2,0, pawTex->getSize().x / 2, pawTex->getSize().y));
						}
						icon->setScale(0.5,0.5);
						this->pawList.push_back(icon);
					}
					this->pawList[count]->getSprite()->setRotation(rand());
					this->pawList[count]->setPosition(wBorder(gen), hBorder(gen));

				}

				TextureManager::getInstance()->mutex.unlock();
				break;
			}
			
			default:
				break;
			}
			keyCheck = true;
	}
	else  if(Event.type == sf::Event::KeyReleased && Event.key.code == sf::Keyboard::Space){
		keyCheck = false;
	}
}

void LoadingScreen::update(sf::Time deltaTime) {
    
	TextureManager* tm = TextureManager::getInstance();

	currProg = tm->getNumLoadedStreamTextures() / tm->getNumTotalStreamTextures();

	ticks += deltaTime.asMicroseconds();


	// * Delete all loading screen objects when assets are all loaded
	if(*finishState == true){
		deleteLoadingObjects();
	}


#pragma region Rhythm Mode

	// * Increments count for interactive loading screen
	if(ticks > interval && mode == rhythm){

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

#pragma endregion

}


// * Deletes all the assets of loading screen. Then delete itself
void LoadingScreen::deleteLoadingObjects()
{

	// TODO Something to make the transition for assets

	GameObjectManager* gm = GameObjectManager::getInstance();

	int pawCount;

	if(mode == MiniGameMode::mash){
		pawCount = count + 10;
	}
	else{
		pawCount = maxCount;
	}

	for(int i = 0; i < pawCount; i++ ){
		gm->deleteObjectByName("Paw"+ std::to_string(i));
	}
	for(int i = 0; i < score; i++ ){
		gm->deleteObjectByName("Fang"+ std::to_string(i));
	}

	GameObjectManager::getInstance()->deleteObject(this);
}

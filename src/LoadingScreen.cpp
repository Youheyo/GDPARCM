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
    AGameObject::~AGameObject();
}

void LoadingScreen::initialize() {

	// ! Rhythm Mode not implemented
	// mode = static_cast<MiniGameMode>(rand() % 2);
	mode = mash;

	TextureManager* tm = TextureManager::getInstance();

	tm->mutex.lock();
    pawTex = tm->getFromTextureMap("PawPrint", 0);

	fangTex = tm->getFromTextureMap("Fang",0);

	if(mode == MiniGameMode::rhythm){
		IconObject* fangObj = new IconObject("Fang1", 0);
		fangObj->getFromStream = false;
		fangList.push_back(fangObj);
		GameObjectManager::getInstance()->addObject(fangObj);
		fangObj->getSprite()->setTexture(*fangTex);
		fangObj->setPosition(9999,9999);
	}
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
		icon->setScale(0.2,0.2);
		icon->setPosition(9999,9999);
		this->pawList.push_back(icon);

	}
	tm->mutex.unlock();

	this->totalLoad = tm->getNumTotalStreamTextures();
}

void LoadingScreen::processInput(sf::Event Event) {

    if(Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Space && !*this->finishState){

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

#pragma region Randomization
				std::random_device rd; 
				std::mt19937 gen(rd());

				std::uniform_int_distribution<int> wBorder(0, BaseRunner::WINDOW_WIDTH);
				std::uniform_int_distribution<int> hBorder(0, BaseRunner::WINDOW_HEIGHT);
				std::uniform_int_distribution<int> rollBounds(0, 100);
#pragma endregion
				
				int roll = rollBounds(gen);

				if(roll < 5 ){ 		// * Place a fang
					IconObject* fang = new IconObject("Fang" + std::to_string(score),0);
					fang->getFromStream = false;
					fangList.push_back(fang);
					GameObjectManager::getInstance()->addObject(fang);
					fang->getSprite()->setTexture(*fangTex);
					fang->getSprite()->setRotation(rand());
					fang->setScale(0.5f,0.5f);
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
						icon->setScale(0.2,0.2);
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

	if(tm->getNumLoadedStreamTextures() > currProg){
  		currProg = tm->getNumLoadedStreamTextures();
	}

	ticks += deltaTime.asSeconds();

#pragma region Rhythm Mode

	// * Increments count for interactive loading screen
	if(ticks > interval && mode == rhythm && !this->finishState){

		// * Hide all 
		if(count >= maxCount){
			for(int i = 0; i < pawList.size(); i++){
				pawList[i]->setPosition(9999, 9999);
				pawList[i]->setScale(0.5, 0.5);
			}
			fangList[0]->setPosition(9999,9999);

			count = 0;
		}

		ticks = 0;
		count++;

		if( count >= maxCount){ // * Count reaches max


			if(good >= maxCount){ // * Add Score When all good
				// * Reward
				score++;
			}

		}

		// * Spawn Sprite
		if(goodFlag && good >= maxCount){
			fangList[0]->setPosition(BaseRunner::WINDOW_WIDTH - 64, BaseRunner::WINDOW_HEIGHT - 64);
		}else{
			spawnPaw();
		}

		goodFlag = false;
	}

#pragma endregion

}

void LoadingScreen::TransitionAction()
{
	deleteLoadingObjects();
}

// * Deletes all the assets of loading screen. Then delete itself
void LoadingScreen::deleteLoadingObjects()
{

	GameObjectManager* gm = GameObjectManager::getInstance();

	for(int i = 0; i < pawList.size(); i++){
		gm->deleteObject(pawList[i]);
	}
	for(int i = 0; i < fangList.size(); i++){
		gm->deleteObject(fangList[i]);
	}

	GameObjectManager::getInstance()->deleteObject(this);
}

float LoadingScreen::checkProgress()
{
    return currProg / totalLoad;
}

void LoadingScreen::spawnPaw()
{
	float heightMod = 1;
	if(count % 2 == 1) heightMod = 2;

	pawList[count]->setPosition(
		128 + 128 * count,
		BaseRunner::WINDOW_HEIGHT - 256 / heightMod
	);

	if(goodFlag){
		pawList[count]->setScale(0.5,0.5);
	}
}

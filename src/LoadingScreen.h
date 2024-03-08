#pragma once

#include "AGameObject.h"
#include <vector>
#include "IconObject.h"
#include "ITransitionEvent.h"
class LoadingScreen : public AGameObject, public ITransitionEvent {

public:

	LoadingScreen(bool *finishState);
	~LoadingScreen();

	void initialize() override;
	void processInput(sf::Event event) override;
	void update(sf::Time deltaTime) override;

	void TransitionAction() override;

	void deleteLoadingObjects();

	float checkProgress();

private:

	bool* finishState = nullptr;

	float currProg = 0;
	float totalLoad = 0;
	float loadProgress = 0;

	bool keyCheck;

#pragma region Textures
	sf::Texture* pawTex;
	std::vector<IconObject*> pawList;

	sf::Texture* fangTex;
	std::vector<IconObject*> fangList;
#pragma endregion

	float ticks = 0.0f;

	int count = 0;		// * Used to count Rhythm Game progress. Counts paw amount spawned if mash mode

	int score = 0;		// * Increments when good == maxCount

	void spawnPaw();
};
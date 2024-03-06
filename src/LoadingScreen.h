#pragma once

#include "AGameObject.h"
#include <vector>
#include "IconObject.h"

class LoadingScreen : public AGameObject{

public:

	enum MiniGameMode{ rhythm, mash};

	LoadingScreen(bool *finishState);
	~LoadingScreen();

	void initialize() override;
	void processInput(sf::Event event) override;
	void update(sf::Time deltaTime) override;

	void deleteLoadingObjects();

private:

	MiniGameMode mode = rhythm;

	bool* finishState = nullptr;

	float currProg;

	bool keyCheck;

#pragma region Textures
	sf::Texture* pawTex;
	std::vector<IconObject*> pawList;

	sf::Texture* fangTex;
#pragma endregion

#pragma region Rhythm minigame values

	float interval = 5.0f;
	float ok_range = 0.5f;

	float ticks = 0.0f;
	float time_check = 0.0f;


	int maxCount = 10;	// * Max rhyhtm game nodes
	int count = 0;		// * Used to count Rhythm Game progress. Counts paw amount spawned if mash mode
	int good = 0;		// * Tracks correctly timed presses

	int score = 0;		// * Increments when good == maxCount
	bool goodFlag = false;

#pragma endregion

};
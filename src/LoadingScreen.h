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

private:

	MiniGameMode mode = rhythm;

	bool* finishState = nullptr;

	float currProg;

	std::vector<IconObject*> pawList;

#pragma region Rhythm minigame values

	float interval = 5.0f;
	float ok_range = 0.5f;

	float ticks = 0.0f;
	float time_check = 0.0f;


	int maxCount = 10;
	int count = 0;
	int good = 0;

	int score = 0;
	bool goodFlag = false;

#pragma endregion

};
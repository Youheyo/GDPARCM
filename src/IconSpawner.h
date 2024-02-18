#pragma once
#include "IExecutionEvent.h"
#include "IconObject.h"
#include <vector>

class IconSpawner : public AGameObject, public IExecutionEvent{

public:
	IconSpawner();
	~IconSpawner();


	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

	void spawnIcons();
	void onFinishedExecution();

private:

	std::vector<IconObject*> IconList;

	int progress = 0;

	float stream_delay = 0.01f;
	float ticks = 0.0f;

	int iconAmt = 480;
	float xOffset = 64;
	float yOffset = 64;

	int max_per_row = 20;
	int posX = 0;
	int currRow = 0;

	bool batch = true;

};
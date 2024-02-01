#include "IconObject.h"

class IconSpawner : public AGameObject{

public:
	IconSpawner();
	~IconSpawner();

	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);


private:
	int progress = 0;
	int iconAmt = 480;
	float xOffset = 64;
	float yOffset = 64;

	int max_per_row = 20;
	int posX = 0;
	int currRow = 0;

};
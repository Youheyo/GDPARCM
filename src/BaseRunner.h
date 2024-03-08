#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
class BaseRunner : private sf::NonCopyable
{
public:
	static const sf::Time	TIME_PER_FRAME;
	static const int WINDOW_WIDTH = 1920;
	static const int WINDOW_HEIGHT = 1080;

	BaseRunner();
	void run();


private:
	
	bool loadingScreenFinished = false;
	bool transition = false;
	int fadeDir = 1;
	bool startTransition = false;
	float transitionAlphaVal = 0;

	sf::RectangleShape* fadeRect;

	sf::RenderWindow		window;

	void render();
	void processEvents();
	void update(sf::Time elapsedTime);
};



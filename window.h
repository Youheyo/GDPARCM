#include <SFML/Graphics.hpp>

class Window{
public:
	int window_width = 1920;
	int window_height = 1080;
	sf::Time time;

	Window();
	~Window();

	void run();

private:
	sf::RenderWindow main_window;

	void processEvents();
	void update(sf::Time time);
	void render();
};
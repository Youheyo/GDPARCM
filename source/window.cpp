#include "window.h"
#include <iostream>

const sf::Time Time_per_Frame = sf::seconds(1.f/60.f);

Window::Window() : main_window(sf::VideoMode(window_width, window_height), "Main Window", sf::Style::Close){


	std::cout << "Window Created\n";
}

Window::~Window() {
    
}

void Window::run()
{
    sf::Clock clock;
	sf::Time timeSinceUpdate = sf::Time::Zero;
	while(this->main_window.isOpen()){

		sf::Time elapsedTime = clock.restart();
		timeSinceUpdate += elapsedTime;
		while(timeSinceUpdate > Time_per_Frame){

			processEvents();
			update(elapsedTime);
		}
		render();
	}
}

void Window::processEvents()
{
	    sf::Event event;
        while (main_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                main_window.close();
        }
}

void Window::update(sf::Time time)
{
	
}

void Window::render() {
    this->main_window.clear();

	sf::CircleShape circle(100.0f);
	circle.setFillColor(sf::Color::Red);
	main_window.draw(circle);

	this->main_window.display();
}

#include "FPSCounter.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include "BaseRunner.h"

FPSCounter::FPSCounter(): AGameObject("FPSCounter")
{
}

FPSCounter::~FPSCounter()
{
	delete this->statsText->getFont();
	delete this->statsText;
	AGameObject::~AGameObject();
}

void FPSCounter::initialize()
{
	sf::Font* font = new sf::Font();
	font->loadFromFile("Media/Sansation.ttf");

	this->statsText = new sf::Text();
	this->statsText->setFont(*font);
	this->statsText->setPosition(BaseRunner::WINDOW_WIDTH - 150, BaseRunner::WINDOW_HEIGHT - 70);
	this->statsText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->statsText->setOutlineThickness(2.5f);
	this->statsText->setCharacterSize(35);
}

void FPSCounter::processInput(sf::Event event)
{
}

void FPSCounter::update(sf::Time deltaTime)
{
	updateTime += deltaTime;
	framesPassed++;
	this->updateFPS(deltaTime);
}

void FPSCounter::draw(sf::RenderWindow* targetWindow)
{
	AGameObject::draw(targetWindow);

	if(this->statsText != nullptr)
		targetWindow->draw(*this->statsText);
}

void FPSCounter::updateFPS(sf::Time elapsedTime)
{

	// int fps = 1.0f / elapsedTime.asSeconds();

	if(updateTime.asSeconds() > 0.5f){
		fps = updateTime.asSeconds() * framesPassed;

		displayCounter = !displayCounter;
		if(displayCounter)
		this->statsText->setString("FPS: " + to_string(fps));
		else
		this->statsText->setString("");

		updateTime = updateTime.Zero;
		framesPassed = 0;
	}

}

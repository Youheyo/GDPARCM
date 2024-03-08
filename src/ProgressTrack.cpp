#include "ProgressTrack.h"
#include "BaseRunner.h"
#include "GameObjectManager.h"

ProgressTrack::ProgressTrack() : AGameObject("ProgressTrack")
{
}

ProgressTrack::~ProgressTrack()
{
    delete this->statsText->getFont();
    delete this->statsText;
    AGameObject::~AGameObject();
}

void ProgressTrack::initialize()
{
    sf::Font* font = new sf::Font();
	font->loadFromFile("Media/Sansation.ttf");

	this->statsText = new sf::Text();
	this->statsText->setFont(*font);
	this->statsText->setPosition( 20, BaseRunner::WINDOW_HEIGHT - 70);
	this->statsText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->statsText->setOutlineThickness(2.5f);
	this->statsText->setCharacterSize(35);

    this->screen = static_cast<LoadingScreen*>(GameObjectManager::getInstance()->findObjectByName("LoadingScreen"));

}

void ProgressTrack::processInput(sf::Event event)
{
}

void ProgressTrack::update(sf::Time deltaTime)
{
    updateProgress();
}

void ProgressTrack::draw(sf::RenderWindow *targetWindow)
{
    AGameObject::draw(targetWindow);

	if(this->statsText != nullptr)
		targetWindow->draw(*this->statsText);
}

void ProgressTrack::setLoadingScreen(LoadingScreen *screen)
{
    this->screen = screen;
}

void ProgressTrack::updateProgress()
{
    if(screen != nullptr){
        int prog = screen->checkProgress() * 100;
        this->statsText->setString("Loading: " + to_string(prog) + "%");
        
    } 
}

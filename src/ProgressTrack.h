#pragma once
#include "AGameObject.h"
#include "LoadingScreen.h"

class ProgressTrack :    public AGameObject
{
	public:
		ProgressTrack();
		~ProgressTrack();
		void initialize() override;
		void processInput(sf::Event event) override;
		void update(sf::Time deltaTime) override;
		void draw(sf::RenderWindow* targetWindow) override;

        void setLoadingScreen(LoadingScreen* screen);
	
	private:
		sf::Text* statsText;
        LoadingScreen* screen = nullptr;

        void updateProgress();
		
};


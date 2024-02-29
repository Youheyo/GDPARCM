#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class AGameObject: sf::NonCopyable
{
	public:
		typedef std::string String;
		AGameObject(String name);
		~AGameObject();
		virtual void initialize() = 0;
		virtual void processInput(sf::Event event) = 0;
		virtual void update(sf::Time deltaTime) = 0;
		virtual void draw(sf::RenderWindow* targetWindow);
		String getName();

		virtual void setPosition(float x, float y);
		virtual void setScale(float x, float y);
		virtual sf::FloatRect getLocalBounds();
		virtual sf::Vector2f getPosition();
		virtual sf::Vector2f getScale();

		virtual sf::Sprite* getSprite();

	protected:
		String name;
		sf::Sprite* sprite = NULL;
		sf::Texture* texture = NULL;

		float posX = 0.0f; float posY = 0.0f;
		float scaleX = 1.0f; float scaleY = 1.0f;
};


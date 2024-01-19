#include "sfmlTest.h"


void sfmlTestWindow()
{

    std::cout << "Test window Successfully called!\n";
    
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML again?!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Cyan);

    sf::RectangleShape rectShape(sf::Vector2f(60,60));
    rectShape.setFillColor(sf::Color::White);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.draw(rectShape);
        window.display();
    }

}
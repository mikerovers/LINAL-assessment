#include <iostream>
#include <SFML/Graphics.hpp>
#include "src/Vector.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lineaire dingen");

    std::vector<Vector*> vectors;
    vectors.push_back(new Vector(60, 60));
    vectors.push_back(new Vector(120, 400));
    vectors.push_back(new Vector(50, 30));

    while (window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        sf::RectangleShape yLine(sf::Vector2f(600.f, 1.f));
        yLine.setPosition(400, 0);
        yLine.rotate(90);
        window.draw(yLine);

        sf::RectangleShape xLine(sf::Vector2f(1200.f, 1.f));
        xLine.setPosition(0, 300);
        window.draw(xLine);

        window.display();
    }

    return 0;
}

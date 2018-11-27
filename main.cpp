#include <iostream>
#include <SFML/Graphics.hpp>
#include "src/Vector2D.h"
#include "src/Matrix.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lineaire dingen", sf::Style::Default, settings);

    std::vector<Vector2D*> vectors;
    vectors.push_back(new Vector2D(60, 60));
    vectors.push_back(new Vector2D(120, 400));
    vectors.push_back(new Vector2D(50, 30));

    auto t1 = Matrix::TranslationMatrix(4, 3);
    auto t2 = Matrix::TranslationMatrix(-4, -3);
    auto s1 = Matrix::ScalingMatrix(2, 2);

    auto res = t1 * s1 * t2;

    auto m6 = Matrix::Matrix2D(4);
    m6(0, 0) = 50;
    m6(1, 0) = 50;

    m6(0, 1) = 300;
    m6(1, 1) = 50;

    m6(0, 2) = 50;
    m6(1, 2) = 300;

    m6(0, 3) = 300;
    m6(1, 3) = 300;

    auto rM = Matrix::RotationMatrix(60);

    window.setKeyRepeatEnabled(false);

    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(800.f, 600.f));
    window.setView(view);

    while (window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        sf::RectangleShape yLine(sf::Vector2f(600.f, 1.f));
        yLine.setPosition(0, -1 * view.getSize().y / 2);
        yLine.rotate(90);
        window.draw(yLine);

        sf::RectangleShape xLine(sf::Vector2f(1200.f, 1.f));
        xLine.setPosition(-1 * view.getSize().x / 2, 0);
        window.draw(xLine);

        m6.draw(window);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            m6.translate(-1, 0);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            m6.translate(1, 0);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            m6.translate(0, -1);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            m6.translate(0, 1);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            m6.rotate(-1);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            m6.rotate(1);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            m6.scale(1.001, 1.001);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        {
            m6.scale(0.999, 0.999);
        }

        for (auto* v : vectors) {
            sf::CircleShape shape(5.f);
            shape.setFillColor(sf::Color::Blue);
            shape.setPosition(static_cast<float>(v->getX()), static_cast<float>(v->getY()));
            window.draw(shape);
        }

        window.display();
    }

    return 0;
}

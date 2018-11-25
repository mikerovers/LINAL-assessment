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
    res.print();

    auto m6 = Matrix::Matrix2D(4);
    m6(0, 0) = 50;
    m6(1, 0) = 50;

    m6(0, 1) = 300;
    m6(1, 1) = 50;

    m6(0, 2) = 50;
    m6(1, 2) = 300;

    m6(0, 3) = 300;
    m6(1, 3) = 300;

    window.setKeyRepeatEnabled(false);

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

        m6.draw(window);

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::LControl)
            {
                m6.scale(1.001, 1.001);
            }

            if (event.key.code == sf::Keyboard::LAlt)
            {
                m6.scale(0.999, 0.999);
            }

            if (event.key.code == sf::Keyboard::Left)
            {
                m6.translate(-1, 0);
            }

            if (event.key.code == sf::Keyboard::Right)
            {
                m6.translate(1, 0);
            }

            if (event.key.code == sf::Keyboard::Up)
            {
                m6.translate(0, -1);
            }

            if (event.key.code == sf::Keyboard::Down)
            {
                m6.translate(0, 1);
            }
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

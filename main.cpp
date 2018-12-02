#include <iostream>
#include <SFML/Graphics.hpp>
#include "src/Vector2D.h"
#include "src/Matrix.h"
#include "src/MyMesh.h"
#include "src/CustomView.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lineaire dingen", sf::Style::Default, settings);

    auto t1 = Matrix::TranslationMatrix(4, 3, 0);
    auto t2 = Matrix::TranslationMatrix(-4, -3, 0);
    auto s1 = Matrix::ScalingMatrix(2, 2, 0);

    auto res = t1 * s1 * t2;

    auto mesh = std::make_unique<MyMesh>();
    mesh->load("cube.obj");
    auto m6 = Matrix::FromModel(*mesh->model);
    m6.scale(50, 50, 50);

    window.setKeyRepeatEnabled(false);

    std::vector<CustomView> views;
    ObjectContainer objects;

    objects.emplace_back(&m6);

    views.emplace_back(top, sf::FloatRect(0.f, 0.f, 0.5f, 0.5f));
    views.emplace_back(side, sf::FloatRect(0.5f, 0.f, 0.5f, 0.5f));
    views.emplace_back(front, sf::FloatRect(0.f, 0.5f, 0.5f, 0.5f));

    auto rotV = Vector3D{100, 8, 100};

    sf::Event event;
    while (window.isOpen()) {
        while(window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            m6.translate(-1, 0, 0);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            m6.translate(1, 0, 0);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            m6.translate(0, -1, 0);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            m6.translate(0, 1, 0);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            m6.scale(1.001, 1.001, 1.001);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            m6.scale(0.999, 0.999, 0.999);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            m6.rotate(1);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            m6.rotate(-1);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                m6.rotateY(-1);
            } else {
                m6.rotateY(1);
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                m6.rotateZ(-1);
            } else {
                m6.rotateZ(1);
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                m6.rotateX(-1);
            } else {
                m6.rotateX(1);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            m6.rotateAroundPoint(rotV, 1);
        }

        window.clear();
        for(auto &view : views) {
            window.setView(view.getView());
            view.draw(window, objects);
            rotV.draw(window, view.getViewType());
        }
        window.display();
    }

    return 0;
}

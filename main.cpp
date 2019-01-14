#include <iostream>
#include <SFML/Graphics.hpp>
#include "src/Vector2D.h"
#include "src/Matrix.h"
#include "src/MyMesh.h"
#include "src/CustomView.h"
#include "src/PulseController.h"
#include "src/vmath.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lineaire dingen", sf::Style::Default, settings);

    auto playerMesh = std::make_unique<MyMesh>("player.obj");
    auto player = GameObject::FromModel(playerMesh->getModel());
    player.setCollisionShape(CollisionShape::SPHERE);
    player.scale(25, 25, 25);

    auto targetMesh = std::make_unique<MyMesh>("target.obj");
    auto target = GameObject::FromModel(targetMesh->getModel());
    target.setColor(sf::Color::Yellow);
    target.scale(25, 25, 25);
    target.setCollisionShape(CollisionShape::SPHERE);

    auto targetPulseController = std::make_unique<PulseController>(target, 30, 40, 0.005);

    window.setKeyRepeatEnabled(false);

    std::vector<CustomView> views;
    ObjectContainer objects;

    objects.emplace_back(&player);
    objects.emplace_back(&target);

    views.emplace_back(top, sf::FloatRect(0.f, 0.f, 0.5f, 0.5f));
    views.emplace_back(side, sf::FloatRect(0.5f, 0.f, 0.5f, 0.5f));
    views.emplace_back(front, sf::FloatRect(0.f, 0.5f, 0.5f, 0.5f));

    auto rotV = Vector3D{10, 8, 6};
    Vector3D zero{ 0, 0, 0 };

    player.print();
    Vector3D pointToShootFrom{};

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
            player.translate(-1, 0, 0);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            player.translate(1, 0, 0);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            player.translate(0, -1, 0);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            player.translate(0, 1, 0);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            player.scale(1.001, 1.001, 1.001);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            player.scale(0.999, 0.999, 0.999);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            player.rotate(1);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            player.rotate(-1);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                player.rotateY(-1);
            } else {
                player.rotateY(1);
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                player.rotateZ(-1);
            } else {
                player.rotateZ(1);
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                player.rotateX(-1);
            } else {
                player.rotateX(1);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            player.rotateAroundPoint(rotV, 1);
        }
			
        targetPulseController->act();

//        pointToShootFrom = getMiddle(player.get(5), player.get(0));
        pointToShootFrom = player.get(4);
        auto shootDirection = player.get(6).crossProduct(player.get(5));
        shootDirection.normalize();
        shootDirection * 100;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {

        }

        auto end = pointToShootFrom += shootDirection;

        window.clear();
        for(auto &view : views) {
            window.setView(view.getView());
            view.draw(window, objects);
            shootDirection.draw(window, view.getViewType());
            pointToShootFrom.draw(window, view.getViewType());
            pointToShootFrom.draw(window, view.getViewType(), end);
            end.draw(window, view.getViewType());
        }
        window.display();
    }

    return 0;
}

#include "CustomView.h"
#include "Matrix.h"

CustomView::CustomView(const ViewType viewType, const sf::FloatRect rect) : viewType(viewType), view(std::make_unique<sf::View>(sf::Vector2f(0, 0), sf::Vector2f(800.f, 600.f)))
{
    view->setViewport(rect);
}

void CustomView::draw(const sf::RenderWindow &window, ObjectContainer &objects)
{
    for (auto object : objects) {
        object->draw(const_cast<sf::RenderWindow &>(window), viewType);
    }
}
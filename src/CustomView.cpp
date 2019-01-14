#include "CustomView.h"
#include "Matrix.h"

CustomView::CustomView(const ViewType viewType, const sf::FloatRect rect) : viewType(viewType), view(std::make_unique<sf::View>(sf::Vector2f(0, 0), sf::Vector2f(800.f, 600.f)))
{
    view->setViewport(rect);
}

void CustomView::draw(sf::RenderWindow &window, ObjectContainer &objects)
{
    for (auto& object : objects) {
        object->draw(window, viewType);
    }
}


void CustomView::drawText(sf::RenderWindow & window, sf::Text text)
{
    window.draw(text);
}
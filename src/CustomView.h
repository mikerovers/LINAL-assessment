#ifndef LINAL_ASSESSMENT_CUSTOMVIEW_H
#define LINAL_ASSESSMENT_CUSTOMVIEW_H

#include <SFML/Graphics.hpp>

class Matrix;

enum ViewType {
    perspective,
    front,
    side,
    top
};

typedef std::vector<Matrix*> ObjectContainer;
extern ViewType ViewTypeE;

class CustomView
{
public:
    CustomView(ViewType viewType, sf::FloatRect rect);
    sf::View& getView() { return *view; }

    void draw(const sf::RenderWindow &window, ObjectContainer &objects);
private:
    ViewType viewType;
    std::unique_ptr<sf::View> view;
};


#endif //LINAL_ASSESSMENT_CUSTOMVIEW_H

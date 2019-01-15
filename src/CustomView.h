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

typedef Matrix GameObject;
typedef std::vector<std::shared_ptr<Matrix>> ObjectContainer;;

class CustomView
{
public:
    CustomView(ViewType viewType, sf::FloatRect rect);
    sf::View& getView() { return *view; }
    const ViewType getViewType() const { return viewType; }

    void draw(sf::RenderWindow &window, ObjectContainer &objects);
    void drawText(sf::RenderWindow &window, sf::Text text);
private:
    ViewType viewType;
    std::unique_ptr<sf::View> view;
};


#endif //LINAL_ASSESSMENT_CUSTOMVIEW_H
#pragma once
#include "src/Vector2D.h"
#include "src/Matrix.h"
#include "src/MyMesh.h"
#include "src/CustomView.h"
#include "src/PulseController.h"
#include "Player.h"
#include "Target.h"

class Game
{
public:
	void start();
	Player& createPlayer();
	Target& createTarget();
	void createViews();
	void reDraw();

private:     
	bool running = true;
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<sf::Text> text;
	ObjectContainer objects;
	std::vector<CustomView> views;
};


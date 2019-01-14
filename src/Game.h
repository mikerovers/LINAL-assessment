#pragma once
#include "Vector2D.h"
#include "Matrix.h"
#include "MyMesh.h"
#include "CustomView.h"
#include "PulseController.h"
#include "Player.h"
#include "Target.h"

class Game
{
public:
	Game();
	~Game();
	void start();
	void createPlayer();
	void createTarget();
	void createViews();
	void reDraw();
	void update();

private:
	bool running = true;
	std::shared_ptr<Player> player;
	std::shared_ptr<Target> target;
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<sf::Text> text;
	ObjectContainer objects;
	std::vector<CustomView> views;
	Vector3D pointToShootFrom{};
	Vector3D shootDirection{};
	std::unique_ptr<PulseController> targetPulseController;
};
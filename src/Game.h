#pragma once
#include "Vector2D.h"
#include "Matrix.h"
#include "MyMesh.h"
#include "CustomView.h"
#include "PulseController.h"
#include "Player.h"
#include "Target.h"
#include "Bullet.h"

class Game
{
public:
	Game();
	~Game();
	void start();
	void createPlayer();
	void createTarget();
	void createBullet();
	void createViews();
	void reDraw();
	void update();

private:
	bool running = true;
	bool drawHelp = true;
	std::shared_ptr<Player> player;
	std::shared_ptr<Target> target;
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<sf::Text> text;
	ObjectContainer objects;
	std::vector<std::shared_ptr<Bullet>> bullets;
	std::vector<CustomView> views;
	Vector3D pointToShootFrom{};
	Vector3D shootDirection{};
    Vector3D playerPositionBackup{};
	std::unique_ptr<PulseController> targetPulseController;

	std::unique_ptr<MyMesh> bulletMesh;
	std::unique_ptr<MyMesh> playerMesh;
	std::unique_ptr<MyMesh> targetMesh;
};
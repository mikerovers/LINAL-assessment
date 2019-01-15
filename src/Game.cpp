#include "Game.h"
#include "vmath.h"
#include "Bullet.h"

Game::Game()
{
	bulletMesh = std::make_unique<MyMesh>("round.obj");
	playerMesh = std::make_unique<MyMesh>("player.obj");
	targetMesh = std::make_unique<MyMesh>("target.obj");
}

void Game::start()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 0;
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "Lineaire dingen", sf::Style::Default, settings);
	window->setKeyRepeatEnabled(false);
	createPlayer();
	createTarget();
	targetPulseController = std::make_unique<PulseController>(*target, 30, 40, 0.005);

	createViews();


	sf::Font font;
	if (!font.loadFromFile("ARIALI.TTF"))
	{
		std::cout << "Can't load font" << std::endl;
		// error...
	}

	sf::Event event;
	text = std::make_shared<sf::Text>();
	text->setFont(font);
	text->setPosition(-150, -250);
	text->setCharacterSize(24);

	bool lost = false;
	bool win = false;
	auto rotV = Vector3D{ 10, 8, 6 };
	while (running && window->isOpen()) {
		while (window->pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window->close();
				break;
			default:
				break;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			if (lost) {
				window->close();
			}
		}
		if (!lost && !win) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				player->increaseSpeed();
				player->setHeading(shootDirection);
			}
			else {
				if (player->getSpeed() >= 1) {
					player->decreaseSpeed();
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				player->translate(0, -1, 0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				player->translate(0, 1, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				player->rotateY(5);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				player->rotateY(-5);
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				player->rotate(1);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
				player->rotate(-1);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
			{
				player->scale(1.001, 1.001, 1.001);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
			{
				player->scale(0.999, 0.999, 0.999);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				player->rotate(1);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
				player->rotate(-1);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
					player->rotateY(-1);
				}
				else {
					player->rotateY(1);
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
					player->rotateZ(-1);
				}
				else {
					player->rotateZ(1);
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
					player->rotateX(-1);
				}
				else {
					player->rotateX(1);
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
				player->rotateAroundPoint(rotV, 1);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
				if (player->getShootTimer() == 0) {
					player->setShootTimer(75);
					createBullet();
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
				drawHelp = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
				drawHelp = false;
			}

			if (player->intersect(*target)) {
				lost = true;
				objects.erase(objects.begin() + 0);
			}

			for (auto const &bullet : bullets) {
				if (bullet->intersect(*target)) {
					win = true;
					objects.erase(std::find(objects.begin(), objects.end(), target));
					break;
				}
			}
		}
		else { // The player has lost
			text->setString("You have collided with an object and lost");
			text->setFillColor(sf::Color::Red);
		}

		if (win) {
			text->setString("You have destroyed all asteroids and won the game!");
			text->setFillColor(sf::Color::Green);
		}

		update();
		reDraw();
	}
}

void Game::createPlayer()
{
	player = std::make_shared<Player>(GameObject::FromModel(playerMesh->getModel()));
	player->setColor(sf::Color::Red);
	player->scale(25, 25, 25);
	player->setCollisionShape(CollisionShape::RECTANGLE);

	objects.emplace_back(player);
}

void Game::createTarget()
{
	target = std::make_shared<Target>(GameObject::FromModel(targetMesh->getModel()));
	target->setColor(sf::Color::Yellow);
	target->scale(25, 25, 25);
	target->translate(-150, 0, -0);
	target->setCollisionShape(CollisionShape::SPHERE);
	objects.emplace_back(target);
}

void Game::createViews()
{
	views.emplace_back(top, sf::FloatRect(0.f, 0.f, 0.5f, 0.5f));
	views.emplace_back(side, sf::FloatRect(0.5f, 0.f, 0.5f, 0.5f));
	views.emplace_back(front, sf::FloatRect(0.f, 0.5f, 0.5f, 0.5f));
}

void Game::reDraw()
{
	window->clear();
	for (auto &view : views) {
		window->setView(view.getView());
		view.draw(*window, objects);
		for (auto &bullet : bullets) {
			bullet->draw(*window, view.getViewType());
		}
		view.drawText(*window, *text);
		if (drawHelp) {
			auto shootDirectionDraw = shootDirection;
			shootDirectionDraw.setX(shootDirectionDraw.getX() + playerPositionBackup.getX());
			shootDirectionDraw.setY(shootDirectionDraw.getY() + playerPositionBackup.getY());
			shootDirectionDraw.setZ(shootDirectionDraw.getZ() + playerPositionBackup.getZ());
			shootDirectionDraw.draw(*window, view.getViewType());
			pointToShootFrom.draw(*window, view.getViewType());
			pointToShootFrom.draw(*window, view.getViewType(), shootDirectionDraw);
		}
	}

	window->display();
}

void Game::update()
{
	playerPositionBackup = player->getOrigin();
	auto invertedPlayerPositionBackup = playerPositionBackup *= -1;
	player->translate(invertedPlayerPositionBackup.getX(), invertedPlayerPositionBackup.getY(), invertedPlayerPositionBackup.getZ());

	pointToShootFrom = player->get(8);

	shootDirection = player->get(0);
	shootDirection.mirror(pointToShootFrom);

	for (auto &object : objects) {
		object->act();
	}
	for (auto &bullet : bullets) {
		bullet->act();
	}
	for (auto &bullet : bullets) {
		if (bullet != nullptr) {
			if (bullet->getLifetime() <= 0) {
				bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet));
			}
		}
	}

	player->translate(playerPositionBackup.getX(), playerPositionBackup.getY(), playerPositionBackup.getZ());
	pointToShootFrom.setX(pointToShootFrom.getX() + playerPositionBackup.getX());
	pointToShootFrom.setY(pointToShootFrom.getY() + playerPositionBackup.getY());
	pointToShootFrom.setZ(pointToShootFrom.getZ() + playerPositionBackup.getZ());

	targetPulseController->act();
}

void Game::createBullet()
{
	auto bullet = std::make_shared<Bullet>(GameObject::FromModel(bulletMesh->getModel()));
	bullet->scale(7, 7, 7);
	bullet->setLifetime(250);
	bullet->setDirection(shootDirection.normalize() * 6);
	bullet->setColor(sf::Color::Green);
	bullet->translate(pointToShootFrom.getX(), pointToShootFrom.getY(), pointToShootFrom.getZ());
	bullet->setCollisionShape(CollisionShape::SPHERE);
	bullet->setSpeedVector(player->getSpeedVector());
	bullet->setSpeedBoost(player->getSpeed() != 0);
	bullets.emplace_back(bullet);
}

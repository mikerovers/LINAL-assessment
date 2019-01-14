#include "Game.h"

void Game::start()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 0;
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "Lineaire dingen", sf::Style::Default, settings);

	auto& player = createPlayer();
	auto& target = createTarget();

	createViews();
	
	
	sf::Font font;
	if (!font.loadFromFile("ARIALI.TTF"))
	{
		std::cout << "Can't load font" << std::endl;
		// error...
	}

	sf::Event event;
	text = std::make_shared<sf::Text>();
	//sf::Text text;
	bool lost = false;
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
		if (!lost) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				player.translate(-1, 0, 0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				player.translate(1, 0, 0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				player.translate(0, -1, 0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				player.translate(0, 1, 0);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				player.scale(1.001, 1.001, 1.001);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				player.scale(0.999, 0.999, 0.999);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				player.rotate(1);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
				player.rotate(-1);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
					player.rotateY(-1);
				}
				else {
					player.rotateY(1);
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
					player.rotateZ(-1);
				}
				else {
					player.rotateZ(1);
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
					player.rotateX(-1);
				}
				else {
					player.rotateX(1);
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
				player.rotateAroundPoint(rotV, 1);
			}


			if (player.intersect(target)) {
				lost = true;
				objects.erase(objects.begin() + 0);
			}
		}
		else { // The player has lost
			text->setFont(font);
			text->setString("You have collided with an object and lost");
			text->setPosition(-150, -250);
			text->setCharacterSize(24);
			text->setFillColor(sf::Color::Red);
		}
		Game::reDraw();
	}

}

Player& Game::createPlayer()
{
	auto playerMesh = std::make_unique<MyMesh>("player.obj");
	auto player = std::make_shared<Player>(GameObject::FromModel(playerMesh->getModel()));
	player->setColor(sf::Color::Green);
	player->scale(25, 25, 25);
	player->setCollisionShape(CollisionShape::SPHERE);
	player->translate(-150, 0, 0);

	objects.emplace_back(player);

	return *player;
}

Target& Game::createTarget()
{
	auto targetMesh = std::make_unique<MyMesh>("target.obj");
	auto target = std::make_shared<Target>(GameObject::FromModel(targetMesh->getModel()));
	target->setColor(sf::Color::Yellow);
	target->scale(25, 25, 25);
	target->setCollisionShape(CollisionShape::SPHERE);
	objects.emplace_back(target);
	return *target;
}

void Game::createViews()
{
	views.emplace_back(top, sf::FloatRect(0.f, 0.f, 0.5f, 0.5f));
	views.emplace_back(side, sf::FloatRect(0.5f, 0.f, 0.5f, 0.5f));
	views.emplace_back(front, sf::FloatRect(0.f, 0.5f, 0.5f, 0.5f));
}

void Game::reDraw()
{
	auto rotV = Vector3D{ 10, 8, 6 };
	window->clear();
	for (auto &view : views) {
		window->setView(view.getView());
		view.draw(*window, objects);
		view.drawText(*window, *text);
		rotV.draw(*window, view.getViewType());
	}

	window->display();
}
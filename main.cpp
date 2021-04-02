#include <iostream>
#include <SFML/Graphics.hpp>
#include "World.h"
#include "Player.h"
#include "InputManager.h"
#include <sstream>
#include <chrono>
#include <thread>
#include "Blocks/BlockEntity.h"
#include <cstdio>

int main()
{
	sf::ContextSettings settings;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "THE HERO", 7, settings);
	window.setVerticalSyncEnabled(true);
	World world;

	sf::Texture sky_texture;
	sky_texture.loadFromFile("Assets/background.png");
	
	Player* player = world.spawn<Player>({ 15.f, -32.f});
	Entity* sky = world.spawn<Entity>({}, sky_texture);
	sky->set_collision_enabled(false);

	sf::Texture dirt_texture;
	sf::Texture grass_texture;
	dirt_texture.loadFromFile("Assets/dirt.png");
	grass_texture.loadFromFile("Assets/grass.png");

	srand(2201);

	for (int y = 0; y < 16; ++y)
	{
		for (int x = -512 / 2; x < 512; ++x)
		{
			int r = rand() % 2;
			if (r < 20)
				continue;

			if(y == 0)
				world.spawn<BlockEntity>(sf::Vector2f(x * 32, y * 32), grass_texture);
			else
				world.spawn<BlockEntity>(sf::Vector2f(x * 32, y * 32), dirt_texture);
		}
	}

	sf::Font font;
	font.loadFromFile("Assets/Roboto-Regular.ttf");
	sf::Text debug_text("coucou", font);
	debug_text.setFillColor(sf::Color::Black);

	sf::View view(window.getDefaultView());
	view.zoom(0.85f);

	auto previous = std::chrono::high_resolution_clock::now();
	while (window.isOpen())
	{
		auto current = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> delta_time_as_duration = current - previous;
		previous = current;

		float delta_time = 0.001f * static_cast<float>(delta_time_as_duration.count());

		input::update();
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				input::on_key_pressed(event);
				break;
			case sf::Event::KeyReleased:
				input::on_key_released(event);
				break;
			}
		}

		world.update(delta_time);
		sky->set_position(player->get_position() - 
			sf::Vector2f((sky_texture.getSize().x / 2) + player->get_position().x / 16, 
			(sky_texture.getSize().y / 2) + player->get_position().y / 8));

		std::stringstream ss;
		ss << "FPS: " << 1.f / delta_time << "\n";
		ss << "Pos: " << player->get_position().x << ", " << player->get_position().y << "\n";
		ss << "Vel: " << player->get_velocity().x << ", " << player->get_velocity().y << "\n";
		debug_text.setString(ss.str());

		window.clear();
		view.setCenter(player->get_position());
		window.setView(view);
		world.draw(window);
		window.setView(window.getDefaultView());
		window.draw(debug_text);
		window.display();
	}
}
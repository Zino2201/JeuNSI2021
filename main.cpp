#include <iostream>
#include <SFML/Graphics.hpp>
#include "World.h"
#include "Player.h"
#include "InputManager.h"
#include <sstream>
#include <chrono>
#include <thread>

int main()
{
	sf::ContextSettings settings;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "THE HERO", 7, settings);
	window.setVerticalSyncEnabled(true);
	World world;

	sf::Texture sky_texture;
	sky_texture.loadFromFile("Assets/background.png");
	
	Player* player = world.spawn<Player>({});
	Entity* sky = world.spawn<Entity>({}, sky_texture);
	sky->set_collision_enabled(false);
	
	Entity* ground = world.spawn<Entity>({ 0.f, 500.f }, sky_texture);
	ground->get_sprite().setColor(sf::Color::Red);
	ground->set_scale({ 1.f, .3f });

	sf::Font font;
	font.loadFromFile("Assets/Roboto-Regular.ttf");
	sf::Text debug_text("coucou", font);
	debug_text.setFillColor(sf::Color::Black);

	sf::View view(window.getDefaultView());

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

		std::stringstream ss;
		ss << "FPS: " << 1.f / delta_time << "\n";
		ss << "Pos: " << player->get_position().x << ", " << player->get_position().y << "\n";
		ss << "Vel: " << player->get_velocity().x << ", " << player->get_velocity().y << "\n";
		debug_text.setString(ss.str());

		window.clear(sf::Color::Red);
		view.setCenter(player->get_position());
		window.setView(view);
		world.draw(window);
		window.setView(window.getDefaultView());
		window.draw(debug_text);
		window.display();
	}
}
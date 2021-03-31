#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Player
{
public:
	Player();
	void update(float delta_time);
	void draw(sf::RenderWindow& window);
private:
	sf::Texture texture;
	sf::Sprite sprite;
};
#include "Player.h"
#include <SFML/Graphics/Texture.hpp>
#include "InputManager.h"

Player::Player() 
{
	texture.loadFromFile("Assets/player.png");
	sprite = sf::Sprite(texture);
}

const float speed = 200.f;
const float gravity = 50.f;

void Player::update(float delta_time)
{
	if (input::is_key_held(sf::Keyboard::Q))
	{
		sprite.setPosition(sprite.getPosition() + sf::Vector2f(-speed * delta_time, 0));
	}

	if (input::is_key_held(sf::Keyboard::D))
	{
		sprite.setPosition(sprite.getPosition() + sf::Vector2f(speed * delta_time, 0));
	}

	/** Gravité */
	sprite.setPosition(sprite.getPosition() + sf::Vector2f(0, gravity * delta_time));
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
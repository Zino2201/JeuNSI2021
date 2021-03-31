#include "Player.h"
#include <SFML/Graphics/Texture.hpp>
#include "InputManager.h"
#include "World.h"

Player::Player(World& in_world) 
	: PhysicsEntity(in_world, {}, zorder_player)
{
	texture.loadFromFile("Assets/player.png");
	sprite = sf::Sprite(texture);
}

const float speed = 200.f;

bool nearly_equals(float a, float b, float epsilon = 0.002f)
{
	return std::abs(a - b) < epsilon;
}

void Player::update(float delta_time)
{
	if (input::is_key_held(sf::Keyboard::Q))
	{
		move_immediate(sf::Vector2f(-speed * delta_time, 0));
	}

	if (input::is_key_held(sf::Keyboard::D))
	{
		move_immediate(sf::Vector2f(speed * delta_time, 0));
	}

	if(input::is_key_pressed(sf::Keyboard::Space)
		&& nearly_equals(velocity.y, 0.f))
	{
		move(sf::Vector2f(0, -world.get_gravity()));
	}

	PhysicsEntity::update(delta_time);
}
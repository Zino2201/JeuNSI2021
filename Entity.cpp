#include "Entity.h"
#include "World.h"

void Entity::set_position(const sf::Vector2f& in_position)
{
	position = in_position;
	sprite.setPosition(in_position);
}

void Entity::set_scale(const sf::Vector2f& in_scale)
{
	scale = in_scale;
	sprite.setScale(in_scale);
}

void Entity::set_collision_enabled(const bool in_collision_enabled)
{
	collision_enabled = in_collision_enabled;
}

void Entity::draw(sf::RenderWindow& window) 
{
	window.draw(sprite);
}

#include "PhysicsEntity.h"
#include "World.h"

void PhysicsEntity::move(const sf::Vector2f& in_direction)
{
	velocity += in_direction;
}

void PhysicsEntity::move_immediate(const sf::Vector2f& in_direction)
{
	/** On avance le rectangle la ou on veut allez et on vérifie que
	 * on ne collisionne avec rien */
	sf::FloatRect rect = sprite.getGlobalBounds();
	rect.left += in_direction.x;
	rect.top += in_direction.y;
	Entity* entity = world.is_colliding(this, rect);
	if(entity)
	{
		velocity = {};
		return;
	}

	set_position(position + in_direction);
}

void PhysicsEntity::update(float delta_time)
{
	if(velocity.y < world.get_terminal_velocity())
		move(sf::Vector2f(0, world.get_gravity() * delta_time));
	
	/** Si on touche un truc, on annule toute velocité sinon on l'applique à la position de l'entité */
	Entity* entity = world.is_colliding(this, sprite.getGlobalBounds());
	if(entity)
	{
		velocity = {};
	}
	else
	{
		move_immediate(velocity * delta_time);
	}
}
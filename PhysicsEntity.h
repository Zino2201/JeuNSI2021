#pragma once

#include "Entity.h"

/**
 * Entité qui est influencé par la GRAVITE et qui possède une VELOCITE
 * (en gros on peut la déplacer mdr)
 */
class PhysicsEntity : public Entity
{
public:
	using Entity::Entity;

	/**
	 * Déplace l'entité vers la direction donnée en faisant un check de collision
	 */
	void move(const sf::Vector2f& in_direction);
	void move_immediate(const sf::Vector2f& in_direction);

	void update(float delta_time) override;

	inline sf::Vector2f get_velocity() const { return velocity; }
protected:
	sf::Vector2f velocity;
};
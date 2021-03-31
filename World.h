#pragma once

#include "Entity.h"
#include <vector>
#include <memory>

/**
 * le monde lol
 */
class World
{
public:
	World() : gravity(400.f), terminal_velocity(400.f) {}

	template<typename T, typename... Args>
	T* spawn(const sf::Vector2f& in_position, Args&&... in_args)
	{
		T* entity = new T(*this, std::forward<Args>(in_args)...);
		entity->set_position(in_position);
		entities.emplace_back(entity);
		sort_entities_by_zorder();
		return entity;
	}

	void update(float delta_time);
	void draw(sf::RenderWindow& window);

	/**
	 * Vérifie si l'entité donné rentre en collision avec une entité
	 */
	Entity* is_colliding(Entity* self, const sf::FloatRect& in_rect);

	inline float get_gravity() const { return gravity; }
	inline float get_terminal_velocity() const { return terminal_velocity; }
private:
	void sort_entities_by_zorder();
private:
	std::vector<std::unique_ptr<Entity>> entities;
	float gravity;
	float terminal_velocity;
};
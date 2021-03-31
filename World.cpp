#include "World.h"

void World::sort_entities_by_zorder()
{
	std::sort(entities.begin(), entities.end(),
		[](const auto& left, const auto& right)
		{
			return left->get_zorder() < right->get_zorder();
		});
}

void World::update(float delta_time)
{
	for(const auto& entity : entities)
	{
		entity->update(delta_time);
	}
}

void World::draw(sf::RenderWindow& window)
{
	for(const auto& entity : entities)
	{
		entity->draw(window);
	}
}

Entity* World::is_colliding(Entity* self, const sf::FloatRect& in_rect)
{
	for(const auto& entity : entities)
	{
		/** On s'ignore soi-même */
		if(entity.get() == self || !entity->has_collision_enabled())
			continue;

		if(in_rect.intersects(entity->get_bounding_box()))
			return entity.get();
	}

	return nullptr;
}
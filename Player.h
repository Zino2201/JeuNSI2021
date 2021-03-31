#pragma once

#include <SFML/Graphics.hpp>
#include "PhysicsEntity.h"

class Player final : public PhysicsEntity
{
public:
	Player(World& in_world);
	void update(float delta_time) override;
private:
	sf::Texture texture;
};
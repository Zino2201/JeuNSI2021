#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

static constexpr uint8_t zorder_sky = 0;
static constexpr uint8_t zorder_sprites = 1;
static constexpr uint8_t zorder_npcs = 254;
static constexpr uint8_t zorder_player = 255;

class World;

/**
 * Classe de base pour les objets qui sont dans le monde
 */
class Entity
{
public:
	Entity(World& in_world, const sf::Texture& in_texture = sf::Texture(), const uint8_t in_zorder = 0) : world(in_world), 
		sprite(in_texture), zorder(in_zorder), collision_enabled(true) {}

	virtual void update(float delta_time) {}
	virtual void draw(sf::RenderWindow& window);

	void set_position(const sf::Vector2f& in_position);
	void set_scale(const sf::Vector2f& in_scale);
	void set_collision_enabled(const bool in_collision_enabled);

	inline sf::Vector2f get_position() const { return position; }
	inline sf::Vector2f get_rotation() const { return rotation; }
	inline sf::Vector2f get_scale() const { return scale; }
	inline sf::Sprite& get_sprite() { return sprite; }
	inline uint8_t get_zorder() const { return zorder; }
	inline sf::FloatRect get_bounding_box() const { return sprite.getGlobalBounds(); }
	inline bool has_collision_enabled() { return collision_enabled; } 
protected:
	void update_bounding_box();
protected:
	World& world;
	sf::Vector2f position;
	sf::Vector2f rotation;
	sf::Vector2f scale;
	uint8_t zorder;
	sf::FloatRect bounding_box;
	bool collision_enabled;
	sf::Sprite sprite;
};
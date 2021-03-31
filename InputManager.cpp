#include "InputManager.h"
#include <unordered_map>

namespace input
{

std::unordered_map<sf::Keyboard::Key, bool> pressed_keys;
std::unordered_map<sf::Keyboard::Key, bool> held_keys;
	
void update()
{
	pressed_keys.clear();
}

bool is_key_pressed(const sf::Keyboard::Key& key)
{
	return pressed_keys[key];
}

bool is_key_held(const sf::Keyboard::Key& key)
{
	return held_keys[key];
}

void on_key_pressed(const sf::Event& event)
{
	pressed_keys[event.key.code] = true;
	held_keys[event.key.code] = true;
}

void on_key_released(const sf::Event& event)
{
	held_keys[event.key.code] = false;
}

}
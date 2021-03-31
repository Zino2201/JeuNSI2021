#pragma once

#include <SFML/Graphics.hpp>

namespace input
{

void update();

bool is_key_pressed(const sf::Keyboard::Key& key);
bool is_key_held(const sf::Keyboard::Key& key);

void on_key_pressed(const sf::Event& event);
void on_key_released(const sf::Event& event);

}

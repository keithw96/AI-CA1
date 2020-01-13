#pragma once
#include <SFML/Graphics.hpp>
class Predator
{
public:
	Predator(sf::Vector2f pos, sf::Sprite sprite, sf::Vector2f roomcenter);

	void update(sf::Time deltaTime, sf::Vector2f playerPos);
	void render(sf::RenderWindow *window, sf::Vector2f scale);
private:
	sf::Vector2f m_startPos;
	sf::Vector2f m_position;
	sf::Vector2f m_roomCenter;
	int m_rotation;
	sf::Vector2f m_range;
	int m_velocity;
	sf::Sprite m_sprite;
};


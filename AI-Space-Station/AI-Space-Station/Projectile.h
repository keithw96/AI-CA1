#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Projectile
{
public:
	Projectile(sf::Vector2f position, sf::Sprite sprite, bool homing);
	~Projectile();

	void Update(sf::Time deltaTime, sf::Vector2f playerPos);
	void Render(sf::RenderWindow *window, sf::Vector2f scale);

	void Homing(sf::Vector2f playerPos);
	bool m_alive;
private:
	sf::Vector2f m_position;
	float m_rotation;
	int count;
	float m_velocity;
	bool m_homing;
	sf::Sprite m_sprite;
};


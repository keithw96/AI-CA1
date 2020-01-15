#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#define _USE_MATH_DEFINES

#include <math.h>

#include "Tile.h"
class Projectile
{
public:
	Projectile(sf::Vector2f position, sf::Sprite sprite, bool homing);
	Projectile(sf::Vector2f position, sf::Sprite sprite, float rotation, bool homing);
	~Projectile();

	void update(sf::Time deltaTime, sf::Vector2f playerPos, std::vector<Tile> boundaryTiles);
	void render(sf::RenderWindow *window, sf::Vector2f scale);

	void homing(sf::Vector2f playerPos);
	void notHoming();
	void rotate();
	void boundaryCollision(std::vector<Tile> boundaryTiles);
	bool m_alive;
private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_rotation;
	float m_directionRotation;
	int count;
	float m_speed;
	bool m_homing;
	int fireRate;
	int maxFireRate;
	sf::Sprite m_sprite;
};


#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <list>
#include "Projectile.h"
#include "Predator.h"
#include "Tile.h"

class AlienNest
{
public:
	AlienNest(sf::Vector2f pos, sf::Sprite sprite, sf::Sprite projectileSprite, sf::Sprite predatorSprite);

	void render(sf::RenderWindow *window, sf::Vector2f scale);
	void update(sf::Time deltaTime, sf::Vector2f playerPos, std::vector<Tile> boundaryTiles);
	std::vector<Predator*> getPredators();
	std::vector<Projectile*> getProjectiles();
	sf::Sprite getSprite();

private:
	sf::Vector2f m_position;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Sprite m_projectileSprite;
	sf::Sprite m_predatorSprite;
	std::vector<Projectile*> m_projectiles;
	std::vector<Predator*> m_predators;
};
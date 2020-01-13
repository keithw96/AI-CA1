#pragma once
#include "SFML/Graphics.hpp"

class Tile
{
public:
	Tile(sf::Vector2f position, sf::Sprite sprite, int t);
	Tile() {};
	
	void draw(sf::RenderWindow *window);

	sf::Sprite getSprite();
	int getType();

private:
	sf::Sprite m_sprite; 
	int m_type;

	sf::Vector2f m_position;
	std::vector<Tile*> adjacents;
};
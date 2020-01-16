#pragma once
#include"SFML/Graphics.hpp"
#include<stdlib.h>
#include "Tile.h"
class Worker
{
public:
	Worker();
	~Worker();
	sf::RectangleShape getBody();
	void update();
	void setPos(sf::Vector2f newPos);
	void setVel();
	bool getAlive();
	void checkWallCollision(std::vector<Tile>& tilemap);
	void checkPlayerCollision(sf::Sprite player);

private:
	sf::RectangleShape m_body;//visual representation
	sf::Vector2f m_pos;//position
	sf::Vector2f m_vel;//velocity
	sf::Texture m_texture;
	bool m_alive = true;
};

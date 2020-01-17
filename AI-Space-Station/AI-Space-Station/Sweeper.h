#pragma once
#include"SFML/Graphics.hpp"
#include"Tile.h"
class Sweeper
{
public:
	Sweeper();
	~Sweeper();
	sf::RectangleShape getBody();
	void checkForWorker(sf::Vector2f workerPos);
	void checkForPlayer(sf::Sprite player);
	void checkForWall(std::vector<Tile>& tilemap);
	void move();
	void update();

private:
	sf::RectangleShape m_body;
	sf::Texture m_texture;
	//float m_danger[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	float m_desire[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	sf::Vector2f m_direction[8];
	float speed = 1.0f;
	sf::Vector2f m_vel;
	sf::Vector2f m_pos;
	bool flee = false;
	int numOfWorkers = 0;
};

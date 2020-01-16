#include"Worker.h"
#include<iostream>
Worker::Worker()
{
	float LO = -1.0f;
	float HI = 1.0f;
	float r1 = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
	float r2 = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
	m_vel = sf::Vector2f(r1 , r2);
	if (m_vel.x == 0 && m_vel.y == 0)
	{
		m_vel.x = 0.76;
		m_vel.y = -0.69;
	}
	m_pos = sf::Vector2f(2750, 5000);
	m_texture.loadFromFile("ASSETS/Textures/NPC.png");
	m_body.setTexture(&m_texture);
	m_body.setSize(sf::Vector2f(50, 50));
	m_body.setFillColor(sf::Color::Green);
	m_body.setPosition(m_pos);
}

Worker::~Worker()
{
}

sf::RectangleShape Worker::getBody()
{
	return m_body;
}

void Worker::update()
{
	m_pos += m_vel * 4.0f;
	m_body.setPosition(m_pos);
}

void Worker::setPos(sf::Vector2f newPos)
{
	m_pos = newPos;
}

void Worker::setVel()
{
	float LO = -1.0f;
	float HI = 1.0f;
	float r1 = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - -1.0f)));
	float r2 = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - -1.0f)));
	m_vel = sf::Vector2f(r1, r2);
}

bool Worker::getAlive()
{
	return m_alive;
}

void Worker::checkWallCollision(std::vector<Tile>& tilemap)
{
	for (int i = 0; i < tilemap.size(); i++)
	{
		if (tilemap[i].getType() == 1)
		{
			//
			if (m_body.getGlobalBounds().intersects(tilemap[i].getSprite().getGlobalBounds()))
			{
				setVel();
			}
		}
	}
}

void Worker::checkPlayerCollision(sf::Sprite player)
{
	if (m_body.getGlobalBounds().intersects(player.getGlobalBounds()))
	{
		m_alive = false;
		//this->~Worker();
	}
}

void Worker::checkSweeperCollision(sf::RectangleShape sweeper)
{
	if (m_body.getGlobalBounds().intersects(sweeper.getGlobalBounds()))
	{
		m_alive = false;
		//this->~Worker();
	}
}

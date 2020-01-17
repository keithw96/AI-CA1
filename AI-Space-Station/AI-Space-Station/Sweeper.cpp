#include"Sweeper.h"

Sweeper::Sweeper()
{
	m_direction[0] = sf::Vector2f(0, -3 *speed);
	m_direction[1] = sf::Vector2f(speed, -speed);
	m_direction[2] = sf::Vector2f(speed, 0);
	m_direction[3] = sf::Vector2f(speed, speed);
	m_direction[4] = sf::Vector2f(0, speed);
	m_direction[5] = sf::Vector2f(-speed, speed);
	m_direction[6] = sf::Vector2f(-speed, 0);
	m_direction[7] = sf::Vector2f(-speed, -speed);

	m_vel = m_direction[0];
	m_pos = sf::Vector2f(2750, 5500);

	m_texture.loadFromFile("ASSETS/Textures/sweeper.png");
	m_body.setTexture(&m_texture);
	m_body.setPosition(sf::Vector2f(m_pos));
	m_body.setSize(sf::Vector2f(50, 50));
	m_body.setFillColor(sf::Color::Blue);
}

Sweeper::~Sweeper()
{
}

sf::RectangleShape Sweeper::getBody()
{
	return m_body;
}

void Sweeper::checkForWorker(sf::Vector2f workerPos)
{
	float dist = sqrt(((workerPos.x - m_pos.x) * (workerPos.x - m_pos.x)) + ((workerPos.y - m_pos.y) * (workerPos.y - m_pos.y)));

	if (dist < 300 && !flee)
	{
		sf::Vector2f vectorTowardsWorker = workerPos - m_pos;
		vectorTowardsWorker = vectorTowardsWorker / (sqrt((vectorTowardsWorker.x * vectorTowardsWorker.x) + (vectorTowardsWorker.y * vectorTowardsWorker.y)));
		m_vel = vectorTowardsWorker * 4.0f;
	}
}

void Sweeper::checkForPlayer(sf::Sprite player)
{
	float dist = sqrt(((player.getPosition().x - m_pos.x) * (player.getPosition().x - m_pos.x)) + ((player.getPosition().y - m_pos.y) * (player.getPosition().y - m_pos.y)));

	if (dist < 200)
	{
		sf::Vector2f vecTowardsPlayer = player.getPosition() - m_pos;
		vecTowardsPlayer = vecTowardsPlayer / (sqrt((vecTowardsPlayer.x * vecTowardsPlayer.x) + (vecTowardsPlayer.y * vecTowardsPlayer.y)));
		m_vel = vecTowardsPlayer * -4.0f;
		flee = true;
	}
	else if ( dist > 300)
	{
		flee = false;
	}
}

void Sweeper::checkForWall(std::vector<Tile>& tilemap)
{
	for (int i = 0; i < tilemap.size(); i++)
	{
		if (tilemap[i].getType() == 1)
		{
			//
			if (m_body.getGlobalBounds().intersects(tilemap[i].getSprite().getGlobalBounds()))
			{
				m_vel *= -1.0f;
			}
		}
	}
}

void Sweeper::move()
{
	m_pos += m_vel * speed;
	m_body.setPosition(m_pos);
}

void Sweeper::update()
{
	move();
}

void Sweeper::setPos(sf::Vector2f newPos)
{
	m_pos = newPos;
}

#include "Predator.h"
#include<iostream>

/// <summary>
/// constructor
/// </summary>
/// <param name="pos"></param>
/// <param name="sprite"></param>
/// <param name="roomCenter"></param>
Predator::Predator(sf::Vector2f pos, sf::Sprite sprite, sf::Vector2f roomCenter)
{
	m_startPos = pos;
	m_position = pos;
	m_sprite = sprite;
	m_roomCenter = roomCenter;
	m_rotation = 0;
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2));
}

/// <summary>
/// updates the predators movement and rotation
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="playerPos"></param>
void Predator::update(sf::Time deltaTime, sf::Vector2f playerPos, std::vector<Tile>& tilemap)
{
	
	sf::Vector2f vectorTowardsPlayer = playerPos - m_position;
	vectorTowardsPlayer = vectorTowardsPlayer / (sqrt((vectorTowardsPlayer.x * vectorTowardsPlayer.x) + (vectorTowardsPlayer.y * vectorTowardsPlayer.y)));;
	m_velocity = vectorTowardsPlayer * 6.0f;
	if (moving)
	{
		m_position += m_velocity;
	}
	m_rotation += 5;
	m_sprite.setRotation(m_rotation);
	m_sprite.setPosition(m_position);

	for (int i = 0; i < tilemap.size(); i++)
	{
		if (tilemap[i].getType() == 1)
		{
			//
			if (m_sprite.getGlobalBounds().intersects(tilemap[i].getSprite().getGlobalBounds()))
			{
				m_position -= m_velocity;
			}
		}
	}
}

/// <summary>
/// renders the predator
/// </summary>
/// <param name="window"></param>
/// <param name="scale"></param>
void Predator::render(sf::RenderWindow *window, sf::Vector2f scale)
{
	m_sprite.setScale(scale);
	window->draw(m_sprite);
}

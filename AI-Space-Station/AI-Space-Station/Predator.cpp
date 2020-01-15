#include "Predator.h"

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
	m_velocity = 3;
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
void Predator::update(sf::Time deltaTime, sf::Vector2f playerPos)
{
	if (m_roomCenter.x - playerPos.x < 400 && m_roomCenter.x - playerPos.x > -400 && m_roomCenter.y - playerPos.y < 400 && m_roomCenter.y - playerPos.y > -400)
	{
		if (m_position.x < playerPos.x)
		{
			m_position.x += m_velocity;
		}

		if (m_position.x > playerPos.x)
		{
			m_position.x -= m_velocity; 
		}

		if (m_position.y > playerPos.y)
		{
			m_position.y -= m_velocity;
		}

		if (m_position.y < playerPos.y)
		{
			m_position.y += m_velocity;
		}
	}

	else
	{
		if (m_position.x < m_startPos.x)
		{
			m_position.x += m_velocity;
		}

		if (m_position.x > m_startPos.x)
		{
			m_position.x -= m_velocity;
		}

		if (m_position.y > m_startPos.y)
		{
			m_position.y -= m_velocity;
		}

		if (m_position.y < m_startPos.y)
		{
			m_position.y += m_velocity;
		}
	}
	m_rotation += 5;
	m_sprite.setRotation(m_rotation);

	m_sprite.setPosition(m_position);
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

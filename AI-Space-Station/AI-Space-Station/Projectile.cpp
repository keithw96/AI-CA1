#include "Projectile.h"

/// <summary>
/// constructor
/// </summary>
/// <param name="pos"></param>
/// <param name="sprite"></param>
/// <param name="homing"></param>
Projectile::Projectile(sf::Vector2f pos, sf::Sprite sprite, bool homing)
{
	m_position = pos;
	m_sprite = sprite;
	m_velocity = 5.0f;
	m_homing = homing;
	count = 0;
	m_alive = true;
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2));
}

/// <summary>
/// deconstructor
/// </summary>
Projectile::~Projectile()
{

}

/// <summary>
/// updates the portjectile depending on what type of projectile it is
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="playerPos"></param>
void Projectile::Update(sf::Time deltaTime, sf::Vector2f playerPos)
{
	if (m_homing && m_alive)
	{
		count++;
		Homing(playerPos);

		if (count >= 200)
		{
			m_alive = false;
		}
	}
	
	
}

/// <summary>
/// renders the projectile if it is alive
/// </summary>
/// <param name="window"></param>
/// <param name="scale"></param>
void Projectile::Render(sf::RenderWindow *window, sf::Vector2f scale)
{
	if (m_alive)
	{
		window->draw(m_sprite);
	}
}

/// <summary>
/// homes the projectile in on the players current position
/// </summary>
/// <param name="playerPos"></param>
void Projectile::Homing(sf::Vector2f playerPos)
{
	if (m_position.x < playerPos.x)
	{
		m_position.x += m_velocity;
	}

	if (m_position.x > playerPos.x)
	{
		m_position.x -= m_velocity;
	}

	if (m_position.y < playerPos.y)
	{
		m_position.y += m_velocity;
	}

	if (m_position.y > playerPos.y)
	{
		m_position.y -= m_velocity;
	}

	m_sprite.setPosition(m_position);
}
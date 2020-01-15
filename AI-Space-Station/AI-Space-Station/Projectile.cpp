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
	m_speed = 4.0f;
	m_homing = homing;
	count = 0;
	m_alive = true;
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2));
}

/// <summary>
/// Second constructor for bullets fired by the player
/// </summary>
/// <param name="position"></param>
/// <param name="sprite"></param>
/// <param name="rotation"></param>
/// <param name="homing"></param>
Projectile::Projectile(sf::Vector2f position, sf::Sprite sprite, float rotation, bool homing)
{
	m_position = position;
	m_sprite = sprite;
	m_speed = 10.0f;
	m_directionRotation = rotation;
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
void Projectile::update(sf::Time deltaTime, sf::Vector2f playerPos, std::vector<Tile> boundaryTiles)
{
	if (m_homing && m_alive)
	{
		count++;
		homing(playerPos);
		boundaryCollision(boundaryTiles);
		if (count >= 200)
		{
			m_alive = false;
		}
		
	}
	else if (m_alive)
	{
		count++;
		notHoming();
		boundaryCollision(boundaryTiles);
		if (count >= 200)
		{
			m_alive = false;
		}
		std::cout << m_sprite.getPosition().x << ", " << m_sprite.getPosition().y << std::endl;
	}
	rotate();
}

/// <summary>
/// renders the projectile if it is alive
/// </summary>
/// <param name="window"></param>
/// <param name="scale"></param>
void Projectile::render(sf::RenderWindow *window, sf::Vector2f scale)
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
void Projectile::homing(sf::Vector2f playerPos)
{
	if (m_position.x < playerPos.x)
	{
		m_position.x += m_speed;
	}

	if (m_position.x > playerPos.x)
	{
		m_position.x -= m_speed;
	}

	if (m_position.y < playerPos.y)
	{
		m_position.y += m_speed;
	}

	if (m_position.y > playerPos.y)
	{
		m_position.y -= m_speed;
	}

	m_sprite.setPosition(m_position);
}

/// <summary>
/// Player fired bullet
/// </summary>
void Projectile::notHoming()
{
	m_velocity.x = cos((M_PI / 180) * m_directionRotation) * m_speed;
	m_velocity.y = sin((M_PI / 180) * m_directionRotation) * m_speed;

	m_position += m_velocity;
	m_sprite.setPosition(m_position);
}

/// <summary>
/// Rotates the projectile
/// </summary>
void Projectile::rotate()
{
	m_rotation += 25;

	if (m_rotation > 360)
	{
		m_rotation = 0;
	}

	m_sprite.setRotation(m_rotation);
}

/// <summary>
/// Detects if the bullet sprite intersects the boundary tiles 
/// sets the alive boolean to false
/// </summary>
/// <param name="boundaryTiles"></param>
void Projectile::boundaryCollision(std::vector<Tile> boundaryTiles)
{
	for (auto t : boundaryTiles)
	{
		if (m_sprite.getGlobalBounds().intersects(t.getSprite().getGlobalBounds()))
		{
			m_alive = false;
		}
	}
}

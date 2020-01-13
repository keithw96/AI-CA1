#include "Tile.h"

/// <summary>
/// constructor
/// </summary>
/// <param name="position"></param>
/// <param name="sprite"></param>
/// <param name="t"></param>
Tile::Tile(sf::Vector2f position, sf::Sprite sprite, int t)
{
	m_sprite = sprite;
	m_position = position;
	m_type = t;
	m_sprite.setScale(sf::Vector2f(2, 2));

	m_sprite.setPosition(m_position.x * m_sprite.getTextureRect().width * m_sprite.getScale().x, m_position.y * m_sprite.getTextureRect().height * m_sprite.getScale().y);
}

/// <summary>
/// rensers the tile
/// </summary>
/// <param name="window"></param>
void Tile::draw(sf::RenderWindow *window) 
{
	window->draw(m_sprite);
}

/// <summary>
/// returns the sprite of the tile
/// </summary>
/// <returns></returns>
sf::Sprite Tile::getSprite()
{
	return m_sprite;
}

/// <summary>
/// returns the type of the tile
/// </summary>
/// <returns></returns>
int Tile::getType()
{
	return m_type;
}
#include "AlienNest.h"

/// <summary>
/// alien nest constructor
/// takes in a starting position, sprite, sprite for its projectiles and a sprite for its predators
/// </summary>
/// <param name="pos"></param>
/// <param name="sprite"></param>
/// <param name="projectileSprite"></param>
/// <param name="predatorSprite"></param>
AlienNest::AlienNest(sf::Vector2f pos, sf::Sprite sprite, sf::Sprite projectileSprite, sf::Sprite predatorSprite)
{
	init(pos, sprite, projectileSprite, predatorSprite);
}

/// <summary>
/// Alien Nest Update:
/// updates the nests variables and the variables of its projectiles
/// and predators
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="playerPos"></param>
void AlienNest::update(sf::Time deltaTime, sf::Vector2f playerPos, std::vector<Tile> boundaryTiles)
{
	if (m_position.x - playerPos.x < 300 && m_position.x - playerPos.x > -300 && m_position.y - playerPos.y < 300 && m_position.y - playerPos.y > -300 && m_projectiles.size() < 1)
	{
		Projectile * bullet = new Projectile(m_position, m_projectileSprite, true);
		m_projectiles.push_back(bullet);
	}

	for (int i = 0; i < m_projectiles.size(); i++)
	{
		m_projectiles[i]->update(deltaTime, playerPos, boundaryTiles);

		if (m_projectiles[i]->m_alive == false)
		{
			m_projectiles[i]->~Projectile();
			m_projectiles[i] = nullptr;
			m_projectiles.erase(m_projectiles.begin() + i);
			i--;
		}
	}

	for (auto& pred : m_predators)
	{
		pred->update(deltaTime, playerPos, boundaryTiles);
	}
}

void AlienNest::init(sf::Vector2f pos, sf::Sprite sprite, sf::Sprite projectileSprite, sf::Sprite predatorSprite)
{
	m_position = pos;
	m_projectileSprite = projectileSprite;
	m_sprite = sprite;
	m_predatorSprite = predatorSprite;

	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2));

	Predator* pred1 = new Predator(sf::Vector2f(m_position.x + m_sprite.getTextureRect().width, m_position.y), predatorSprite, m_position);
	Predator* pred2 = new Predator(sf::Vector2f(m_position.x - m_sprite.getTextureRect().width, m_position.y), predatorSprite, m_position);

	m_predators.push_back(pred1);
	m_predators.push_back(pred2);
}

/// <summary>
/// Returns the array of predators that are children of the nest
/// </summary>
/// <returns></returns>
std::vector<Predator*> AlienNest::getPredators()
{
	return m_predators;
}

/// <summary>
/// returns the array of projectiles that are childeren of the nest
/// </summary>
/// <returns></returns>
std::vector<Projectile*> AlienNest::getProjectiles()
{
	return m_projectiles;
}

/// <summary>
/// Returns the nests sprite
/// </summary>
/// <returns></returns>
sf::Sprite AlienNest::getSprite()
{
	return m_sprite;
}

/// <summary>
/// Renders the nest and its predators 
/// and projectiles 
/// </summary>
/// <param name="window"></param>
/// <param name="scale"></param>
void AlienNest::render(sf::RenderWindow *window, sf::Vector2f scale)
{
	m_sprite.setScale(scale);
	window->draw(m_sprite);
	for (auto& p : m_projectiles)
	{
		p->render(window, scale);
	}

	for (auto& pred : m_predators)
	{
		pred->render(window, scale);
	}
}
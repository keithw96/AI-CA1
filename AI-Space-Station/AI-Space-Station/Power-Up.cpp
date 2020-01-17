#include "Power-Up.h"

/// <summary>
/// constructor
/// </summary>
PowerUp::PowerUp()
{
	init();
}

/// <summary>
/// deconstructor
/// </summary>
PowerUp::~PowerUp()
{

}

/// <summary>
/// intialises the power ups variables
/// </summary>
void PowerUp::init()
{
	loadTextures();
	setPowerUpSpawns();
	int random = rand() % 16;
	m_position = m_spawnpositions[random];
	m_texture = m_textureTypeOne;
	m_lifeTime = 700;
	m_respawnTime = 0;
	m_type = 1;
	m_active = true;
}

/// <summary>
/// loads the power ups texture depending on what power up it is
/// </summary>
void PowerUp::loadTextures()
{
	if (!m_textureTypeOne.loadFromFile("ASSETS/Textures/Invincibility.png"))
	{
		std::cout << "Error! Unable to load License.png from game files!" << std::endl;
	}

	if (!m_textureTypeTwo.loadFromFile("ASSETS/Textures/HealthPack.png"))
	{
		std::cout << "Error! Unable to load License.png from game files!" << std::endl;
	}
}

/// <summary>
/// updates the powers lifetime timer
/// </summary>
/// <param name="deltaTime"></param>
void PowerUp::update(sf::Time deltaTime)
{
	respawn();

	if (m_active == true)
	{
		m_lifeTime--;
	}

	if (m_lifeTime <= 0)
	{
		m_active = false;
	}
}

/// <summary>
/// handles the respawn timer for the power up
/// </summary>
void PowerUp::respawn()
{
	if (m_active == false)
	{
		m_respawnTime++;
	}

	if (m_respawnTime >= 40 && m_active == false)
	{

		int random = rand() % 16;
		m_position = m_spawnpositions[random];
		m_type = rand() % 20 + 1;
		

		if (m_type >= 1 && m_type <= 10)
		{
			m_texture = m_textureTypeOne;
		}

		if (m_type >= 11 && m_type <= 20)
		{
			m_texture = m_textureTypeTwo;
		}

		m_lifeTime = 700;
		m_respawnTime = 0;
		m_active = true;
	}

	m_sprite.setPosition(m_position);
	m_sprite.setTexture(m_texture);
}

/// <summary>
/// renders the powerup if it is active
/// </summary>
/// <param name="window"></param>
void PowerUp::render(sf::RenderWindow& window, sf::Vector2f scale)
{
	m_sprite.setScale(scale);
	if (m_active == true)
	{
		window.draw(m_sprite);
	}
}

/// <summary>
/// returns the type of the powerup
/// </summary>
/// <returns></returns>
int PowerUp::getType()
{
	return m_type;
}

/// <summary>
/// returns the powerups sprite
/// </summary>
/// <returns></returns>
sf::Sprite PowerUp::getSprite()
{
	return m_sprite;
}

/// <summary>
/// sets the powerup to active
/// </summary>
/// <param name="active"></param>
void PowerUp::setActive(bool active)
{
	m_active = active;
}

/// <summary>
/// gets the avtive bool of the power up
/// </summary>
/// <returns></returns>
bool PowerUp::getActive()
{
	return m_active;
}

/// <summary>
/// sets the position of the powerup
/// </summary>
/// <param name="position"></param>
void PowerUp::setPosition(sf::Vector2f position)
{
	m_position = position;
}

/// <summary>
/// returns the position of the powerup
/// </summary>
/// <returns></returns>
sf::Vector2f PowerUp::getPosition()
{
	return m_position;
}

void PowerUp::setPowerUpSpawns()
{
	m_spawnpositions.push_back(sf::Vector2f(750, 3300));
	m_spawnpositions.push_back(sf::Vector2f(750, 3635));
	m_spawnpositions.push_back(sf::Vector2f(1335, 3300));
	m_spawnpositions.push_back(sf::Vector2f(1335, 3635));
	m_spawnpositions.push_back(sf::Vector2f(2410, 5475));
	m_spawnpositions.push_back(sf::Vector2f(2410, 4918));
	m_spawnpositions.push_back(sf::Vector2f(3047, 5475));
	m_spawnpositions.push_back(sf::Vector2f(3047, 4918));
	m_spawnpositions.push_back(sf::Vector2f(3805, 3816));
	m_spawnpositions.push_back(sf::Vector2f(3805, 3282));
	m_spawnpositions.push_back(sf::Vector2f(4735, 3816));
	m_spawnpositions.push_back(sf::Vector2f(4735, 3282));
	m_spawnpositions.push_back(sf::Vector2f(560, 1283));
	m_spawnpositions.push_back(sf::Vector2f(560, 1814));
	m_spawnpositions.push_back(sf::Vector2f(1517, 1283));
	m_spawnpositions.push_back(sf::Vector2f(1517, 1814));
}
#include "Player.h"

/// <summary>
/// constructor
/// </summary>
Player::Player()
{
	init();
}

/// <summary>
/// deconstructor
/// </summary>
Player::~Player()
{

}

/// <summary>
/// initialises the player and its variables
/// </summary>
void Player::init()
{
	loadTextures();

	m_position.x = 2750;
	m_position.y = 5175;

	m_velocity.x = 0;
	m_velocity.y = 0;

	m_maxSpeed = 15;
	m_boostSpeed = 10;
	m_rotation = 0;
	m_speed = 0;
	m_maxVelocity = 3;
	m_fireRate = 50;
	m_coolDown = m_fireRate;
	m_health = 100;
	m_animatedColour = 0;

	m_iColour = 1;
	m_bColour = 1;

	m_powerupTime = 0;

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2);
	m_sprite.setRotation(0);
	m_projectileSprite.setTexture(m_projectileTxt);

	m_invincible = false;
	m_boosted = false;
	m_mapCreated = false;
	m_up = false;
	m_right = false;
	m_down = false;
	m_left = false;
}

/// <summary>
/// loads the players texture and outputs and error if it cant find the file
/// </summary>
void Player::loadTextures()
{
	if (!m_texture.loadFromFile("ASSETS/Textures/PlayerShip.png"))
	{
		std::cout << "Error! Unable to load PlayerShip.png from game files!" << std::endl;
	}
	if (!m_projectileTxt.loadFromFile("ASSETS/Textures/playerLaserBall.png"))
	{
		std::cout << "Error! Unable to load playerLaserBall.png from game files!" << std::endl;
	}
}

/// <summary>
/// Updates the player's movements and collisions
/// </summary>
/// <param name="deltaTime"></param>
void Player::update(sf::Time deltaTime, sf::View& v, PowerUp* powerup, std::vector<Tile> boundaryTiles, int playerNumber)
{
	m_health--;
	powerupColourAnimate();
	powerupTime();

	if (m_invincible == false && m_boosted == false)
	{
		m_animatedColour = 0;
		m_iColour = 1;
		m_bColour = 1;
	}

	rotate();
	speed();
	shoot();
	powerupCollision(powerup);


	if (playerNumber == 1)
	{
		v.setCenter(m_sprite.getPosition());
	}

	move();
	tileCollision(boundaryTiles, playerNumber);
	updateBullets(deltaTime, boundaryTiles);

}

/// <summary>
/// renders the player
/// </summary>
/// <param name="window"></param>
void Player::render(sf::RenderWindow* window, sf::Vector2f scale)
{
	m_sprite.setScale(scale);
	window->draw(m_sprite);
	renderBullets(window, scale);
}

///// <summary>
///// increases the players speed if the up key is pressed
///// </summary>
//void Player::addVelocity()
//{

//	if (sf::Keyboard::isKeyPressed(m_keyboard.Up))
//	{
//		if (m_boosted == true)
//		{
//			speed = m_maxSpeed + m_boostSpeed;
//		}
//		else if (m_boosted == false)
//		{
//			speed = m_maxSpeed;
//		}
//	}
//
//	//
//	else if (sf::Keyboard::isKeyPressed(m_keyboard.Down))
//	{
//		if (m_boosted == true)
//		{
//			speed = m_maxSpeed + m_boostSpeed;
//		}
//		else if (m_boosted == false)
//		{
//			speed = m_maxSpeed;
//		}
//	}
//
//	//
//	else if (sf::Keyboard::isKeyPressed(m_keyboard.Left))
//	{
//		if (m_boosted == true)
//		{
//			speed = m_maxSpeed + m_boostSpeed;
//		}
//		else if (m_boosted == false)
//		{
//			speed = m_maxSpeed;
//		}
//
//		m_up = false;
//		m_down = false;
//		m_left = true;
//		m_right = false;

//		m_angle = 270;
//		m_position.x -= speed;
//	}
//
//	else if (sf::Keyboard::isKeyPressed(m_keyboard.Right))
//	{
//		if (m_boosted == true)
//		{
//			speed = m_maxSpeed + m_boostSpeed;
//		}
//		else if (m_boosted == false)
//		{
//			speed = m_maxSpeed;
//		}
//
//		m_up = false;
//		m_down = false;
//		m_left = false;
//		m_right = true;
//		m_angle = 90;
//		m_position.x += speed;
//	}
//	m_sprite.setRotation(m_angle);
//}

/// <summary>
/// Raises or lowers the players speed via the up down W or S keys
/// </summary>
void Player::speed()
{
	if (m_speed < m_maxSpeed && sf::Keyboard::isKeyPressed(m_keyboard.W))
	{
		m_speed += 0.5f;
	}

	if (m_speed > 0 && sf::Keyboard::isKeyPressed(m_keyboard.S))
	{
		m_speed -= 0.5f;
	}
}

/// <summary>
/// rotates the player if the left, right, A or D key is pressed down;
/// </summary>
void Player::rotate()
{

	if (sf::Keyboard::isKeyPressed(m_keyboard.A) || sf::Keyboard::isKeyPressed(m_keyboard.Left))
	{
		m_rotation -= 2;
		if (m_rotation < 0)
		{
			m_rotation = 360;
		}
	}

	if (sf::Keyboard::isKeyPressed(m_keyboard.D) || sf::Keyboard::isKeyPressed(m_keyboard.Right))
	{
		m_rotation += 5;
		if (m_rotation > 360)
		{
			m_rotation = 0;
		}
	}
	m_sprite.setRotation(m_rotation);
}

/// <summary>
/// The players movement code
/// </summary>
void Player::move()
{
	m_velocity.x = cos((M_PI / 180) * m_rotation) * m_speed;
	m_velocity.y = sin((M_PI / 180) * m_rotation) * m_speed;

	m_position = m_position + m_velocity;
	m_sprite.setPosition(m_position);
}

/// <summary>
/// creates a projectile and adds it to the projectile vector if the count is greater than the fire rate
/// </summary>
void Player::shoot()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (m_coolDown > m_fireRate)
		{
			Projectile* projectile = new Projectile(m_position, m_projectileSprite, m_rotation, false);
			m_projectiles.push_back(projectile);
			m_coolDown = 0;
		}
		
	}
	m_coolDown++;
}

/// <summary>
/// updates all of the bullets in the vector
/// deletes any that are dead
/// </summary>
/// <param name="deltatime"></param>
/// <param name="boundaryTiles"></param>
void Player::updateBullets(sf::Time deltatime, std::vector<Tile> boundaryTiles)
{
	for (int i = 0; i < m_projectiles.size(); i++)
	{
		m_projectiles[i]->update(deltatime, m_position, boundaryTiles);


		if (m_projectiles[i]->m_alive == false)
		{
			m_projectiles[i]->~Projectile();
			m_projectiles[i] = nullptr;
			m_projectiles.erase(m_projectiles.begin() + i);
			i--;
		}
	}
}

/// <summary>
/// Renders the bullets
/// </summary>
/// <param name="window"></param>
/// <param name="scale"></param>
void Player::renderBullets(sf::RenderWindow* window, sf::Vector2f scale)
{
	for (auto b : m_projectiles)
	{
		b->render(window, scale);
	}
}

void Player::workerCollision()
{

}

void Player::projectileCollision()
{
	if (m_invincible == false)
	{

	}
}

void Player::enemyCollision()
{
	if (m_invincible == false)
	{

	}
}

/// <summary>
/// if the player's global bounds intersects the power up 
/// the power up's active is set to false and the player gets the buff of the power up
/// </summary>
/// <param name="powerup"></param>
void Player::powerupCollision(PowerUp * powerup)
{
	if (powerup->getActive() == true)
	{
		if (m_sprite.getGlobalBounds().intersects(powerup->getSprite().getGlobalBounds()))
		{
			powerup->setActive(false);

			if (powerup->getType() >= 1 && powerup->getType() <= 10)
			{
				m_invincible = true;
				m_boosted = false;
				m_iColour = 1; 
				m_bColour = 1;
				m_powerupTime = 250;
			}
			else if (powerup->getType() >= 11 && powerup->getType() <= 20)
			{
				m_invincible = false;
				m_boosted = true;
				m_iColour = 1;
				m_bColour = 1;
				m_powerupTime = 400;
			}
		}
	}
}

/// <summary>
/// prevents the player from going out of bounds
/// if the player intersects a black tile the player is pushed back 
/// depending on the direction they were facing 
/// </summary>
/// <param name="tilemap"></param>
void Player::tileCollision(std::vector<Tile>& tilemap, int playerNumber)
{
	if (playerNumber == 1)
	{
		for (int i = 0; i < tilemap.size(); i++)
		{
			if (tilemap[i].getType() == 1)
			{
				if (m_sprite.getGlobalBounds().intersects(tilemap[i].getSprite().getGlobalBounds()))
				{
					m_position -= m_velocity;
					m_sprite.setPosition(m_position);
				}
			}
		}
	}
}

/// <summary>
/// animates the player if the player has picked up a power up
/// </summary>
void Player::powerupColourAnimate()
{
	if (m_invincible == true)
	{
		m_animatedColour++;

		if (m_animatedColour > 20)
		{
			m_iColour *= -1;
			m_animatedColour = 0;
		}
	}

	else if (m_boosted == true)
	{
		m_animatedColour++;

		if (m_animatedColour > 20)
		{
			m_bColour *= -1;
			m_animatedColour = 0;
		}
	}

	if (m_iColour == -1)
	{
		m_sprite.setColor(sf::Color::Blue);
	}
	else if (m_bColour == -1)
	{
		m_sprite.setColor(sf::Color::Red);
	}
	else
	{
		m_sprite.setColor(sf::Color::White);
	}
}

/// <summary>
/// timer for the powerup
/// resets the invincible and boosted bools if the timer is 0
/// </summary>
void Player::powerupTime()
{
	if (m_invincible == true || m_boosted == true)
	{
		m_powerupTime--;
		std::cout << m_powerupTime << std::endl;

		if (m_powerupTime <= 0)
		{
			m_invincible = false;
			m_boosted = false;
			m_iColour = 1;
			m_bColour = 1;
			m_powerupTime = 0;
		}
	}
}

/// <summary>
/// returns the players position
/// </summary>
/// <returns></returns>
sf::Vector2f Player::getPosition()
{
	return m_sprite.getPosition();
}

/// <summary>
/// sets the players position
/// </summary>
/// <param name="position"></param>
void Player::setPosition(sf::Vector2f position)
{
	m_position = position;
	m_sprite.setPosition(m_position);
}


int Player::getHealth()
{
	return m_health;
}

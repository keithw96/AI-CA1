//
//
//
//
// C00204076
// Brandon Sea-Dempsey
// Started at 13:35 8 January 2019
// Finished at
// Time taken:
// Known bugs:

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
	m_angle = 0;
	m_maxVelocity = 5;

	m_health = 100;
	m_animatedColour = 0;

	m_iColour = 1;
	m_bColour = 1;

	m_powerupTime = 0;

	//m_projectileSprite.setTexture(m_projectileTxt);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2);
	m_sprite.setRotation(0);

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

	m_projectileTxt.loadFromFile("ASSETS/Textures/playerLaserBall.png");
}

/// <summary>
/// Updates the player's movements and collisions
/// </summary>
/// <param name="deltaTime"></param>
void Player::update(sf::Time deltaTime, sf::View & v, PowerUp * powerup, std::vector<Tile> &tilemap, int playerNumber)
{
	//
	m_position = m_sprite.getPosition();
	//
	createBoundaryTileVector(tilemap);
	//
	powerupColourAnimate();
	//
	powerupTime();
	
	//
	if (m_invincible == false && m_boosted == false)
	{
		m_animatedColour = 0;
		m_iColour = 1;
		m_bColour = 1;
	}

	//
	addVelocity();
	//
	powerupCollision(powerup);
	tileCollision(m_boundaryTiles, playerNumber);

	m_sprite.setPosition(m_position);
	//
	if (playerNumber == 1)
	{
		v.setCenter(m_sprite.getPosition());
	}
}

/// <summary>
/// renders the player
/// </summary>
/// <param name="window"></param>
void Player::render(sf::RenderWindow& window, sf::Vector2f scale)
{
	m_sprite.setScale(scale);
	window.draw(m_sprite);
}

/// <summary>
/// increases the players speed if the up key is pressed
/// </summary>
void Player::addVelocity()
{
	float speed = 0.0f;

	//
	if (sf::Keyboard::isKeyPressed(m_keyboard.Up))
	{
		//
		if (m_boosted == true)
		{
			speed = m_maxSpeed + m_boostSpeed;
		}
		//
		else if (m_boosted == false)
		{
			speed = m_maxSpeed;
		}
		//
		m_up = true;
		m_down = false;
		m_left = false;
		m_right = false;
		//
		m_angle = 0;
		m_position.y -= speed;
	}

	//
	else if (sf::Keyboard::isKeyPressed(m_keyboard.Down))
	{
		//
		if (m_boosted == true)
		{
			speed = m_maxSpeed + m_boostSpeed;
		}
		//
		else if (m_boosted == false)
		{
			speed = m_maxSpeed;
		}

		//
		m_up = false;
		m_down = true;
		m_left = false;
		m_right = false;
		//
		m_angle = 180;
		m_position.y += speed;
	}

	//
	else if (sf::Keyboard::isKeyPressed(m_keyboard.Left))
	{
		//
		if (m_boosted == true)
		{
			speed = m_maxSpeed + m_boostSpeed;
		}
		//
		else if (m_boosted == false)
		{
			speed = m_maxSpeed;
		}

		//
		m_up = false;
		m_down = false;
		m_left = true;
		m_right = false;
		//
		m_angle = 270;
		m_position.x -= speed;
	}

	//
	else if (sf::Keyboard::isKeyPressed(m_keyboard.Right))
	{
		//
		if (m_boosted == true)
		{
			speed = m_maxSpeed + m_boostSpeed;
		}
		//
		else if (m_boosted == false)
		{
			speed = m_maxSpeed;
		}

		//
		m_up = false;
		m_down = false;
		m_left = false;
		m_right = true;
		//
		m_angle = 90;
		m_position.x += speed;
	}

	m_sprite.setRotation(m_angle);
}

//
void Player::workerCollision()
{

}

//
void Player::projectileCollision()
{
	if (m_invincible == false)
	{

	}
}

//
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
	//
	if (powerup->getActive() == true)
	{
		if (m_sprite.getGlobalBounds().intersects(powerup->getSprite().getGlobalBounds()))
		{
			powerup->setActive(false);

			//
			if (powerup->getType() >= 1 && powerup->getType() <= 10)
			{
				m_invincible = true;
				m_boosted = false;
				m_iColour = 1; 
				m_bColour = 1;
				m_powerupTime = 250;
			}
			//
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
void Player::tileCollision(std::vector<Tile> &tilemap, int playerNumber)
{
	//
	if (playerNumber == 1)
	{
		for (int i = 0; i < tilemap.size(); i++)
		{
			if (tilemap[i].getType() == 1)
			{
				//
				if (m_sprite.getGlobalBounds().intersects(tilemap[i].getSprite().getGlobalBounds()))
				{
					std::cout << "Collided" << std::endl;

					//
					if (m_up == true)
					{
						m_position.y += 50;
					}
					//
					else if (m_down == true)
					{
						m_position.y -= 50;
					}
					//
					else if (m_left == true)
					{
						m_position.x += 55;
					}
					//
					else if (m_right == true)
					{
						m_position.x -= 55;
					}
				}//End if
			}//End if
		}//End for
	}

}

/// <summary>
/// creats a vector of the boundary tiles
/// </summary>
/// <param name="tilemap"></param>
void Player::createBoundaryTileVector(std::vector<Tile> &tilemap)
{
	//
	if (m_mapCreated == false)
	{
		//
		for (int i = 0; i < tilemap.size(); i++)
		{
			//
			if (tilemap[i].getType() == 1)
			{
				m_boundaryTiles.push_back(tilemap[i]);
			}

		}
	}

	//
	m_mapCreated = true;
}

/// <summary>
/// animates the player if the player has picked up a power up
/// </summary>
void Player::powerupColourAnimate()
{
	//
	if (m_invincible == true)
	{
		m_animatedColour++;

		if (m_animatedColour > 20)
		{
			m_iColour *= -1;
			m_animatedColour = 0;
		}
	}

	//
	else if (m_boosted == true)
	{
		m_animatedColour++;

		if (m_animatedColour > 20)
		{
			m_bColour *= -1;
			m_animatedColour = 0;
		}
	}

	//
	if (m_iColour == -1)
	{
		m_sprite.setColor(sf::Color::Blue);
	}
	//
	else if (m_bColour == -1)
	{
		m_sprite.setColor(sf::Color::Red);
	}
	//
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



#ifndef PLAYER_H
#define PLAYER_H

#define _USE_MATH_DEFINES

#include "SFML/Graphics.hpp"

#include "Power-Up.h"
#include "Tile.h"
#include "Projectile.h"
#include <iostream>
#include <vector>
#include <math.h>

class Player
{
public:
	Player();
	~Player();

	void update(sf::Time deltaTime, sf::View& v, PowerUp* powerup, std::vector<Tile> boundaryTiles, int playerNumber);
	void render(sf::RenderWindow* window, sf::Vector2f scale);

	void init();
	int getHealth();
	int getWorkerCount();
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);

	void tileCollision(std::vector<Tile>& tilemap, int playerNumber);

	sf::Sprite getBody();

private:
	void speed();
	void rotate();
	void move();
	void shoot();
	void updateBullets(sf::Time deltatime, std::vector<Tile> boundaryTiles);
	void renderBullets(sf::RenderWindow* window, sf::Vector2f scale);
	void powerupColourAnimate();
	void powerupTime();

	void workerCollision();
	void projectileCollision();
	void enemyCollision();
	void powerupCollision(PowerUp* powerup, int playerNum);

	void loadTextures();


	sf::Keyboard m_keyboard;

	sf::Texture m_texture;
	sf::Texture m_projectileTxt;
	sf::Sprite m_sprite;
	sf::Sprite m_projectileSprite;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;

	std::vector<Projectile*> m_projectiles;
	std::vector<sf::Vector2f> m_powerupSpawnPoints;
	float m_speed, m_maxSpeed, m_boostSpeed, m_rotation, m_maxVelocity;

	int m_health, m_maxHealth, m_animatedColour, m_iColour, m_bColour, m_powerupTime, m_coolDown, m_fireRate, m_workerCount;

	bool m_invincible, m_mapCreated, m_up, m_right, m_down, m_left;
};

#endif // !PLAYER_H
#ifndef POWERUP_H
#define POWERUP_H

#include "SFML/Graphics.hpp"

#include <iostream>
#include <stdlib.h> 

//
class PowerUp
{
public:
	PowerUp();
	~PowerUp();

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window, sf::Vector2f scale);

	int getType();

	void setActive(bool active);
	bool getActive();

	sf::Sprite getSprite();

	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();

private:
	void init();
	void loadTextures();
	void respawn();
	void setPowerUpSpawns();

	sf::Texture m_texture, m_textureTypeOne, m_textureTypeTwo;

	sf::Sprite m_sprite;

	sf::Vector2f m_position;

	std::vector<sf::Vector2f> m_spawnpositions;

	int m_type, m_lifeTime, m_respawnTime;
	bool m_active;

};

#endif // !POWERUP_H
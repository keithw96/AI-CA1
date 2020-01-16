#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class GameOverScreen
{
public:
	GameOverScreen();
	~GameOverScreen();

	void update(sf::Time deltatime, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);

private:
	void loadTextures();

	sf::Sprite m_background;
	sf::Sprite m_quitBtn;
	sf::Texture m_backgroundTxt;
	sf::Texture m_quitbtnTxt;
};


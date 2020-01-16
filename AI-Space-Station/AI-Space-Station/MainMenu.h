#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class MainMenu
{
public:
	MainMenu();
	~MainMenu();
	void update(sf::Time deltatime, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void playClickedTrue();
	void playClickedFalse();
	bool playClicked();
private:

	void init();
	void loadTextures();
	
	sf::Sprite m_background;
	sf::Sprite m_PlayBtn;
	sf::Sprite m_quitBtn;
	sf::Texture m_backgroundTxt;
	sf::Texture m_playTxt;
	sf::Texture m_quitTxt;
	bool m_playClicked;
};


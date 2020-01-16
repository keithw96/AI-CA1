#include "MainMenu.h"

/// <summary>
/// 
/// </summary>
MainMenu::MainMenu()
{
	init();
}

MainMenu::~MainMenu()
{
}

void MainMenu::init()
{
	loadTextures();
	m_background.setPosition(sf::Vector2f(0, 0));
	m_PlayBtn.setPosition(sf::Vector2f(200, 500));
	m_quitBtn.setPosition(sf::Vector2f(200, 1250));
	m_playClicked = false;
}

void MainMenu::update(sf::Time deltatime, sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = sf::Vector2f((float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y);
		if (m_PlayBtn.getGlobalBounds().contains(mousePos))
		{
			playClickedTrue();
		}

		if (m_quitBtn.getGlobalBounds().contains(mousePos))
		{
			window.close();
		}
	}
}

void MainMenu::render(sf::RenderWindow& window)
{
	window.draw(m_background);
	window.draw(m_PlayBtn);
	window.draw(m_quitBtn);
}

void MainMenu::loadTextures()
{
	if (!m_backgroundTxt.loadFromFile("ASSETS/Textures/MainMenuBackground.png"))
	{
		std::cout << "Error! Unable to load MainMenuBackgroung.png from game files!" << std::endl;
	}

	if (!m_playTxt.loadFromFile("ASSETS/Textures/PlayBtn.png"))
	{
		std::cout << "Error! Unable to load MainMenuBackgroung.png from game files!" << std::endl;
	}

	if (!m_quitTxt.loadFromFile("ASSETS/Textures/ExitBtn.png"))
	{
		std::cout << "Error! Unable to load MainMenuBackgroung.png from game files!" << std::endl;
	}

	m_background.setTexture(m_backgroundTxt);
	m_PlayBtn.setTexture(m_playTxt);
	m_quitBtn.setTexture(m_quitTxt);
}

void MainMenu::playClickedTrue()
{
	m_playClicked = true;
}
void MainMenu::playClickedFalse()
{
	m_playClicked = false;
}

bool MainMenu::playClicked()
{
	return m_playClicked;
}


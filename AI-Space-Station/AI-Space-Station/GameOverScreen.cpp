#include "GameOverScreen.h"

/// <summary>
/// Constructor
/// </summary>
GameOverScreen::GameOverScreen()
{
	loadTextures();
	m_background.setPosition(sf::Vector2f(0, 0));
	m_quitBtn.setPosition(1150, 1500);
}

/// <summary>
/// Deconstructor
/// </summary>
GameOverScreen::~GameOverScreen()
{
}

/// <summary>
/// Checks for a mouse click over the quit button
/// </summary>
/// <param name="deltatime"></param>
/// <param name="window"></param>
void GameOverScreen::update(sf::Time deltatime, sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = sf::Vector2f((float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y);

		if (m_quitBtn.getGlobalBounds().contains(mousePos))
		{
			window.close();
		}
	}
}

/// <summary>
/// Renders the screen
/// </summary>
/// <param name="window"></param>
void GameOverScreen::render(sf::RenderWindow& window)
{
	window.draw(m_background);
	window.draw(m_quitBtn);
}

/// <summary>
/// Loads the textures and sets them to the sprites
/// </summary>
void GameOverScreen::loadTextures()
{
	if (!m_backgroundTxt.loadFromFile("ASSETS/Textures/GameOver.png"))
	{
		std::cout << "Error! Unable to load GameOver.png from game files!" << std::endl;
	}
	if (!m_quitbtnTxt.loadFromFile("ASSETS/Textures/ExitBtn.png"))
	{
		std::cout << "Error! Unable to load MainMenuBackgroung.png from game files!" << std::endl;
	}

	m_background.setTexture(m_backgroundTxt);
	m_quitBtn.setTexture(m_quitbtnTxt);
}

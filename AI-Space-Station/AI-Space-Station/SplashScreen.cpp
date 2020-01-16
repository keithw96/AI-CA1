#include "SplashScreen.h"

/// <summary>
/// constructor 
/// </summary>
Splash::Splash()
{
	init();
}

/// <summary>
/// deconstructor
/// </summary>
Splash::~Splash()
{

}

/// <summary>
/// intiialises the splash screens variables
/// </summary>
void Splash::init()
{
	loadFonts();

	m_screenTime = 0;

	m_yPosOne = -100;
	m_xPosTwo = -750;
	m_xPosThree = 1800;
	m_yPosThree = 2100;

	m_positionOne = sf::Vector2f(800, -100);
	m_positionTwo = sf::Vector2f(-750, 700);
	m_positionThree = sf::Vector2f(1800, 2100); // 800, 800

	m_textOne.setString("Developed and Test by");
	m_textOne.setFont(m_font);
	m_textOne.setCharacterSize(70);
	m_textOne.setPosition(m_positionOne);

	m_textTwo.setString("Keith Wilson - C00205321");
	m_textTwo.setFont(m_font);
	m_textTwo.setCharacterSize(70);
	m_textTwo.setPosition(m_positionTwo);

	m_textThree.setString("Martin Farrel - C00157047");
	m_textThree.setFont(m_font);
	m_textThree.setCharacterSize(70);
	m_textThree.setPosition(m_positionThree);
}

/// <summary>
/// loads the arial font used in the splash screen
/// </summary>
void Splash::loadFonts()
{
	if (!m_font.loadFromFile("ASSETS/Fonts/arial.ttf"))
	{
		std::cout << "Error! Unable to load arial.ttf from game files!" << std::endl;
	}
}

/// <summary>
/// updates the splash screen
/// </summary>
/// <param name="deltaTime"></param>
void Splash::update(sf::Time deltaTime)
{
	if (m_yPosOne < 600)
	{
		m_yPosOne += 5;
		m_positionOne = sf::Vector2f(800, m_yPosOne);
	}
	if (m_xPosTwo < 800)
	{
		m_xPosTwo += 8;
		m_positionTwo = sf::Vector2f(m_xPosTwo, 700);

	}
	if (m_xPosThree > 800)
	{
		m_xPosThree -= 8;
		m_positionThree = sf::Vector2f(m_xPosThree, m_yPosThree);
	}
	if (m_yPosThree > 800)
	{
		m_yPosThree -= 10;
		m_positionThree = sf::Vector2f(m_xPosThree, m_yPosThree);
	}
	m_textOne.setPosition(m_positionOne);
	m_textTwo.setPosition(m_positionTwo);
	m_textThree.setPosition(m_positionThree);

	m_screenTime++;
}

/// <summary>
/// renders the text 
/// </summary>
/// <param name="window"></param>
void Splash::render(sf::RenderWindow& window)
{
	window.draw(m_textOne);
	window.draw(m_textTwo);
	window.draw(m_textThree);
}

/// <summary>
/// returns the timer for the screen
/// </summary>
/// <returns></returns>
int Splash::getScreenTime()
{
	return m_screenTime;
}
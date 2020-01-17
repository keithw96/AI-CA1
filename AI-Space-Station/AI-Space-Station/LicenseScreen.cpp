#include "LicenseScreen.h"

/// <summary>
/// constructor
/// </summary>
License::License()
{
	init();
}

/// <summary>
/// deconstructor
/// </summary>
License::~License()
{

}

/// <summary>
/// intitialises the License screens vairables 
/// </summary>
void License::init()
{
	//
	loadTextures();
	//
	m_position = sf::Vector2f(0, 0);
	//
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(50, 50);
	//
	m_screenTime = 0;
}

/// <summary>
/// loads the license screens background
/// </summary>
void License::loadTextures()
{
	//
	if (!m_texture.loadFromFile("ASSETS/Textures/License.png"))
	{
		std::cout << "Error! Unable to load License.png from game files!" << std::endl;
	}
}

/// <summary>
/// updates the timer for the licence screen
/// </summary>
/// <param name="deltaTime"></param>
void License::update(sf::Time deltaTime)
{
	m_screenTime++;
}

/// <summary>
/// renders the licence screen
/// </summary>
/// <param name="window"></param>
void License::render(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}


/// <summary>
/// returns the timer for the licence screen
/// </summary>
/// <returns></returns>
int License::getScreenTime()
{
	return m_screenTime;
}
//
//
//
//
// C00204076
// Brandon Sea-Dempsey
// Started at 9:26 11 January 2019
// Finished at
// Time taken:
// Known bugs:

#ifndef SPLASH_H
#define SPLASH_H

#include "SFML/Graphics.hpp"

#include <iostream>

class Splash
{
public:
	Splash();
	~Splash();

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window);

	int getScreenTime();

private:
	void init();
	void loadFonts();

	sf::Text m_textOne, m_textTwo, m_textThree;
	sf::Font m_font;

	sf::Vector2f m_positionOne, m_positionTwo, m_positionThree;

	int m_screenTime;

	float m_yPosOne, m_xPosTwo, m_xPosThree, m_yPosThree;
};

#endif // !SPLASH_H
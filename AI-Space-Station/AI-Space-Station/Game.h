#ifndef GAME_H
#define GAME_H
#include <vector>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Tile.h"
#include "AlienNest.h"
#include "Predator.h"
#include "Worker.h"
#include "Sweeper.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "LicenseScreen.h"
#include "Player.h"
#include "Power-Up.h"

class Splash;
class License;
class Player;
class PowerUp;
class AlienNest;

enum class GameState
{
	SPLASH, LICENSE, MENU, GAME, CONTROLS, GAMEOVER
};

struct VectorComparator
{
	bool operator() (sf::Vector2f lhs, sf::Vector2f rhs) const
	{
		return std::tie(lhs.x, rhs.y) < std::tie(rhs.x, lhs.y);
	}
};

class Game
{
public:
	Game();
	~Game();
	void setGameState(GameState gameMode);
	GameState getGameState();
	void run();

protected:

	GameState gameState;
private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void loadSprites();
	void determineTile(int type, int x, int y);
	void updateHealthBar();

	sf::RenderWindow m_window;
	sf::View m_view;
	sf::View miniMap;

	int m_windowHeight;
	int m_windowWidth;
	int m_healthBarHeight;
	int m_healthBarWidth;

	sf::RectangleShape m_healthBarBorder;
	sf::RectangleShape m_healthBar;

	bool is_running;


	sf::Texture m_horizontalTileTexture;
	sf::Texture m_verticalTileTexture;
	sf::Texture m_bottomLeftTileTexture;
	sf::Texture m_bottomRightTileTexture;
	sf::Texture m_topLeftTileTexture;
	sf::Texture m_topRightTileTexture;
	sf::Texture m_tJunctionLeftTexture;
	sf::Texture m_tJunctionRightTexture;
	sf::Texture m_tJunctionUpTexture;
	sf::Texture m_tJunctionDownTexture;
	sf::Texture m_black_tileTexture;
	sf::Texture m_tileTexture;
	sf::Texture m_nestTexture;
	sf::Texture m_predatorTexture;
	sf::Texture m_projectileTexture;

	sf::Sprite m_horizontalTileSprite;
	sf::Sprite m_verticalTileSprite;
	sf::Sprite m_bottomLeftTileSprite;
	sf::Sprite m_bottomRightTileSprite;
	sf::Sprite m_topLeftTileSprite;
	sf::Sprite m_topRightTileSprite;
	sf::Sprite m_tJunctionLeftSprite;
	sf::Sprite m_tJunctionRightSprite;
	sf::Sprite m_tJunctionUpSprite;
	sf::Sprite m_tJunctionDownSprite;
	sf::Sprite m_black_tileSprite;
	sf::Sprite m_tileSprite;
	sf::Sprite m_nestSprite;
	sf::Sprite m_predatorSprite;
	sf::Sprite m_projectileSprite;

	std::vector<Tile> m_tileMap;
	std::vector<Tile> m_boundaryTiles;
	std::vector<AlienNest> m_nestArr;

	static const int NUM_OF_WORKERS = 15;
	/*
	0 = nonCollision Black tile
	1 = Collision black tile
	2 = vertical tile
	3 = horizontal
	4 = top left corner
	5 = top right corner
	6 = bottom left corner
	7 = bottom right corner
	8 = blue tile
	9 = T junction left
	10 = T juntion right
	11 = T junction up
	12 = T juntion down
	*/

	int map[32][32] = {
	{ 0, 0, 0, 0,  0,  0, 0,  0,  0,  0, 0, 0, 0, 0,  0,  0,  0,  0,  1, 1, 1,  1,  1,  1,  1,  1,   1,  1, 0, 0, 0, 0, } ,
	{ 0, 0, 0, 0,  0,  0, 0,  0,  0,  0, 0, 0, 0, 0,  0,  0,  0,  0,  1, 4, 11, 11, 11, 11, 11, 11,  5,  1, 0, 0, 0, 0, } ,
	{ 0, 0, 0, 0,  1,  1, 1,  1,  1,  1, 1, 1, 1, 0,  0,  0,  0,  0,  1, 9, 8,  8,  8,  8,  8,  8,   10, 1, 0, 0, 0, 0, } ,
	{ 0, 0, 0, 0,  1,  4, 3,  3,  3,  3, 3, 5, 1, 0,  0,  0,  1,  1,  1, 9, 8,  8,  8,  8,  8,  8,   10, 1, 0, 0, 0, 0, } ,
	{ 0, 0, 0, 0,  1,  2, 1,  1,  1,  1, 1, 2, 1, 0,  0,  0,  1,  4,  3, 8, 8,  8,  8,  8,  8,  8,   10, 1, 0, 0, 0, 0, } ,
	{ 0, 1, 1, 1,  1,  2, 1,  1,  1,  1, 1, 2, 1, 0,  0,  0,  1,  2,  1, 9, 8,  8,  8,  8,  8,  8,   10, 1, 0, 0, 0, 0, } ,
	{ 0, 1, 4, 11, 11, 8, 11, 11, 5,  1, 1, 2, 1, 0,  0,  0,  1,  2,  1, 9, 8,  8,  8,  8,  8,  8,   10, 1, 0, 0, 0, 0, } ,
	{ 0, 1, 9, 8,  8,  8, 8,  8,  10, 1, 1, 2, 1, 1,  1,  1,  1,  2,  1, 6, 12, 12, 8,  12, 12, 12,  7,  1, 0, 0, 0, 0, } ,
	{ 0, 1, 9, 8,  8,  8, 8,  8,  10, 1, 1, 6, 3, 3,  3,  3,  3,  10, 1, 1, 1,  1,  2,  1,  1,  1,   1,  1, 0, 0, 0, 0, } ,
	{ 0, 1, 9, 8,  8,  8, 8,  8,  10, 1, 1, 1, 1, 1,  1,  1,  1,  2,  1, 0, 0,  1,  2,  1,  0,  0,   0,  0, 0, 0, 0, 0, } ,
	{ 0, 1, 6, 12, 12, 8, 12, 12, 7,  1, 0, 0, 0, 0,  0,  0,  1,  2,  1, 0, 0,  1,  2,  1,  1,  1,   1,  0, 0, 0, 0, 0, } ,
	{ 0, 1, 1, 1,  1,  2, 1,  1,  1,  1, 0, 0, 0, 0,  0,  0,  1,  2,  1, 0, 0,  1,  2,  1,  0,  0,   0,  0, 0, 0, 0, 0, } ,
	{ 0, 0, 0, 1,  1,  2, 1,  0,  0,  0, 0, 0, 0, 1,  1,  1,  1,  2,  1, 1, 1,  1,  2,  1,  0,  0,   0,  0, 0, 0, 0, 0, } ,
	{ 0, 0, 0, 1,  1,  2, 1,  0,  0,  0, 0, 0, 0, 1,  4,  3,  3,  12, 3, 3, 3,  3,  10, 1,  0,  0,   0,  0, 0, 0, 0, 0, } ,
	{ 0, 0, 0, 1,  1,  2, 1,  0,  0,  0, 0, 0, 0, 1,  2,  1,  1,  1,  1, 1, 1,  1,  2,  1,  0,  0,   0,  0, 0, 0, 0, 0, } ,
	{ 0, 0, 0, 1,  1,  2, 1,  0,  0,  0, 0, 0, 0, 1,  2,  1,  0,  0,  0, 0, 0,  1,  2,  1,  0,  0,   0,  0, 0, 0, 0, 0, } ,
	{ 0, 0, 1, 1,  1,  2, 1,  1,  1,  0, 0, 0, 0, 1,  2,  1,  0,  0,  1, 1, 1,  1,  2,  1,  1,  1,   1,  0, 0, 0, 0, 0, } ,
	{ 0, 0, 1, 4,  11, 8, 11, 5,  1,  0, 0, 0, 0, 1,  2,  1,  0,  0,  1, 4, 11, 11, 8,  11, 11, 5,   1,  0, 0, 0, 0, 0, } ,
	{ 0, 0, 1, 9,  8,  8, 8,  10, 1,  1, 1, 1, 1, 1,  2,  1,  1,  1,  1, 9, 8,  8,  8,  8,  8,  10,  1,  0, 0, 0, 0, 0, } ,
	{ 0, 0, 1, 9,  8,  8, 8,  8,  3,  3, 3, 3, 3, 3,  8,  3,  3,  3,  3, 8, 8,  8,  8,  8,  8,  10,  1,  0, 0, 0, 0, 0, } ,
	{ 0, 0, 1, 6,  12, 8, 12, 7,  1,  1, 1, 1, 1, 1,  2,  1,  1,  1,  1, 9, 8,  8,  8,  8,  8,  10,  1,  0, 0, 0, 0, 0, } ,
	{ 0, 0, 1, 1,  1,  2, 1,  1,  1,  0, 0, 0, 0, 1,  2,  1,  0,  0,  1, 6, 12, 12, 8,  12, 12, 7,   1,  0, 0, 0, 0, 0, } ,
	{ 0, 0, 0, 0,  1,  2, 1,  0,  0,  0, 0, 0, 0, 1,  2,  1,  0,  0,  1, 1, 1,  1,  2,  1,  1,  1,   1,  0, 0, 0, 0, 0, } ,
	{ 0, 0, 0, 0,  1,  2, 1,  0,  0,  0, 0, 0, 0, 1,  2,  1,  0,  0,  0, 0, 0,  1,  2,  1,  0,  0,   0,  0, 0, 0, 0, 0, } ,
	{ 0, 0, 0, 0,  1,  2, 1,  0,  0,  0, 0, 0, 0, 1,  2,  1,  0,  0,  0, 0, 0,  1,  2,  1,  0,  0,   0,  0, 0, 0, 0, 0, } ,
	{ 0, 0, 0, 0,  1,  2, 1,  0,  0,  0, 0, 1, 1, 1,  2,  1,  1,  1,  0, 0, 0,  1,  2,  1,  0,  0,   0,  0, 0, 0, 0, 0, } ,
	{ 0, 0, 0, 0,  1,  2, 1,  0,  0,  0, 0, 1, 4, 11, 8,  11, 5,  1,  0, 0, 0,  1,  2,  1,  0,  0,   0,  0, 0, 0, 0, 0, } ,
	{ 0, 0, 0, 0,  1,  2, 1,  1,  1,  1, 1, 1, 9, 8,  8,  8,  10, 1,  1, 1, 1,  1,  2,  1,  0,  0,   0,  0, 0, 0, 0, 0, } ,
	{ 0, 0, 0, 0,  1,  6, 3,  3,  3,  3, 3, 3, 8, 8,  8,  8,  8,  3,  3, 3, 3,  3,  7,  1,  0,  0,   0,  0, 0, 0, 0, 0, } ,
	{ 0, 0, 0, 0,  1,  1, 1,  1,  1,  1, 1, 1, 9, 8,  8,  8,  10, 1,  1, 1, 1,  1,  1,  1,  0,  0,   0,  0, 0, 0, 0, 0, } ,
	{ 0, 0, 0, 0,  0,  0, 0,  0,  0,  0, 0, 1, 6, 12, 12, 12, 7,  1,  0, 0, 0,  0,  0,  0,  0,  0,   0,  0, 0, 0, 0, 0, } ,
	{ 0, 0, 0, 0,  0,  0, 0,  0,  0,  0, 0, 1, 1, 1,  1,  1,  1,  1,  0, 0, 0,  0,  0,  0,  0,  0,   0,  0, 0, 0, 0, 0, } ,
	};

	//
	Predator * m_predator;
	Splash * m_splash;
	License * m_license;
	Player * m_player;
	Player *m_miniPlayer;
	PowerUp * m_powerup;
	Worker m_worker[NUM_OF_WORKERS];
	Sweeper m_sweeper;
	Player* m_player;
	Player* m_miniPlayer;
	MainMenu* m_mainMenu;
};

#endif // !GAME_H

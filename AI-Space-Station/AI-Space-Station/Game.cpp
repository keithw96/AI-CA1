#include "Game.h"

/// <summary>
/// constructor
/// </summary>
Game::Game():
	m_window{ sf::VideoMode{3840, 2160, 32}, "AI Space Station"},
	is_running{ true },
	gameState{GameState::YOUWIN}
{
	m_menuView = m_window.getView();

	m_view.setCenter(m_window.getSize().x / 2, m_window.getSize().y / 2);
	m_view.setSize(2500, 2000);
	m_view.zoom(1.5f);

	m_view.zoom(0.35f);
	
	miniMap.reset(sf::FloatRect(0, 0, m_window.getSize().x / 2, m_window.getSize().y / 2));
	miniMap.setViewport(sf::FloatRect(1.1f - (1.f*miniMap.getSize().x) / m_window.getSize().x - 0.04f, 0.3f - (1.f*miniMap.getSize().y) / m_window.getSize().y - 0.02f, (1.f*miniMap.getSize().x) / m_window.getSize().x, (1.f*miniMap.getSize().y) / m_window.getSize().y));
	miniMap.zoom(11.0f);

	loadSprites();

	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			determineTile(map[i][j], j, i);
		}
	}

	m_nestArr.push_back(AlienNest(sf::Vector2f(4260, 812), m_nestSprite, m_projectileSprite, m_predatorSprite));
	m_nestArr.push_back(AlienNest(sf::Vector2f(1061, 1557), m_nestSprite, m_projectileSprite, m_predatorSprite));
	m_nestArr.push_back(AlienNest(sf::Vector2f(4295, 3555), m_nestSprite, m_projectileSprite, m_predatorSprite));

	m_splash = new Splash();
	m_license = new License();
	m_mainMenu = new MainMenu();
	m_gameOverScreen = new GameOverScreen();
	m_youWinScreen = new YouWinScreen();
	m_player = new Player();
	m_miniPlayer = new Player();
	m_powerup = new PowerUp();

	m_healthBarHeight = 40;
	m_healthBarWidth = 200;
	m_healthBarBorder = sf::RectangleShape(sf::Vector2f(m_healthBarWidth, m_healthBarHeight));
	m_healthBarBorder.setPosition(m_view.getCenter().x - ((m_window.getSize().x / 2) - 5), m_view.getCenter().y + ((m_window.getSize().y / 2) - (m_healthBarHeight + 5)));
	m_healthBarBorder.setOutlineColor(sf::Color::Magenta);
	m_healthBarBorder.setOutlineThickness(5);
	m_healthBarBorder.setFillColor(sf::Color::Transparent);

	m_healthBar = sf::RectangleShape(sf::Vector2f(m_healthBarWidth * ((float)m_player->getHealth() / 100.0f), m_healthBarHeight));
	m_healthBar.setPosition(m_view.getCenter().x - ((m_window.getSize().x / 2) - 5), m_view.getCenter().y + ((m_window.getSize().y / 2) - (m_healthBarHeight + 5)));
	m_healthBar.setFillColor(sf::Color::Green);
	m_worker[1].setPos(sf::Vector2f(600, 1200));
	m_worker[2].setPos(sf::Vector2f(1000, 1300));
	m_worker[3].setPos(sf::Vector2f(1000, 3200));
	m_worker[4].setPos(sf::Vector2f(2750, 3300));
	m_worker[5].setPos(sf::Vector2f(1000, 5000));
	m_worker[6].setPos(sf::Vector2f(4000, 5200));
	m_worker[7].setPos(sf::Vector2f(4000, 3200));
	m_worker[8].setPos(sf::Vector2f(4000, 1200));
	m_worker[9].setPos(sf::Vector2f(3800, 1400));
	m_worker[10].setPos(sf::Vector2f(4200, 1400));
	m_worker[11].setPos(sf::Vector2f(4200, 3000));
	m_worker[12].setPos(sf::Vector2f(3800, 2800));
}

/// <summary>
/// deconstructor
/// </summary>
Game::~Game()
{

}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);

	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			processEvents();
			update(timeSinceLastUpdate);
			timeSinceLastUpdate = sf::Time::Zero;
		}
		render();
	}
}

/// <summary>
/// updates the current gamestate
/// </summary>
/// <param name="deltaTime"></param>
void Game::update(sf::Time deltaTime)
{
	if (!is_running)
	{
		m_window.close();
	}

	// Updates game based on current state
	switch (gameState)
	{
	case GameState::SPLASH:
		m_splash->update(deltaTime);
		if (m_splash->getScreenTime() > 270)
		{
			setGameState(GameState::LICENSE);
		}
		break;
	case GameState::LICENSE:
		m_license->update(deltaTime);
		if (m_license->getScreenTime() > 270)
		{
			setGameState(GameState::MENU);
		}
		break;
	case GameState::MENU:
		m_mainMenu->update(deltaTime, m_window);
		if (m_mainMenu->playClicked())
		{
			m_mainMenu->playClickedFalse();
			gameState = GameState::GAME;
		}
		break;
	case GameState::GAME:
		m_player->update(deltaTime, m_view, m_powerup, m_boundaryTiles, 1);
		m_miniPlayer->update(deltaTime, m_view, m_powerup, m_boundaryTiles, 2);

		m_miniPlayer->setPosition(m_player->getPosition());

		m_powerup->update(deltaTime);
		for (int i = 0; i < m_nestArr.size(); i++)
		{
			m_nestArr[i].update(deltaTime, m_player->getPosition(), m_boundaryTiles);
		}

		m_healthBar.setPosition(m_view.getCenter().x - (m_view.getSize().x / 2) + 50, m_view.getCenter().y - (m_view.getSize().y / 2) + m_healthBarHeight);
		m_healthBar.setSize(sf::Vector2f(m_healthBarWidth * ((float)m_player->getHealth() / 100.0f), m_healthBarHeight));
		m_healthBarBorder.setPosition(m_view.getCenter().x - (m_view.getSize().x / 2) + 50, m_view.getCenter().y - (m_view.getSize().y / 2) + m_healthBarHeight);

		updateHealthBar();

		for (int i = 0; i < NUM_OF_WORKERS; i++)
		{
			m_worker[i].update();
			m_worker[i].checkWallCollision(m_tileMap);
			m_worker[i].checkPlayerCollision(m_player->getBody()); //need to get player sprite
			m_worker[i].checkSweeperCollision(m_sweeper.getBody());
		}

		m_sweeper.update();
		for (int i = 0; i < NUM_OF_WORKERS; i++)
		{
			if (m_worker[i].getAlive())
			{
				m_sweeper.checkForWorker(m_worker[i].getBody().getPosition());
			}
		}

		if (m_player->getHealth() <= 0)
		{
			gameState = GameState::GAMEOVER;
		}

		if (m_player->getWorkerCount() == 12)
		{
			gameState = GameState::YOUWIN;
		}

		m_sweeper.checkForPlayer(m_player->getBody());
		m_sweeper.checkForWall(m_tileMap);

		break;
	case GameState::GAMEOVER:
		m_gameOverScreen->update(deltaTime, m_window);
		break;

	case GameState::YOUWIN:
		m_youWinScreen->update(deltaTime, m_window);
		break;
	}

	m_window.display();
}

/// <summary>
/// checks for events that close the window 
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type)
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				is_running = false;
			}
		}
	}
}

/// <summary>
/// renders the current gamestate
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0));

	// Updates rendering based on current state
	switch (gameState)
	{
	case GameState::SPLASH:
		m_splash->render(m_window);
		break;
	case GameState::LICENSE:
		m_license->render(m_window);
		break;
	case GameState::MENU:
		m_window.setView(m_menuView);
		m_mainMenu->render(m_window);
		break;
	case GameState::GAME:
		//game render
		m_window.setView(m_view);

		for (int i = 0; i < m_tileMap.size(); i++)
		{
			m_tileMap[i].draw(&m_window);
		}

		for (int i = 0; i < m_nestArr.size(); i++)
		{
			m_nestArr[i].render(&m_window, sf::Vector2f(1.0, 1.0));
		}

		m_player->render(&m_window, sf::Vector2f(1.0f, 1.0f));
		for (int i = 0; i < NUM_OF_WORKERS; i++)
		{
			if (m_worker[i].getAlive())
			{
				m_window.draw(m_worker[i].getBody());
			}
		}
		m_window.draw(m_sweeper.getBody());
		m_powerup->render(m_window, sf::Vector2f(1.0f, 1.0f));

		m_window.draw(m_healthBar);
		m_window.draw(m_healthBarBorder);

		m_window.setView(miniMap);

		//minimap render
		for (int i = 0; i < m_tileMap.size(); i++)
		{
			m_tileMap[i].draw(&m_window);
		}

		/*for (int i = 0; i < m_nestArr.size(); i++)
		{
			m_nestArr[i].render(&m_window, sf::Vector2f(2.0, 2.0));
		}*/

		m_miniPlayer->render(&m_window, sf::Vector2f(10.0f, 10.0f));
		m_powerup->render(m_window, sf::Vector2f(5.0f, 5.0f));
		break;
	case GameState::GAMEOVER:
		m_window.setView(m_menuView);
		m_gameOverScreen->render(m_window);
		break;
	case GameState::YOUWIN:
		m_window.setView(m_menuView);
		m_youWinScreen->render(m_window);
	}
	m_window.display();
}

/// <summary>
/// sets the current gamestate
/// </summary>
/// <param name="gameMode"></param>
void Game::setGameState(GameState gameMode)
{
	gameState = gameMode;
}

/// <summary>
/// returns the current gamestate
/// </summary>
/// <returns></returns>
GameState Game::getGameState()
{
	return gameState;
}

/// <summary>
/// loads all of the games textures and sets them to their relevant sprite
/// </summary>
void Game::loadSprites()
{
	m_bottomLeftTileTexture.loadFromFile("ASSETS/Textures/bottom_left_corner.png");
	m_bottomRightTileTexture.loadFromFile("ASSETS/Textures/bottom_right_corner.png");
	m_topLeftTileTexture.loadFromFile("ASSETS/Textures/top_left_corner.PNG");
	m_topRightTileTexture.loadFromFile("ASSETS/Textures/top_right_corner.PNG");
	m_horizontalTileTexture.loadFromFile("ASSETS/Textures/horizontal_tile.PNG");
	m_verticalTileTexture.loadFromFile("ASSETS/Textures/vertical_tile.PNG");
	m_tJunctionLeftTexture.loadFromFile("ASSETS/Textures/T_junction_left.PNG");
	m_tJunctionRightTexture.loadFromFile("ASSETS/Textures/T_junction_right.PNG");
	m_tJunctionUpTexture.loadFromFile("ASSETS/Textures/T_junction_up.PNG");
	m_tJunctionDownTexture.loadFromFile("ASSETS/Textures/T_junction_down.PNG");
	m_black_tileTexture.loadFromFile("ASSETS/Textures/black_tile.png");
	m_tileTexture.loadFromFile("ASSETS/Textures/tile.png");
	m_nestTexture.loadFromFile("ASSETS/Textures/alien_maker.png");
	m_predatorTexture.loadFromFile("ASSETS/Textures/predatorMine.png");
	m_projectileTexture.loadFromFile("ASSETS/Textures/laserBall.png");
	

	m_black_tileSprite.setTexture(m_black_tileTexture);
	m_bottomLeftTileSprite.setTexture(m_bottomLeftTileTexture);
	m_bottomRightTileSprite.setTexture(m_bottomRightTileTexture);
	m_horizontalTileSprite.setTexture(m_horizontalTileTexture);
	m_tileSprite.setTexture(m_tileTexture);
	m_tJunctionLeftSprite.setTexture(m_tJunctionLeftTexture);
	m_tJunctionRightSprite.setTexture(m_tJunctionRightTexture);
	m_tJunctionUpSprite.setTexture(m_tJunctionUpTexture);
	m_tJunctionDownSprite.setTexture(m_tJunctionDownTexture);
	m_topLeftTileSprite.setTexture(m_topLeftTileTexture);
	m_topRightTileSprite.setTexture(m_topRightTileTexture);
	m_verticalTileSprite.setTexture(m_verticalTileTexture);
	m_nestSprite.setTexture(m_nestTexture);
	m_predatorSprite.setTexture(m_predatorTexture);
	m_projectileSprite.setTexture(m_projectileTexture);
}

/// <summary>
/// creates the vector of tiles and sets their position and sprite
/// </summary>
/// <param name="type"></param>
/// <param name="x"></param>
/// <param name="y"></param>
void Game::determineTile(int type, int x, int y)
{
	if (type == 0) {
		m_tileMap.push_back(Tile(sf::Vector2f(x, y), m_black_tileSprite, 0));
	}
	if (type == 1) {
		m_tileMap.push_back(Tile(sf::Vector2f(x, y), m_black_tileSprite, 1));
		m_boundaryTiles.push_back(Tile(sf::Vector2f(x, y), m_black_tileSprite, 1));
	}
	if (type == 2) {
		m_tileMap.push_back(Tile(sf::Vector2f(x, y), m_verticalTileSprite, 2));
	}
	if (type == 3) {
		m_tileMap.push_back(Tile(sf::Vector2f(x, y), m_horizontalTileSprite, 3));
	}
	if (type == 4) {
		m_tileMap.push_back(Tile(sf::Vector2f(x, y), m_topLeftTileSprite, 4));
	}
	if (type == 5) {
		m_tileMap.push_back(Tile(sf::Vector2f(x, y), m_topRightTileSprite, 5));
	}
	if (type == 6) {
		m_tileMap.push_back(Tile(sf::Vector2f(x, y), m_bottomLeftTileSprite, 6));
	}
	if (type == 7) {
		m_tileMap.push_back(Tile(sf::Vector2f(x, y), m_bottomRightTileSprite, 7));
	}
	if (type == 8) {
		m_tileMap.push_back(Tile(sf::Vector2f(x, y), m_tileSprite, 8));
	}
	if (type == 9) {
		m_tileMap.push_back(Tile(sf::Vector2f(x, y), m_tJunctionLeftSprite, 9));
	}
	if (type == 10) {
		m_tileMap.push_back(Tile(sf::Vector2f(x, y), m_tJunctionRightSprite, 10));
	}
	if (type == 11) {
		m_tileMap.push_back(Tile(sf::Vector2f(x, y), m_tJunctionUpSprite, 11));
	}
	if (type == 12) {
		m_tileMap.push_back(Tile(sf::Vector2f(x, y), m_tJunctionDownSprite, 12));
	}
}

void Game::updateHealthBar()
{
	if (m_player->getHealth() < 66)
	{
		m_healthBar.setFillColor(sf::Color::Yellow);
	}
	if (m_player->getHealth() < 33)
	{
		m_healthBar.setFillColor(sf::Color::Red);
	}
}
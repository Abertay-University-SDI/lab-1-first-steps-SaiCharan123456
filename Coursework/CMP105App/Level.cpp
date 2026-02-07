#include "Level.h"
using namespace std;

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in), m_text(m_font), m_scoreText(m_font), m_gameOverText(m_font)
{
	// initialise game objects
	m_player.setRadius(15);
	m_player.setFillColor(sf::Color::Green);
	m_player.setPosition({ 400,400 });

	m_food.setRadius(10);
	m_food.setFillColor(sf::Color::Red);

	if (!m_font.openFromFile("font/arial.ttf")) std::cerr << "missed font\n";

	m_text.setFont(m_font);
	m_text.setString("Score:- ");
	m_text.setStyle(sf::Text::Bold);
	m_text.setPosition({ 50,50 });
	m_text.setCharacterSize(50);

	spawnFood();

}

// handle user input
void Level::handleInput(float dt)
{

	if (m_input.isLeftMousePressed())
	{
		std::cout << "left mouse pressed" << std::endl;
		spawnFood();
	}

	if (m_isGameOver) 
	{
		if (m_input.isKeyDown(sf::Keyboard::Scancode::R)){
			m_isGameOver = false;
			m_score = 0;
			m_timer = 0;
			m_speed = 100;
			m_scoreText.setString(to_string(m_score));
			m_player.setPosition({ 400,400 });
		}
	}

	

	if (m_input.isKeyDown(sf::Keyboard::Scancode::W) || m_input.isKeyDown(sf::Keyboard::Scancode::Up))
	{		
		m_direction = Direction::Up;
	}

	if (m_input.isKeyDown(sf::Keyboard::Scancode::S) || m_input.isKeyDown(sf::Keyboard::Scancode::Down))
	{
		m_direction = Direction::Down;
	}

	if (m_input.isKeyDown(sf::Keyboard::Scancode::A) || m_input.isKeyDown(sf::Keyboard::Scancode::Left))
	{
		m_direction = Direction::Left;
	}

	if (m_input.isKeyDown(sf::Keyboard::Scancode::D) || m_input.isKeyDown(sf::Keyboard::Scancode::Right))
	{
		m_direction = Direction::Right;
	}

}

// Update game objects
void Level::update(float dt)
{

	if (m_isGameOver) 
	{
		return;
	}

	m_timer += dt;

	float position = m_speed * dt;

	switch (m_direction)
	{
	case Direction::Up:
		m_player.move({ 0, -position });
		break;
	case Direction::Down:
		m_player.move({ 0, position });
		break;
	case Direction::Left:
		m_player.move({ -position, 0 });
		break;
	case Direction::Right:
		m_player.move({ position, 0 });
		break;
	}

	if (m_player.getPosition().x  >= m_window.getSize().x || m_player.getPosition().x - m_player.getRadius() <= 0 || m_player.getPosition().y >= m_window.getSize().y || m_player.getPosition().y - m_player.getRadius() <= 0)
	{
		m_isGameOver = true;
		cout << "Game Over" << endl;
		cout << "Score: " << m_score << endl;
		cout << "Time Taken: " << m_timer << "sec" << endl;
		cout << "Press R to Restart" << endl;
		m_gameOverText.setString("       Game Over\n \nScore: " + to_string(m_score) + "\n\nTime Taken: " + to_string(m_timer) + " sec\n\nPress R to Restart");
		m_gameOverText.setPosition({ 150,100 });
		m_gameOverText.setStyle(sf::Text::Bold);
		m_gameOverText.setCharacterSize(50);
	}


	// Collide with food -- we already have pos and radius for the snake
	float x_dist = (m_player.getPosition().x + 15) - (m_food.getPosition().x + m_food.getRadius());
	float y_dist = (m_player.getPosition().y + 15) - (m_food.getPosition().y + m_food.getRadius());

	float squared_dist = (x_dist * x_dist) + (y_dist * y_dist);
	float radii_sum = 15 + m_food.getRadius();
	if (squared_dist < radii_sum * radii_sum)
	{
		// they are colliding
		spawnFood();
		m_speed *= 1.1f;
		m_score++;
		m_scoreText.setString(to_string(m_score));
		m_scoreText.setPosition({ 230,55 });
		m_scoreText.setStyle(sf::Text::Bold);
		m_scoreText.setCharacterSize(50);
		std::cout << m_speed << std::endl;
	}
}

// Render level
void Level::render()
{
	if (m_isGameOver) 
	{
		beginDraw();
		m_window.draw(m_gameOverText);
		endDraw();
		return;
	}
	beginDraw();
	m_window.draw(m_text);
	m_window.draw(m_scoreText);
	m_window.draw(m_player);
	m_window.draw(m_food);
	endDraw();
}

void Level::spawnFood()
{
	float posX = rand() % m_window.getSize().x;
	float posY = rand() % m_window.getSize().y;

	m_food.setPosition({ posX,posY });
}


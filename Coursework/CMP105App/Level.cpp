#include "Level.h"

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{
	// initialise game objects
	m_player.setRadius(15);
	m_player.setFillColor(sf::Color::Green);
	m_player.setPosition({ 400,400 });

	m_food.setRadius(10);
	m_food.setFillColor(sf::Color::Red);

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
		m_player.setPosition({ 400,400 });
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
		std::cout << m_speed << std::endl;
	}
}

// Render level
void Level::render()
{
	beginDraw();
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


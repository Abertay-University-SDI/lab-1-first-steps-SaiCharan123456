#include "Level.h"

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{
	// initialise game objects
	m_player.setRadius(15);
	m_player.setFillColor(sf::Color::Green);
	m_player.setPosition({ 400,400 });

}

// handle user input
void Level::handleInput(float dt)
{

	if (m_input.isLeftMousePressed())
	{
		std::cout << "left mouse pressed" << std::endl;
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

	if (m_input.isKeyDown(sf::Keyboard::Scancode::LShift))
	{
		m_speed = 500;
	}
	else {
		m_speed = 100;
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
}

// Render level
void Level::render()
{
	beginDraw();
	m_window.draw(m_player);
	endDraw();
}


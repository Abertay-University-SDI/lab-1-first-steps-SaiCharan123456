#pragma once

#include "Framework/BaseLevel.h"

class Level : BaseLevel{
public:
	Level(sf::RenderWindow& window, Input& input);
	~Level() override = default;

	void handleInput(float dt) override;
	void update(float dt);
	void render();

private:
	
	enum class Direction {Up, Down, Left, Right};

	// Default functions for rendering to the screen.
	void spawnFood();

	// Default variables for level class.
	sf::Font m_font;
	sf::Text m_text;
	sf::Text m_scoreText;
	sf::Text m_gameOverText;
	sf::CircleShape m_player;
	sf::CircleShape m_food;
	float m_speed = 100;
	bool m_isGameOver = false;
	int m_score = 0;
	float m_timer = 0;
	Direction m_direction;
	
};
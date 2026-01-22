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

	// Default variables for level class.
	sf::CircleShape m_player;
	float m_speed = 100;
	Direction m_direction;
	
};
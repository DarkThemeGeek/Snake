#pragma once

#include "Color.hpp"
#include "input.hpp"
#include <Rectangle.hpp>
#include <Vector2.hpp>
#include <Window.hpp>
#include <deque>
#include <raylib.h>
#include <vector>
#define nrSquaresLength 20
// Snake class
class Snake {
  public:
	float width, height;
	// the grids that the body occupies
	std::deque<raylib::Vector2> bodyPositions;
	// length
	int length = 0;
	// Color of the snake
	raylib::Color color; // SNake color
	// Direction the snake is going each tick direction
	///     -1
	/// -1       1
	///      1
	raylib::Vector2 direction;
	void update();

	void drawSnake();

	void increaseSize(raylib::Vector2 pos);

};
class Fruit {
  public:
	float width, height;
	raylib::Vector2 position;
	raylib::Color color;

	float radius;

	void draw() {
		DrawCircle((position.x )+ width / 2, (position.y )+ height / 2, radius,
				   YELLOW);
	}

};
class SnakeGame {
	float width, height;
	Input input{snake.direction};
	std::vector<Fruit> fruits;

  public:
	raylib::Window &window;
	SnakeGame(raylib::Window &window) : window(window) {
		width = window.GetSize().GetX() / nrSquaresLength;
		height = window.GetSize().GetY() / nrSquaresLength;

		input.width = width;
		input.height = height;

		snake.width = width;
		snake.height = height;

		snake.increaseSize({0, 0});
	};
	struct Tile {
		raylib::Rectangle rect;
		raylib::Color color;
	};

	Tile grid[nrSquaresLength][nrSquaresLength];

	Snake snake{};

	int ticks;
	// begins code execution
	void start();
	// basic update function
	void update();
	// increases size of snake if it eats a fruit
	void CheckForFruit();
	void SpawnFruit();
	// functions to run once
	void Init();

	void makeGrid();
	// functions to draw
	void draw();
	void drawGrid();
    void drawFruits();
};

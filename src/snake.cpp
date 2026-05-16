#include "snake.hpp"
#include "Ray.hpp"
#include "Window.hpp"
#include <Rectangle.hpp>
#include <Vector2.hpp>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <raylib.h>
#include <vector>
int main() {
	raylib::Window window{800, 600, "Snake"};
	SnakeGame game{window};
	game.start();
}
void SnakeGame::start() {
	Init();
	while (!window.ShouldClose()) {
		update();

		window.BeginDrawing();
		window.ClearBackground(WHITE);
		draw();

		window.EndDrawing();
	}
}
void SnakeGame::Init() {
	window.SetTargetFPS(60);
	SpawnFruit();
    SpawnFruit();
	makeGrid();
	ticks = 0;
}

void SnakeGame::update() {
	if (ticks > 20) {
		ticks = 0;
		snake.update();
		CheckForFruit();
	}

	input.PoolInput();
	ticks++;
}

void SnakeGame::draw() {
	drawGrid();
	drawFruits();
	snake.drawSnake();
}
void SnakeGame::drawFruits() {
	for (auto &fruit : fruits) {
		fruit.draw();
	}
}
void SnakeGame::makeGrid() {
	// function to draw a checkerBoard
	for (int x = 0; x < nrSquaresLength; x++)
		for (int y = 0; y < nrSquaresLength; y++) {
			if ((x + y) % 2 == 0) {
				grid[x][y].rect =
					raylib::Rectangle(width * x, height * y, width, height);
				grid[x][y].color = GREEN;
			} else {
				grid[x][y].rect =
					raylib::Rectangle(width * x, height * y, width, height);
				grid[x][y].color = DARKGREEN;
			}
		}
}
void SnakeGame::drawGrid() {
	for (int x = 0; x < nrSquaresLength; x++)
		for (int y = 0; y < nrSquaresLength; y++) {
			// std::cout << grid[x][y].rect.x <<" "<< grid[x][y].rect.y
			// 		  <<" "<< grid[x][y].rect.GetHeight()
			// 		  <<" "<< grid[x][y].rect.GetWidth()<<"\n";
			grid[x][y].rect.Draw(grid[x][y].color);
		}
}
void SnakeGame::CheckForFruit() {
	raylib::Vector2 diff;
	bool ok = false;
	for (auto &fruit : fruits) {
	    diff = snake.bodyPositions[0] - fruit.position;
        std::cout<<abs(diff.x/width)<<abs(diff.y/height)<<"\n";
		if (abs(diff.x/width) < 0.5 && abs(diff.y/height) < 0.5) {
			__gnu_cxx::__normal_iterator<Fruit *, std::vector<Fruit>> it =
				fruits.end();
			
			// adding the tail 2 times so it increasesin size
			it = std::find_if(fruits.begin(), fruits.end(), [&](Fruit &f) {
				diff = (f.position - fruit.position);
				return abs(diff.x/width) < 0.5 && abs(diff.y/height) < 0.5;
			});
			if (it != fruits.end()) {
                std::cout<<"works";
				fruits.erase(it);
                snake.increaseSize(snake.bodyPositions.back());
				ok = true;
			}
		}
	}
	if (ok)
		SpawnFruit();
}

void Snake::drawSnake() {
	for (auto &vec : bodyPositions) {
		DrawRectangle(vec.x, vec.y, width, height, RED);
	}
}
void Snake::update() {
	// Moving snake
	bodyPositions.push_front(this->bodyPositions.front() + direction);
	bodyPositions.pop_back();
}
void Snake::increaseSize(raylib::Vector2 vec) {
	bodyPositions.push_back(vec);
	length++;
}
void SnakeGame::SpawnFruit() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, nrSquaresLength-1);

	int x = distrib(gen);
	int y = distrib(gen);
	fruits.push_back(Fruit{width, height, raylib::Vector2{(float)x*width, (float)y*height},
						   RED, (float)height / 2});
}
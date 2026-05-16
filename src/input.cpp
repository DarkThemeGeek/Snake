
#include "input.hpp"
#include <Vector2.hpp>
#include <raylib.h>

void Input::PoolInput() {
	if (IsKeyDown(KeyboardKey::KEY_A)) {
		direction = raylib::Vector2{-1, 0}*width;
	}
	if (IsKeyDown(KeyboardKey::KEY_W)) {
		direction = raylib::Vector2{0, -1}*height;
	}
	if (IsKeyDown(KeyboardKey::KEY_D)) {
		direction = raylib::Vector2{1, 0}*width;
	}
	if (IsKeyDown(KeyboardKey::KEY_S)) {
		direction = raylib::Vector2{0, 1}*height;
	}
}
#pragma once
#include <Vector2.hpp>
class Input {

  public:
	raylib::Vector2 &direction;
	float width;
	float height;
	void PoolInput();
};
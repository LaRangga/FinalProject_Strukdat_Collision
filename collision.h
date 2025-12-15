#pragma once
#include <vector>
#include "ball.h"

float dot(sf::Vector2f a, sf::Vector2f b);
float length(sf::Vector2f v);

void resolveCollision(Ball& a, Ball& b);
void bruteForce(std::vector<Ball*>& balls);

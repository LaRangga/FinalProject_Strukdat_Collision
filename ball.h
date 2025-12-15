#pragma once
#include <SFML/Graphics.hpp>

float randFloat(float a, float b);
sf::Color randColor();

class Ball {
public:
    sf::Vector2f pos, vel;
    float radius, mass;
    sf::Color color;

    Ball(float x, float y);
    void update(float dt, const sf::Vector2u& win);
    void draw(sf::RenderWindow& win);
};

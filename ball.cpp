#include "ball.h"
#include <random>

static std::mt19937 rng(std::random_device{}());

float randFloat(float a, float b) {
    std::uniform_real_distribution<float> d(a, b);
    return d(rng);
}

sf::Color randColor() {
    return sf::Color(
        randFloat(80,255),
        randFloat(80,255),
        randFloat(80,255)
    );
}

Ball::Ball(float x, float y) {
    pos = {x, y};
    radius = randFloat(10, 25);
    vel = {randFloat(-300,300), randFloat(-300,300)};
    mass = radius * radius;
    color = randColor();
}

void Ball::update(float dt, const sf::Vector2u& win) {
    pos += vel * dt;

    if (pos.x - radius < 0) {
        pos.x = radius;
        vel.x *= -1;
    }
    if (pos.x + radius > win.x) {
        pos.x = win.x - radius;
        vel.x *= -1;
    }
    if (pos.y - radius < 0) {
        pos.y = radius;
        vel.y *= -1;
    }
    if (pos.y + radius > win.y) {
        pos.y = win.y - radius;
        vel.y *= -1;
    }
}

void Ball::draw(sf::RenderWindow& win) {
    sf::CircleShape c(radius);
    c.setOrigin(radius, radius);
    c.setPosition(pos);
    c.setFillColor(color);
    win.draw(c);
}

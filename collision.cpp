#include "collision.h"
#include <cmath>

float dot(sf::Vector2f a, sf::Vector2f b) {
    return a.x*b.x + a.y*b.y;
}

float length(sf::Vector2f v) {
    return std::sqrt(dot(v,v));
}

void resolveCollision(Ball& a, Ball& b) {
    sf::Vector2f n = b.pos - a.pos;
    float dist = length(n);
    float minDist = a.radius + b.radius;

    if (dist == 0 || dist >= minDist) return;

    sf::Vector2f normal = n / dist;
    float overlap = minDist - dist;

    a.pos -= normal * (overlap * 0.5f);
    b.pos += normal * (overlap * 0.5f);

    sf::Vector2f rv = b.vel - a.vel;
    float velAlongNormal = dot(rv, normal);

    if (velAlongNormal > 0) return;

    float e = 1.0f;
    float j = -(1 + e) * velAlongNormal / (1/a.mass + 1/b.mass);
    sf::Vector2f impulse = j * normal;

    a.vel -= impulse / a.mass;
    b.vel += impulse / b.mass;
}

void bruteForce(std::vector<Ball*>& balls) {
    for (size_t i = 0; i < balls.size(); i++)
        for (size_t j = i + 1; j < balls.size(); j++)
            resolveCollision(*balls[i], *balls[j]);
}

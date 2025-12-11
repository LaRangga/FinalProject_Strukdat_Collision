#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include <cmath>

struct Ball {
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float radius;

    Ball(float x, float y, float r, sf::Color color, sf::Vector2f vel) {
        radius = r;
        shape.setRadius(radius);
        shape.setFillColor(color);
        shape.setPosition(x, y);
        velocity = vel;
    }

    void move() {
        shape.move(velocity);
    }

    void bounceWindow(int W, int H) {
        sf::Vector2f pos = shape.getPosition();

        if (pos.x < 0 || pos.x + radius*2 > W) velocity.x *= -1;
        if (pos.y < 0 || pos.y + radius*2 > H) velocity.y *= -1;
    }
};

/// ===============================
/// FISIKA TABRAKAN 2 BOLA
/// ===============================
inline bool checkCollision(Ball& A, Ball& B) {
    sf::Vector2f diff = B.shape.getPosition() - A.shape.getPosition();
    float dist = std::sqrt(diff.x*diff.x + diff.y*diff.y);
    return dist < (A.radius + B.radius);
}

inline void resolveCollision(Ball& A, Ball& B) {
    sf::Vector2f posA = A.shape.getPosition();
    sf::Vector2f posB = B.shape.getPosition();

    sf::Vector2f normal = posB - posA;
    float dist = std::sqrt(normal.x*normal.x + normal.y*normal.y);

    if (dist == 0) return;
    normal /= dist;

    sf::Vector2f tangent(-normal.y, normal.x);

    float vA_n = A.velocity.x * normal.x + A.velocity.y * normal.y;
    float vB_n = B.velocity.x * normal.x + B.velocity.y * normal.y;

    float vA_t = A.velocity.x * tangent.x + A.velocity.y * tangent.y;
    float vB_t = B.velocity.x * tangent.x + B.velocity.*_

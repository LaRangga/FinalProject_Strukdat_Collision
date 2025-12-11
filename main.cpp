#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "Ball.h"
#include "Quadtree.h"

#define WIDTH 1000
#define HEIGHT 700

enum Mode { BRUTE_FORCE, QUADTREE };

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Collision Simulation");
    window.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");

    Mode mode = BRUTE_FORCE;
    std::vector<Ball> balls;

    // Add initial balls
    for (int i=0; i<30; i++) {
        balls.emplace_back(rand()%800 + 50, rand()%500 + 50, 10,
            sf::Color::Green, sf::Vector2f((rand()%5)+1, (rand()%5)+1));
    }

    sf::Clock fpsClock;
    float fps = 0;

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();

            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::B) mode = BRUTE_FORCE;
                if (e.key.code == sf::Keyboard::Q) mode = QUADTREE;
            }

            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                balls.emplace_back(e.mouseButton.x, e.mouseButton.y, 10,
                    sf::Color::Red, sf::Vector2f(3,3));
            }
        }

        // ================================================
        // MOVE BALLS
        // ================================================
        for (auto& b: balls) {
            b.move();
            b.bounceWindow(WIDTH, HEIGHT);
        }

        // ================================================
        // COLLISION DETECTION
        // ================================================
        if (mode == BRUTE_FORCE) {
            for (int i=0; i < balls.size(); i++) {
                for (int j=i+1; j < balls.size(); j++) {
                    if (checkCollision(balls[i], balls[j])) {
                        resolveCollision(balls[i], balls[j]);
                    }
                }
            }
        }
        else if (mode == QUADTREE) {
            Quadtree qt(0, {0,0, WIDTH, HEIGHT});

            for (auto& b: balls) qt.insert(&b);

            for (auto& b: balls) {
                std::vector<Ball*> possible;
                qt.retrieve(possible, &b);

                for (auto* other : possible) {
                    if (other != &b && checkCollision(b, *other)) {
                        resolveCollision(b, *other);
                    }
                }
            }
        }

        // ================================================
        // CALCULATE FPS
        // ================================================
        fps = 1.f / fpsClock.restart().asSeconds();

        // ================================================
        // DRAW
        // ================================================
        window.clear();

        for (auto& b : balls) window.draw(b.shape);

        sf::Text text;
        text.setFont(font);
        text.setString("FPS: " + std::to_string((int)fps) +
                       "\nMode: " + (mode == BRUTE_FORCE ? "Brute Force" : "Quadtree") +
                       "\nBalls: " + std::to_string(balls.size()));
        text.setCharacterSize(16);
        text.setFillColor(sf::Color::White);
        text.setPosition(10, 10);
        window.draw(text);

        window.display();
    }
}

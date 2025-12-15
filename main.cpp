#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "ball.h"
#include "collision.h"
#include "quadtree.h"

int main() {
    sf::RenderWindow win(sf::VideoMode(900,600), "Project Strukdat");
    win.setFramerateLimit(144);

    std::vector<Ball*> balls;
    bool useQuadtree = false;

    for(int i=0;i<700;i++)
        balls.push_back(new Ball(randFloat(50,850), randFloat(50,550)));

    sf::Clock clock;
    sf::Font font;
    font.loadFromFile("PixelPowerline.ttf");

    while(win.isOpen()) {
        sf::Event e;
        while(win.pollEvent(e)) {
            if(e.type == sf::Event::Closed) win.close();
            if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
                balls.push_back(new Ball(e.mouseButton.x, e.mouseButton.y));
            if(e.type == sf::Event::KeyPressed) {
                if(e.key.code == sf::Keyboard::B) useQuadtree=false;
                if(e.key.code == sf::Keyboard::Q) useQuadtree=true;
            }
        }

        float dt = clock.restart().asSeconds();
        float fps = 1.f/dt;

        for(auto b:balls) b->update(dt, win.getSize());

        if(!useQuadtree)
            bruteForce(balls);
        else {
            Quadtree qt({0,0,(float)win.getSize().x,(float)win.getSize().y});
            for(auto b:balls) qt.insert(b);

            for(auto b:balls) {
                AABB r{b->pos.x-b->radius*2,b->pos.y-b->radius*2,
                       b->radius*4,b->radius*4};
                std::vector<Ball*> cand;
                qt.query(r,cand);
                for(auto o:cand) if(b!=o) resolveCollision(*b,*o);
            }
        }

        win.clear();
        for(auto b:balls) b->draw(win);

        sf::Text hud(
            "FPS: "+std::to_string((int)fps)+
            "\nBalls: "+std::to_string(balls.size())+
            "\nMODE: "+std::string(useQuadtree?"QUADTREE":"BRUTE FORCE"),
            font,20
        );
        hud.setPosition(10,10);
        win.draw(hud);

        win.display();
    }
}

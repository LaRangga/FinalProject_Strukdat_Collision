#pragma once
#include <vector>
#include "ball.h"

struct AABB {
    float x,y,w,h;
};

bool intersects(const AABB& a, Ball* b);

class Quadtree {
public:
    AABB box;
    int capacity;
    bool divided;

    std::vector<Ball*> objects;
    Quadtree *NE,*NW,*SE,*SW;

    Quadtree(AABB boundary, int cap=4);
    void subdivide();
    void insert(Ball* b);
    void query(const AABB& range, std::vector<Ball*>& found);
};

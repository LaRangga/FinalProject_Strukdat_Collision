#include "quadtree.h"
#include <algorithm>

bool intersects(const AABB& a, Ball* b) {
    float nx = std::max(a.x, std::min(b->pos.x, a.x + a.w));
    float ny = std::max(a.y, std::min(b->pos.y, a.y + a.h));
    float dx = b->pos.x - nx;
    float dy = b->pos.y - ny;
    return dx*dx + dy*dy <= b->radius*b->radius;
}

Quadtree::Quadtree(AABB boundary, int cap)
: box(boundary), capacity(cap), divided(false),
  NE(nullptr), NW(nullptr), SE(nullptr), SW(nullptr) {}

void Quadtree::subdivide() {
    float w = box.w/2, h = box.h/2;
    NE = new Quadtree({box.x+w, box.y, w, h}, capacity);
    NW = new Quadtree({box.x, box.y, w, h}, capacity);
    SE = new Quadtree({box.x+w, box.y+h, w, h}, capacity);
    SW = new Quadtree({box.x, box.y+h, w, h}, capacity);
    divided = true;
}

void Quadtree::insert(Ball* b) {
    if (!intersects(box,b)) return;

    if (objects.size() < (size_t)capacity) {
        objects.push_back(b);
        return;
    }

    if (!divided) subdivide();
    NE->insert(b); NW->insert(b); SE->insert(b); SW->insert(b);
}

void Quadtree::query(const AABB& range, std::vector<Ball*>& found) {
    if (range.x > box.x+box.w || range.x+range.w < box.x ||
        range.y > box.y+box.h || range.y+range.h < box.y)
        return;

    for (auto b : objects)
        if (intersects(range,b)) found.push_back(b);

    if (divided) {
        NE->query(range,found);
        NW->query(range,found);
        SE->query(range,found);
        SW->query(range,found);
    }
}

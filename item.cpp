//
// Created by Atticus Patrick (starter code by Lisa Dion)
//

#include "Shapes/circle.h"
#include "cloud.h"
#include "item.h"
#include "human.h"
#include "Shapes/rect.h"
#include "graphics.h"
#include <ctime>

using namespace std;

Item::Item() {
    // Call non-default constructor
    Item({1, 1, 1}, 0, 0, 50);
}

Item::Item(color fill, int x, int y, int width) {
    dimensions bottom(width, width/8);
    shapes2.push_back(make_unique<Rect>(fill, x, y, bottom));
}

void Item::moveUpAndJumpY(int deltaY, int height, int randInt) {
    for (const unique_ptr<Shape> &s : shapes2) {
        // Move all the shapes by deltaY
        s->moveY(deltaY);
        // If a shape has moved off the screen
        if (s->getBottomY() < 0) {
            // Set it to the bottom of the screen so that it passes through again
            s->setCenterY(height + (s->getBottomY() - s->getTopY()) / 2);
            jumpX(randInt);
        }
    }
}

void Item::jumpX(int randInt) {
    for (const unique_ptr<Shape> &s : shapes2) {
        if (shapes2[0]->getCenterX() > 250) {
            s->setCenterX(s->getCenterX() - randInt);
        }
        else {
            s->setCenterX(s->getCenterX() + randInt);
        }
    }
}

bool Item::isOverlapping(Rect r) {
    if (dynamic_cast<Rect&>(*shapes2[0]).isOverlapping(r)) {
        return true;
    }
    return false;
}

void Item::draw() const {
    for (const unique_ptr<Shape> &s : shapes2) {
        s->draw();
    }
}

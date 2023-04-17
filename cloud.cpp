//
// Created by Lisa Dion on 1/9/23.
//

#include "Shapes/circle.h"
#include "cloud.h"
#include "human.h"
#include "Shapes/rect.h"
#include "graphics.h"
#include <ctime>

using namespace std;

Cloud::Cloud() {
    // Call non-default constructor
    Cloud({1, 1, 1}, 0, 0, 50);
}

Cloud::Cloud(color fill, int x, int y, int width) {
    // width = 80
    // center x = 315
    dimensions bottom(width/2, width/2);
    shapes.push_back(make_unique<Circle>(fill, x-(width/4), y, width/4));
    shapes.push_back(make_unique<Circle>(fill, x+(width/4), y, width/4));
    shapes.push_back(make_unique<Circle>(fill, x+(width/16), y-(width/4), width/4));
    shapes.push_back(make_unique<Rect>(fill, x, y, bottom));
}

void Cloud::moveUpAndJumpY(int deltaY, int height, int randInt) {
    for (const unique_ptr<Shape> &s : shapes) {
        // Move all the shapes by deltaY
        s->moveY(deltaY);
        // If a shape has moved off the screen
        if (s->getBottomY() < 0) {
            // Set it to the bottom of the screen so that it passes through again - Alex Vokey
            s->setCenterY(height + (s->getBottomY() - s->getTopY()) / 2);
            jumpX(randInt);
        }
    }
}

// Alex Vokey
void Cloud::jumpX(int randInt) {
    for (const unique_ptr<Shape> &s : shapes) {
        if (shapes[3]->getCenterX() > 250) {
            s->setCenterX(s->getCenterX() - randInt);
        }
        else {
            s->setCenterX(s->getCenterX() + randInt);
        }
    }
}

bool Cloud::isOverlapping(Rect r) {
    // This method only checks the Rect object in the Cloud
    if (dynamic_cast<Rect&>(*shapes[3]).isOverlapping(r)) {
        return true;
    }
    return false;
}

void Cloud::draw() const {
    for (const unique_ptr<Shape> &s : shapes) {
        s->draw();
    }
}

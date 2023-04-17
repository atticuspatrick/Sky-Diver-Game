#include "human.h"

Human::Human() {
    color bodyFill(0, .5, 1), limbFill(1, .5, 0), headFill(.75, .5, 0);
    int x = 250, y = 100;
    dimensions limbSize(5, 25);
    dimensions bodySize(50, 8);
    dimensions headSize(12, 12);

    shapes.push_back(std::make_unique<Rect>(limbFill, x-25, y-12, limbSize));
    shapes.push_back(std::make_unique<Rect>(limbFill, x-17, y-12, limbSize));
    shapes.push_back(std::make_unique<Rect>(limbFill, x+10, y-12, limbSize));
    shapes.push_back(std::make_unique<Rect>(limbFill, x+18, y-12, limbSize));
    shapes.push_back(std::make_unique<Rect>(bodyFill, x, y, bodySize));
    shapes.push_back(std::make_unique<Rect>(headFill, x+25, y-3, headSize));
}

Rect Human::getBody() const {
    return *shapes[4];
}

double Human::getLeftX() const {
    return shapes[0]->getCenterX() - 5;
}

double Human::getRightX() const {
    return shapes[5]->getCenterX() + 5;
}

double Human::getCenterX() const {
    return shapes[4]->getCenterX();
}

void Human::setCenterX(double x) {
    shapes[0]->setCenterX(x - 25);
    shapes[1]->setCenterX(x - 17);
    shapes[2]->setCenterX(x + 10);
    shapes[3]->setCenterX(x + 18);
    shapes[4]->setCenterX(x);
    shapes[5]->setCenterX(x + 25);
}

void Human::draw() const {
    for (const unique_ptr<Rect> &s: shapes) {
        s->draw();
    }
}
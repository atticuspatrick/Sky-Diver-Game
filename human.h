//
// Created by Alex Vokey
//
#include "Shapes/circle.h"
#include "Shapes/rect.h"
#include <memory>
#include <vector>
using std::vector;
using std::unique_ptr;

class Human {
private:
    vector<unique_ptr<Rect>> shapes;

public:
    // Constructor
    Human();

    // Returns true if any shape in the cloud overlaps with s; returns false otherwise
//    bool isOverlapping(Rect& r);

    // Getters
    Rect getBody() const;
    double getLeftX() const;
    double getRightX() const;
    double getCenterX() const;

    // Setters
    void setCenterX(double x);

    // Draw
    void draw() const;
};


#endif //M4OEP_HUMAN_H

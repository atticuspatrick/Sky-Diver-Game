//
// Created by Lisa Dion on 1/9/23.
//

#include "human.h"
#include "Shapes/rect.h"
#include <memory>
#include <vector>
using std::vector;
using std::unique_ptr;

class Cloud {
private:
    vector<unique_ptr<Shape>> shapes;

public:
    // Constructors
    Cloud();
    Cloud(color fill, int x, int y, int width);

    // Move all shapes' x-values by the delta and jump the shapes that are fully negative x-values to be greater than width
    void moveUpAndJumpY(int deltaY, int height, int randInt);

    // Move clouds by random amount
    void jumpX(int randInt);

    // Returns true if any shape in the cloud overlaps with r; returns false otherwise
    bool isOverlapping(Rect r);

    // Draw the cloud
    void draw() const;
};


#endif

//
// Created by Atticus Patrick (starter code by Lisa Dion)
//

#include "human.h"
#include "Shapes/rect.h"
#include <memory>
#include <vector>
using std::vector;
using std::unique_ptr;

class Item {
private:
    vector<unique_ptr<Shape>> shapes2;

public:
    // Constructors
    Item();
    Item(color fill, int x, int y, int width);

    // Move all shapes' x-values by the delta and jump the shapes that are fully negative x-values to be greater than width
    void moveUpAndJumpY(int deltaY, int height, int randInt);

    // Move items to a random location
    void jumpX(int randInt);

    // Returns true if any shape in the item overlaps with r; returns false otherwise
    bool isOverlapping(Rect r);

    // Draw the item
    void draw() const;
};


#endif

//
// Starter code by Lisa Dion
//

#include "graphics.h"
#include "human.h"
#include "Shapes/circle.h"
#include "cloud.h"
#include "Shapes/rect.h"
#include <iostream>
#include <memory>
#include <vector>
#include <ctime>
#include "item.h"
using namespace std;

GLdouble width, height;
int wd, speed, startTime, currentTime;
int lives = 3;
int gracePeriod = 0;
int gracePeriod2 = 0;
string speedLabel, liveMessage;
const color skyBlue(77/255.0, 213/255.0, 240/255.0);
const color grassGreen(26/255.0, 176/255.0, 56/255.0);
const color white(1, 1, 1);
const color brickRed(201/255.0, 20/255.0, 20/255.0);
const color darkBlue(1/255.0, 110/255.0, 214/255.0);
const color purple(119/255.0, 11/255.0, 224/255.0);
const color black(0, 0, 0);
const color magenta(1, 0, 1);
const color orange(1, 163/255.0, 22/255.0);
const color cyan (0, 1, 1);

vector<Cloud> cloudVec;
vector<Item> itemVec;
Human user;

//Enumerated type screen with START,GAME,END and INFO
enum Screen {
    START,
    GAME,
    END,
    INFO
};

Screen currentScreen = START;

void initClouds() {
    cloudVec.clear();
    // Note: the Rect objects that make up the flat bottom of the clouds
    // won't appear until you implement the Rect::draw method.
    cloudVec.push_back(Cloud(white, 100, 200, 100));
    cloudVec.push_back(Cloud(white, 300, 380, 80));
    cloudVec.push_back(Cloud(white, 445, 450, 80));
    speed = -5;
    speedLabel = "Speed: " + to_string(speed * -1) + "  ";
    liveMessage = " Lives: " + to_string(lives);
}

void initItems() {
    itemVec.clear();
    // Note: the Rect objects that make up the flat bottom of the clouds
    // won't appear until you implement the Rect::draw method.
    itemVec.push_back(Item(brickRed, 155, 120, 40));
    itemVec.push_back(Item(brickRed, 375, 400, 40));
    speed = -5;
}

void initUser() {
    Human();
}

void init() {
    width = 500;
    height = 500;
    srand(time(0));
    initClouds();
    initItems();
    initUser();
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(skyBlue.red, skyBlue.green, skyBlue.blue, 1.0f);
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE (unless you are running Catalina on Mac)
    
    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

    // Display Screens - Atticus Patrick
    // Display start screen if currentScreen is START
    // Displays multiple options for the user
    if (currentScreen == START) {
        for (Cloud &c : cloudVec) {
            c.draw();
        }
        glBegin(GL_QUADS);
        glColor3f(skyBlue.red, skyBlue.green, skyBlue.blue);
        glVertex2i(0, 0);
        glVertex2i(0, 30);
        glVertex2i(500, 30);
        glVertex2i(500, 0);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(skyBlue.red, skyBlue.green, skyBlue.blue);
        glVertex2i(0, 470);
        glVertex2i(0, 500);
        glVertex2i(500, 500);
        glVertex2i(500, 470);
        glEnd();

        string message = "Welcome to SkyDiver!";
        glColor3f(0, 0.1, 0.7);
        glRasterPos2i(160, 225);
        for (char letter : message) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
        string message2 = "Press 'i' for info";
        glColor3f(0, 0.1, 0.7);
        glRasterPos2i(175, 250);
        for (char letter : message2) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
        string message3 = "Press 'b' to begin";
        glColor3f(0, 0.1, 0.7);
        glRasterPos2i(175, 275);
        for (char letter : message3) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
    }

    //Info screen gives the user info about the game
    if (currentScreen == INFO) {
        string message4 = "In this game you are a sky diver trying to survive";
        glColor3f(0, 0.1, 0.7);
        glRasterPos2i(0, 150);
        for (char letter : message4) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
        string message5 = "for as long as possible. You have three lives. Avoid";
        glColor3f(0, 0.1, 0.7);
        glRasterPos2i(0, 175);
        for (char letter : message5) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
        string message6 = "clouds and pick up red items to slow down. Press";
        glColor3f(0, 0.1, 0.7);
        glRasterPos2i(0, 200);
        for (char letter : message6) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
        string message7 = "'s' in game to increase speed (for a challenge!)";
        glColor3f(0, 0.1, 0.7);
        glRasterPos2i(0, 225);
        for (char letter : message7) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
        string message8 = "Press 'm' for the start menu";
        glColor3f(0, 0.1, 0.7);
        glRasterPos2i(0, 275);
        for (char letter : message8) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
        string message9 = "Press 'b' to begin";
        glColor3f(0, 0.1, 0.7);
        glRasterPos2i(0, 300);
        for (char letter : message9) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
    }

    //Starts the game - Anthony Mazzola
    // Has clouds that must be avoided
    //User moves either left or right
    //3 lives given
    //Speed increases every 5 seconds
    if (currentScreen == GAME) {
        for (Cloud &c : cloudVec) {
            c.draw();
        }
        for (Item &i : itemVec) {
            i.draw();
        }
        glBegin(GL_QUADS);
        glColor3f(skyBlue.red, skyBlue.green, skyBlue.blue);
        glVertex2i(0, 0);
        glVertex2i(0, 30);
        glVertex2i(500, 30);
        glVertex2i(500, 0);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(skyBlue.red, skyBlue.green, skyBlue.blue);
        glVertex2i(0, 470);
        glVertex2i(0, 500);
        glVertex2i(500, 500);
        glVertex2i(500, 470);
        glEnd();

        user.draw();

        glColor3f(0, 0.1, 0.7);
        glRasterPos2i(25, 485);

        currentTime = time(0);
        // only change speed if between -20 and -4
        if (currentTime > startTime + 5 && speed > -20 && speed < -4) {
            speed -= 1;
            startTime = currentTime;
            speedLabel = "Speed: " + to_string(speed * -1) + "  ";
        }

        for (const char &letter : speedLabel) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        for (char letter : liveMessage) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        // Check if the user is overlapping with the clouds
        // If they are overlapping, lower the life and then start the grace period
        // grace period is there so lives don't go down instantly
        // Create new liveMessage and end the game if lives are 0

        for (Cloud& c : cloudVec) {
            if (c.isOverlapping(user.getBody())) {
                if (gracePeriod == 0){
                    gracePeriod += 1;
                    gracePeriod2 = time(0);
                    lives -= 1;
                }
                if (time(0) >= (gracePeriod2 + 5)) {
                    gracePeriod = 0;
                }
                liveMessage = " Lives: " + to_string(lives);
                if (lives == 0) {
                    currentScreen = END;
                }
            }
        }

        // Check if the user is overlapping with the items
        // If they are overlapping, slow speed
        for (Item& i : itemVec) {
            int currspeed = speed;
            // only decrement speed if the speed is from -1 to -20
            if (i.isOverlapping(user.getBody()) && speed > -21 && speed < -5) {
                speed = currspeed + 1;
                speedLabel = "Speed: " + to_string(speed * -1) + "  ";
            }
        }
    }

    //End screen
    //Gives user multiple options
    //Can quit play again
    //Return to main menu
    if (currentScreen == END) {
        string message = "Game Over! Press 'q' to quit";
        glColor3f(0, 0.1, 0.7);
        glRasterPos2i(125, 225);
        for (char letter : message) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
        string message2 = "Press 'm' for the start menu";
        glColor3f(0, 0.1, 0.7);
        glRasterPos2i(125, 250);
        for (char letter : message2) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
        string message3 = "Press 'b' to play again";
        glColor3f(0, 0.1, 0.7);
        glRasterPos2i(125, 275);
        for (char letter : message3) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
    }

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
//Multiple if statements that handle the different input from the user
//The user can press different keyboard inputs and will get a different output dependant on which state you are currently in
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    // Set max speed of -20 and min speed of -1
    else if (key == 's' && currentScreen == GAME && speed > -20 && speed < 0) {
        speed -= 1;
    }

    if (currentScreen == START && key == 'b') {
        startTime = time(0);
        currentScreen = GAME;
    }

    if (currentScreen == START && key == 'i') {
        currentScreen = INFO;
    }

    if (currentScreen == INFO && key == 'm') {
        currentScreen = START;
    }

    if (currentScreen == INFO && key == 'b') {
        currentScreen = GAME;
    }

    if (currentScreen == END && key == 'm') {
        lives = 3;
        speed = -1;
        speedLabel = "Speed: " + to_string(speed * -1) + "  ";
        liveMessage = " Lives: " + to_string(lives);
        currentScreen = START;
    }

    if (currentScreen == END && key == 'b') {
        lives = 3;
        speed = -5;
        speedLabel = "Speed: " + to_string(speed * -1) + "  ";
        liveMessage = " Lives: " + to_string(lives);
        startTime = time(0);
        currentScreen = GAME;
    }

    if (currentScreen == END && key == 'q') {
        glutDestroyWindow(wd);
        exit(0);
    }
    speedLabel = "Speed: " + to_string(speed * -1);
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            
            break;
        case GLUT_KEY_LEFT:
            if (user.getLeftX() > 1) {
                user.setCenterX(user.getCenterX() - 5);
            }
            break;
        case GLUT_KEY_RIGHT:
            if (user.getRightX() < width - 1) {
                user.setCenterX(user.getCenterX() + 5);
            }
            break;
        case GLUT_KEY_UP:
            
            break;
    }
    
    glutPostRedisplay();
}

void cursor(int x, int y) {

    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    glutPostRedisplay();
}

void cloudTimer(int dummy) {
    int randInt;
    for (Cloud& c : cloudVec) {
        randInt = rand() % 250 + 1;
        c.moveUpAndJumpY(speed, height, randInt);
    }
    
    glutPostRedisplay();
    glutTimerFunc(50, cloudTimer, dummy);
}

void itemTimer(int dummy) {
    int randInt2;
    for (Item& i : itemVec) {
        randInt2 = rand() % 250 + 1;
        i.moveUpAndJumpY(speed, height, randInt2);
    }

    glutPostRedisplay();
    glutTimerFunc(50, itemTimer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    
    init();
    
    glutInit(&argc, argv);          // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGBA);
    
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(200, 100); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Runner" /* title */ );
    
    // Register callback handler for window re-paint event
    glutDisplayFunc(display);
    
    // Our own OpenGL initialization
    initGL();
    
    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);
    
    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);
    
    // handles mouse movement
    glutPassiveMotionFunc(cursor);
    
    // handles mouse click
    glutMouseFunc(mouse);
    
    // handles timer
    glutTimerFunc(0, cloudTimer, 0);
    glutTimerFunc(0, itemTimer, 0);
    
    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}

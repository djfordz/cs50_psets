//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3


// height and width of paddle
#define PHEIGHT 7
#define PWIDTH 60

// height and width of brick
#define BHEIGHT 12
#define BWIDTH 35

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball, GCompound brickSet);
void movePaddle(GWindow window, GRect paddle);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);
    

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

     // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // Add objects to window.
    add(window, ball);
    add(window, paddle);
    add(window, label);
    add(window, brick);

    // instantiate velocity variables
    double dy =0.200;
    double dx = 0.200 * drand48();
    
    // keep playing until game over
    while(lives > 0 && bricks > 0)
    {   
        // Instantiate paddle move.
        movePaddle(window, paddle);

        // move ball.
        move(ball, dx, dy);
       
       // change direction of ball when ball reaches edge of window
        if(getY(ball) + getHeight(ball) >= getHeight(window))
        {
            setLocation(ball, (WIDTH / 2) - RADIUS, (HEIGHT / 2) - RADIUS);
            lives--;
        }
        else if(getX(ball) + getWidth(ball) >= getWidth(window))
        {
            dx = -dx;
        }
        else if(getY(ball) <= 0)
        {
            dy = -dy;
        }
        else if(getX(ball) <= 0)
        {
            dx = -dx;
        }

        // instantiate object at ball coordinates.
        GObject object = detectCollision(window, ball, brickSet);
        //GObject brick = getGObject(brick, getX(ball), getY(ball));

        
        if(object != NULL)
        {
            // if ball contacts paddle change direction of ball.
            if(object == paddle)
            {
                dy = -dy;
            }
            // if ball contacts brick remove brick, update scoreboard and change direction of ball.
            else if(object == brick)
            {
                points++;
                bricks--;
                removeGCompound(brickSet, brick);
                dy = -dy;
                updateScoreboard(window, label, points);
            }
        }

        // slow animation down to a playable level.
        //pause(3);

    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // initialize arrays.
    char* color[ROWS] = {"RED", "GREEN", "ORANGE", "YELLOW", "BLUE"};

    // build rows of bricks.
    for(int i = 5; i < ROWS; i += BWIDTH + 4)
    {
        for(int j = 50; j < COLS + 50; j += BHEIGHT + 4)
        {
                GRect brick = newGRect(i, j + (BHEIGHT * k) + (k * 4), BWIDTH, BHEIGHT);
                setFilled(brick, true);
                setColor(brick, "WHITE");
                setFillColor(brick[k], color[k]);
                add(window, brick);         
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval *ball = newGOval((WIDTH / 2) - RADIUS, (HEIGHT / 2) - RADIUS, 2 * RADIUS, 2 * RADIUS);
    setFilled(ball, true);
    setFillColor(ball, "BLACK");
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect((WIDTH / 2) - (PWIDTH / 2), HEIGHT - 50, PWIDTH, PHEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    char* s = "0";

    // create label
    GLabel label = newGLabel(s);
    setFont(label, "Helvetica-40");
    setColor(label, "#AAAAAA");

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);

    return label;
}

/**
 * Moves the paddle along the x-axis with the mouse.
 */
void movePaddle(GWindow window, GRect paddle)
{
    // Initialize event
    GMouseEvent setPaddle = getNextEvent(MOUSE_MOVED);

    // check
    if(setPaddle != NULL)
    {
        // moving mouse moves paddle across x-axis
        if(getEventType(setPaddle) == MOUSE_MOVED)
        {
            // initialize variables
            double moveX = getX(setPaddle);
            double y = getY(paddle);

            // keep within window
            if(moveX >= 0 && moveX <= WIDTH - PWIDTH)
            {
                setLocation(paddle, moveX, y);
            }
        }
    }
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball, GCompound brickSet)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner on z plane
    object = getGObjectCompound(brickSet, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-left corner on z-plane
    object = getGObjectCompound(brickSet, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

     // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner on z-plane
    object = getGObjectCompound(brickSet,  x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

     // check for collision at ball's bottom-right corner on z-plane
    object = getGObjectCompound(brickSet, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}

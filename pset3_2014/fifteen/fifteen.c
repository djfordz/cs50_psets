/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
static int d;

// prototypes
void clear(void);
void greet(void);
int init(int board[][d], int d);
void draw(int board[][d], int d);
bool move(int tile, int board[][d], int d);
bool won(int board[][d], int d);
void save(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    int board[d][d];
    init(board, d);

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw(board, d);

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won(board, d))
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile, board, d))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
int init(int board[][d], int d)
{
    // Initialize variables.
    int i, j;
    int count = d * d - 1;

    // iterate backwards through count and save on board.
    for(i = 0; i < d; i++)
    {
        for(j = 0; j < d; j++)
        {
            board[i][j] = count;
            count--;
        }
    }
    // create character for empty space.
    board[d - 1][d - 1] = '_';

    // Swap 1 an 2 on odd boards.
    if(d % 2 == 0)
            {
                board[d - 1][d - 2] = 2;
                board[d - 1][d - 3] = 1;
            }

    return **board;
}

/**
 * Prints the board in its current state.
 */
void draw(int board[][d], int d)
{
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            // print escape character at empty position.
            if (board[i][j] == '_')
            {
                int _ = '_';
                printf("%2c ", _);
            }
            else
                printf("%2d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile, int board[][d], int d)
{
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            // Ensure tile is on board and swap as necessary.
            if (board[i][j] == tile)
            {
                if (board[i + 1][j] == '_')
                {
                    board[i][j] = '_';
                    board[i + 1][j] = tile;
                    return true;
                }
                else if (board[i][j + 1] =='_')
                {
                    board[i][j] = '_';
                    board[i][j + 1] = tile;
                    return true;
                }
                else if (board[i -1][j] == '_')
                {
                    board[i][j] = '_';
                    board[i - 1][j] = tile;
                    return true;
                }
                else if (board[i][j - 1] == '_')
                {
                    board[i][j] = '_';
                    board[i][j - 1] = tile;
                    return true;
                }
            } 
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(int board[][d], int d)
{
    // Initialize variables.
    int values[d * d - 1];
    int k = 1;

   for (int i = 0; i < d; i++)
   {
        for (int j = 0; j < d; j++)
        {
            // Save count in array.
            values[j] = k;
            
            // Test board against count.
            printf("%d,  %d\n", board[i][j], values[j]);
            if(board[i][j] < values[j])
            {
               return false;
            }
            
            // iterate count.
            k++;
        }
    }

    return true;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}

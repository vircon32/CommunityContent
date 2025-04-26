// include Vircon libraries
#include "video.h"
#include "math.h"
#include "time.h"
#include "input.h"
#include "misc.h"


#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 360
#define PIPE_COUNT    4
#define PIPE_SPACING  160
#define PIPE_SPEED 2
#define GAP_HEIGHT    60
#define BIRD_X        140


struct Pipe{
		int x;
		int gapY;
		bool scored;
	};
	
Pipe[PIPE_COUNT] pipes;

float birdY = 100.0;
float velocity = 0.0;
float gravity = 0.5;
float flapStrength = -6.0;

bool isAlive = true;

int score = 0;
int maxScore = 0;

int[12] numberBuffer; 

void init_pipes()
{
    for (int i = 0; i < PIPE_COUNT; i++)
    {
        pipes[i].x = SCREEN_WIDTH + i * PIPE_SPACING;
        pipes[i].gapY = 40 + (rand() % (SCREEN_HEIGHT - GAP_HEIGHT - 80));
    }
}


void update_pipes()
{
    for (int i = 0; i < PIPE_COUNT; i++)
    {
        pipes[i].x -= PIPE_SPEED;

        // Reset when offscreen
        if (pipes[i].x < -8)
        {
            pipes[i].x = SCREEN_WIDTH;
            pipes[i].gapY = 40 + (rand() % (SCREEN_HEIGHT - GAP_HEIGHT - 80));
			pipes[i].scored = false;
        }
    }
}

void draw_pipe(Pipe* pipe)
{
    for (int y = 0; y < SCREEN_HEIGHT; y += 8)
    {
        if (y < pipe->gapY || y > pipe->gapY + GAP_HEIGHT)
        {
            set_drawing_point(pipe->x, y);
            print("|");
        }
    }
}

void int_to_string(int value, int* buffer)
{
    // Handle 0 as a special case
    if (value == 0)
    {
        buffer[0] = '0';
        buffer[1] = 0;
        return;
    }

    // Handle negative numbers
    int isNegative = 0;
    if (value < 0)
    {
        isNegative = 1;
        value = -value;
    }

    int[10] digits; // max 10 digits
    int length = 0;

    // Extract digits in reverse order
    while (value > 0)
    {
        digits[length++] = '0' + (value % 10);
        value /= 10;
    }

    int i = 0;

    // Add minus sign if needed
    if (isNegative)
        buffer[i++] = '-';

    // Copy digits in correct order
    for (int j = length - 1; j >= 0; j--)
        buffer[i++] = digits[j];

    buffer[i] = 0; // null terminator
}

void main( void )
{   

	init_pipes();

    while (true)
    {
		int ButtonA = gamepad_button_a();
		
		if (isAlive)
		{
			clear_screen(color_black);
			
			if (ButtonA == 1)
				velocity = flapStrength;
			
			velocity += gravity;
			birdY += velocity;
			
			// Keep bird on screen
			if (birdY < 0) birdY = 0;
			if (birdY > SCREEN_HEIGHT - 8) birdY = SCREEN_HEIGHT - 8;
			
			// Update pipes
			update_pipes();
			
			
			//Check collisions
			for (int i = 0; i < PIPE_COUNT; i++)
			{
				int pipeLeft = pipes[i].x;
				int pipeRight = pipeLeft + 4;  // Approximate width of "|"

				// Check if bird is inside the X range of pipe
				if (BIRD_X >= pipeLeft && BIRD_X <= pipeRight)
				{
					int birdTop = (int)birdY;
					int birdBottom = birdTop + 8;

					int gapTop = pipes[i].gapY;
					int gapBottom = gapTop + GAP_HEIGHT;

					// If bird not in gap, it hit the pipe
					if (birdTop < gapTop || birdBottom > gapBottom)
						isAlive = false;
				}
			}

			for (int i = 0; i < PIPE_COUNT; i++)
			{
				if (!pipes[i].scored && pipes[i].x + 4 < BIRD_X)
				{
					pipes[i].scored = true;
					score++;
				}
			}

			// Check top/bottom of screen
			if (birdY <= 0 || birdY >= SCREEN_HEIGHT - 8)
				isAlive = false;
			
			
			// Draw pipes
			for (int i = 0; i < PIPE_COUNT; i++)
				draw_pipe(&pipes[i]);

			// Draw bird
			set_drawing_point(BIRD_X, (int)birdY);
			print(">");
			
			int_to_string(score, numberBuffer);

			set_drawing_point(10, 10);
			print("Score:");

			set_drawing_point(70, 10);
			print(numberBuffer);
			
			int_to_string(maxScore, numberBuffer);

			set_drawing_point(10, 25);
			print("Highscore:");

			set_drawing_point(110, 25);
			print(numberBuffer);
			
			
		}
		else
		{
			if(score > maxScore)
			{
				maxScore = score;
			}
			
			score = 0;
			
			set_drawing_point(120, 100);
			print("Game Over");

			set_drawing_point(100, 120);
			print("Press A to restart");

			if (ButtonA == 1)
			{
				// Reset game state
				birdY = 100;
				velocity = 0;
				isAlive = true;
				init_pipes();
			}
		}

        end_frame();
    }
   
}




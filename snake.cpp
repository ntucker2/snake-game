// Nora Tucker - CSE 20311 - Lab 13 - snake.cpp
// The purpose of this lab is to demonstrate overall competence in using C++
// and to gain experience in designing a program from beginning to end.

// This is the implementation of the snake class. It updates the direction
// and speed, moves (after checking if food or a wall is in the way, based
// on direction, and displays a lose screen if you lost. It also eats and 
// moves the food to a random location. Finally, there is a rectangle
// function that just plots a rectangle and then a function that displays
// the whole board (outer border, food, and snake).

#include "gfx.h"
#include "snake.h"
#include <string>
#include <stdlib.h> // for rand and srand
#include <time.h>	// for initializing srand with time
#include <unistd.h> // has usleep
#include <iostream> 
#include <cstdio>
using namespace std;

// constructor
Snake::Snake()
{	for(int i = 0; i < 6; i++)
	{
		piece head;
		head.x = xsize * mult / 2 / mult * mult;
		head.y = ((ysize * mult / 2) - mult*i) / mult * mult;
		pieces.push_back(head);
	}
	foodx = 15*mult;
	foody = 25*mult;
//	foodx = 3 * xsize / 4 * mult / mult ;
//	foody = ysize / 4 * mult / mult ;
	size = 6;
	speed = 50000;
	dir = 0;

}

// deconstructor
Snake::~Snake() {}

// updates direction variable
void Snake::changeDir(int din)
{
	dir = din;
}

void Snake::changeSpeed(int sin)
{
	speed = sin;
}

// returns 1 if game had to quit, else returns 0
// moves the snake and calls lose and eat methods as needed
int Snake::move()
{
	switch (dir)
	{
		case UP:
			if(pieces[size-1].y == mult)
			{
				lose();
				return 1;
			}
			else if (pieces[size-1].x == foodx && pieces[size-1].y - mult == foody)
				eat();
			else
			{
				bool hitsself = false;
				for(int i = 1; i < size; i++)	
				{
					if((pieces[size-1].x == pieces[i].x) &&(pieces[size-1].y - mult == pieces[i].y))
						hitsself = true;
				}
				if(hitsself)
				{
					lose();
					return 1;
				}
				else
				{
					for(int i = 0; i < size - 1; i++)
					{
						pieces[i].x = pieces[i+1].x;
						pieces[i].y = pieces[i+1].y;
					}
						pieces[size-1].y -= mult;
				}
			}
			break;
		case DOWN:
			if(pieces[size-1].y == ysize*mult - mult)	
			{
				lose();
				return 1;
			}
			else if (pieces[size-1].x == foodx && pieces[size-1].y + mult == foody)
				eat();
			else
			{
				bool hitsself = false;
				for(int i = 1; i < size; i++)	
				{
					if((pieces[size-1].x == pieces[i].x) &&(pieces[size-1].y + mult == pieces[i].y))
						hitsself = true;
				}
				if(hitsself)
				{
					lose();
					return 1;
				}
				else
				{
					for(int i = 0; i < size - 1; i++)
					{
						pieces[i].x = pieces[i+1].x;
						pieces[i].y = pieces[i+1].y;
					}
						pieces[size-1].y += mult;
				}
			}
			break;
		case LEFT:
			if(pieces[size-1].x == mult)
			{
				lose();
				return 1;
			}
			else if (pieces[size-1].x - mult == foodx && pieces[size-1].y == foody)
				eat();
			else
			{
				bool hitsself = false;
				for(int i = 1; i < size; i++)
				{
					if((pieces[size-1].x - mult == pieces[i].x) &&(pieces[size-1].y == pieces[i].y))
						hitsself = true;
				}
				if(hitsself)
				{
					lose();
					return 1;
				}
				else
				{
					for(int i = 0; i < size - 1; i++)
					{
						pieces[i].x = pieces[i+1].x;
						pieces[i].y = pieces[i+1].y;
					}
						pieces[size-1].x -= mult;
				}
			}
			break;
		case RIGHT:
			if(pieces[size-1].x == xsize*mult - mult)
			{
				lose();
				return 1;
			}
			else if (pieces[size-1].x + mult == foodx && pieces[size-1].y == foody) 
				eat();
			else
			{ 
				bool hitsself = false;
				for(int i = 1; i < size; i++)	
				{
					if((pieces[size-1].x + mult == pieces[i].x) &&(pieces[size-1].y == pieces[i].y))
						hitsself = true;
				}
				if(hitsself)
				{ 
					lose();
					return 1;
				}
				else
				{
					for(int i = 0; i < size - 1; i++)
					{
						pieces[i].x = pieces[i+1].x;
						pieces[i].y = pieces[i+1].y;
					} 
						pieces[size - 1].x += mult;
				}
			}
			break;
	}
	return 0;
}

void Snake::lose()
{
	gfx_clear();
	gfx_color(255, 255, 255);
	gfx_text(xsize*mult/2 - 20, ysize*mult/2 - 20, "YOU LOSE");
	string s = "but you got to a size of " + to_string(size) + " pieces!!";
	gfx_text(xsize*mult/2 - 100, ysize*mult/2 + 20, s.c_str());
	gfx_flush();
	usleep(2220000);
}

void Snake::eat()
{
	piece newhead;
	newhead.x = foodx;
	newhead.y = foody;
	pieces.push_back(newhead);
	size++;
	moveFood();
}

void Snake::moveFood()
{
	srand(time(NULL));
	// doing the calculations like this ensures that the food isn't on
	// external border
	int potx = rand() %(xsize*mult - 2*mult) + mult;
	potx = potx / mult * mult;
	int poty = rand() %(ysize*mult - 2*mult) + mult;
	poty = poty / mult * mult;
	bool passed = false;
	while(!passed)
	{
		bool didntwork = false;
		for(int i = 0; i < size; i++)
		{
			if(pieces[i].x == potx && pieces[i].y == poty)
				didntwork = true;
		}
		if (!didntwork)
			passed = true;
		else
		{
			potx = rand() % (xsize*mult - 2*mult) + mult;
			potx = potx / mult * mult;
			poty = rand() % (ysize*mult - 2*mult) + mult;
			poty = poty / mult * mult;
		}
	}
	foodx = potx;
	foody = poty;
}

void Snake::rect(int x1, int y1, int x2, int y2)
{
	for(int i = y1; i <= y2; i++)
		gfx_line(x1, i, x2, i);
}

void Snake::print()
{
	// clear screen
	gfx_clear();

	// first set color to blue and print border
	gfx_color(0, 0, 255);
	rect(0, 0, xsize * mult - 1, mult - 1);
	rect(0, ysize * mult - mult - 1, xsize * mult - 1, ysize * mult - 1);
	rect(0, 0, mult - 1, ysize * mult - 1);
	rect(xsize * mult - mult - 1, 0, xsize * mult - 1, ysize * mult - 1);
	
	// now set color to red and print food	
	gfx_color(255, 0, 0);
	rect(foodx, foody, foodx + mult - 1, foody + mult - 1);
	
	// now set color to green and print snake
	gfx_color(0, 255, 0);	
	for (auto itr = pieces.begin(); itr != pieces.end(); itr++)
	{
		rect((*itr).x, (*itr).y, (*itr).x + mult - 1, (*itr).y + mult - 1);
	}
	// now set color to black and print eye on snake
	gfx_color(0, 0, 0);
	rect(pieces[size-1].x + 1, pieces[size-1].y + 1, pieces[size-1].x + 2, pieces[size-1].y + 2);
	rect(pieces[size-1].x + mult - 2, pieces[size-1].y + 1, pieces[size-1].x + mult - 3, pieces[size-1].y + 2);
	gfx_flush();
	usleep(speed);
}

// Nora Tucker - CSE 20311 - Lab 13 - project.cpp
// The purpose of this lab is to demonstrate overall competence in using C++
// and to gain experience in designing a program from beginning to end.

// This file specifically is the main method for the snake class. It opens a
// window, waits for user inputs, and then calls the snake move and print
// functions to move the snake continuously until the program is quit

#include "gfx.h"
#include "snake.h"
#include <iostream>
using namespace std;

int main()
{
	char c = ' ';
	Snake mysnake;
	bool paused = false;
	// open new drawing window
	gfx_open(xsize * mult, ysize * mult, "snake game");
	
	while (true)
	{
		if(gfx_event_waiting() == 1)
		{	
			c = gfx_wait();
			switch(c)
			{
			case 'R':
				mysnake.changeDir(UP);
				paused = false;
				break; 
			case 'T':
				mysnake.changeDir(DOWN);
				paused = false;
				break;
			case 'S':
				mysnake.changeDir(RIGHT);
				paused = false;
				break;
			case 'Q':
				mysnake.changeDir(LEFT);
				paused = false;
				break;
			case 'e':
				mysnake.changeSpeed(100000);
				break;
			case 'm':
				mysnake.changeSpeed(50000);
				break;
			case 'h':
				mysnake.changeSpeed(10000);
				break;
			case 'p':
				paused = !paused;
				break;
			case 'q':
				return 1;
			}	
		}
		if(!paused)
		{
			if(mysnake.move() == 1)
				return 1;
			mysnake.print();
		}
	}
	return 0;
}

// Nora Tucker - CSE 20311 - Lab 13 - snake.h
// The purpose of this lab is to demonstrate overall competence in using C++
// and to gain experience in designing a program from beginning to end.

// This is the header file for the snake class, containing declarations of
// the various functions utilized by the class. This includes modifying
// the direction and speed of the snake, moving the snake based on what is
// in front of it, plotting a rectangle (like food or the snake), and 
// plotting the whole board.

#include<vector>
#include<string>

using namespace std;

const int xsize = 60;
const int ysize = 40;
const int mult = 12;
const int UP = 1;
const int DOWN = 2;
const int LEFT = 3;
const int RIGHT = 4;

struct piece{
	int x;
	int y;
};

class Snake {
  public:
	Snake();
	~Snake();
	void changeDir(int);
	void changeSpeed(int);
	int move();
	void lose();
	void eat();
	void moveFood();
	void rect(int, int, int, int);
	void print();
  private:
	vector<piece> pieces;
	int foodx;
	int foody;	
	int dir;
	int size;
	int speed;
};

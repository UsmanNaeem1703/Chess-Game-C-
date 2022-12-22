//============================================================================
// Name       :	main.cpp
// Author     :	Muahammad Qasim	21I-1554
//				Usman Naeem		21I-1560
//				Muhammad Qasim	21I-1580
//				Nawfal Waqar	21I-1914
//				Hassaan Jamil	21I-2774
// Version    :	1.0.0
// Copyright  : (c) Reserved
// Description: Chess game
//============================================================================
#pragma warning(disable:4996)
#ifndef Chess_CPP_
#define Chess_CPP_
#include "util.h"
#include "CImg.h"
#include "chess.h"
#include <iostream>
#include <string>
#include <cmath> // for basic math functions such as cos, sin, sqrt
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;


// seed the random numbers generator by current time (see the documentation of srand for further help)...

int screen = 0;
bool name1Enter = true;
bool name2Enter = false;
bool classical = false;
bool fast = true;

void startGame();
void endGame();
void SetCanvasSize(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*
 * Main Canvas drawing function.
 * This function will display content
 * according to the value of screen.
 * */

void GameDisplay()/**/ {
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
	int i = 100, j = 100, width, height;
	float dark_version[3] = { 0.7412, 0.4235, 0.2392 };
	float light_version[3] = { 0.8784, 0.6745, 0.5608 };
	glClear(GL_COLOR_BUFFER_BIT);
	if (screen == 0) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.8784, 0.6745, 0.5608, 1 /*Alpha component*/); // --> Light Saddle Colour
		DrawRectangle(20, 700, 570, 50, colors[WHITE]);
		DrawString(30, 715, "Enter Player 1 Name: ", colors[BLACK]);
		DrawRectangle(20, 630, 570, 50, colors[WHITE]);
		DrawString(30, 645, "Enter Player 2 Name: ", colors[BLACK]);
		DrawString(248, 715, player1->getName(), colors[BLACK]);
		DrawString(248, 645, player2->getName(), colors[BLACK]);
		DrawRoundRect(1060, 630, 120, 120, dark_version, 10);
		DrawRoundRect(1065, 635, 110, 110, light_version, 10);
		DrawString(1082, 682, "START", colors[BLACK]);
		DrawRoundRect(610, 630, 215, 120, dark_version, 10);
		DrawRoundRect(615, 635, 205, 110, light_version, 10);
		DrawRoundRect(835, 630, 215, 120, dark_version, 10);
		DrawRoundRect(840, 635, 205, 110, light_version, 10);
		DrawString(650, 682, "CLASSICAL", colors[BLACK]);
		DrawString(910, 682, "FAST", colors[BLACK]);
		if (classical == true) {
			DrawTriangle(711, 640, 723, 640, 717, 670, dark_version);
		}
		else if (fast == true) {
			DrawTriangle(936, 640, 948, 640, 942, 670, dark_version);
		}
		DrawRoundRect(20, 40, 1160, 550, dark_version, 20);
		DrawRoundRect(25, 45, 1150, 540, light_version, 20);
		DrawString(60, 530, "LEADERBOARD", dark_version);

	} else if (screen == 1) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.4275, 0.4314, 0.4314, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
		DrawSquare(195, -5, 811, colors[BLACK]);
		for (int i = 0; i <= 9; i += 2) {
			for (int j = 2; j <= 9; j += 2) {
				DrawSquare(j * 100, i * 100 + 2, 101, dark_version);
			}
			for (int j = 3; j <= 10; j += 2) {
				DrawSquare(j * 100, i * 100 + 2, 101, light_version);
			}
			for (int j = 2; j <= 9; j += 2) {
				DrawSquare(j * 100, (i + 1) * 100 + 2, 101, light_version);
			}
			for (int j = 3; j <= 9; j += 2) {
				DrawSquare(j * 100, (i + 1) * 100 + 2, 101, dark_version);
			}
		}
		DrawRoundRect(40, 720, 120, 60, dark_version, 10);
		DrawRoundRect(45, 725, 110, 50, light_version, 10);
		DrawRoundRect(1040, 40, 120, 60, dark_version, 10);
		DrawRoundRect(1045, 45, 110, 50, light_version, 10);
		DrawString(1073, 63, to_string(player1->getMin()) + " : " + to_string(player1->getSec()), colors[BLACK]);
		DrawString(73, 743, to_string(player2->getMin()) + " : " + to_string(player2->getSec()), colors[BLACK]);
		for (int i = 0; i < 16; i++) {
			p1[i]->drawPiece();
			p2[i]->drawPiece();
		}

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (showMovement[i][j] == 1) {
					DrawCircle((j * 100 + 200) + 50, (i * 100) + 50, 13, colors[SKY_BLUE]);
					DrawCircle((j * 100 + 200) + 50, (i * 100) + 50, 10, colors[BLUE]);
				}
			}
		}
	}
	

	glutSwapBuffers(); // do not modify this line..

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	char ch;
	if (key == ' ') {
		for (int i = 7; i >= 0; i--) {
			for (int j = 0; j < 8; j++) {
				cout << showPieces[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
		cout << endl;
		for (int i = 7; i >= 0; i--) {
			for (int j = 0; j < 8; j++) {
				cout << showMovement[i][j] << " ";
			}
			cout << endl;
		}
	}
	if (((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key == ' ') || (key == 8)) && (screen == 0) && (name1Enter)) {
		if (key == 8) {
			player1->popBack();
		}
		else {
			ch = key;
			player1->append(ch);
		}
	}
	if (((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key == ' ') || (key == 8)) && (screen == 0) && (name2Enter)) {
		if (key == 8) {
			player2->popBack();
		}
		else {
			ch = key;
			player2->append(ch);
		}
	}
	if (key == 27 && screen == 1) {
		endGame();
	}
	glutPostRedisplay();
}



/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {
	if (player1->getTurn()) {
		player1->timeDecrement();
		//cout << player1->getMin() << " : " << player1->getSec() << endl;
	}
	else if (player2->getTurn()) {
		player2->timeDecrement();
		//cout << player2->getMin() << " : " << player2->getSec() << endl;
	}
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000, Timer, 0);
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {
	int x_axis, y_axis, ox, oy;
	static int blackOutXAxis = 0, blackOutYAxis = 0, whiteOutXAxis = 1100, whiteOutYAxis = 700;
	static ChessPiece* tempPtr = p1[0];
	Player* curPlayer = player1;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && screen == 1) // dealing only with left button
	{
		if (y <= 100) {
			oy = 700;
		}
		else if (y <= 200) {
			oy = 600;
		}
		else if (y <= 300) {
			oy = 500;
		}
		else if (y <= 400) {
			oy = 400;
		}
		else if (y <= 500) {
			oy = 300;
		}
		else if (y <= 600) {
			oy = 200;
		}
		else if (y <= 700) {
			oy = 100;
		}
		else {
			oy = 0;
		}

		////////////////////////////////////
		if (x <= 100) {
			ox = 0;
		}
		else if (x <= 200) {
			ox = 100;
		}
		else if (x <= 300) {
			ox = 200;
		}
		else if (x <= 400) {
			ox = 300;
		}
		else if (x <= 500) {
			ox = 400;
		}
		else if (x <= 600) {
			ox = 500;
		}
		else if (x <= 700) {
			ox = 600;
		}
		else if (x <= 800) {
			ox = 700;
		}
		else if (x <= 900) {
			ox = 800;
		}
		else if (x <= 1000) {
			ox = 900;
		}
		else if (x <= 1100) {
			ox = 1000;
		}
		else if (x <= 1200) {
			ox = 1100;
		}
		else {
			ox = 1200;
		}
		if (boolToggleShowMovement && screen == 1 && player1->getTurn()) {
			if ((ox - 200) / 100 >= 0 && (ox - 200) / 100 <= 1000 && oy / 100 >= 0 && oy / 100 <= 800 && showMovement[oy / 100][(ox - 200) / 100] == 1) {
				showPieces[tempPtr->getYCoords() / 100][(tempPtr->getXCoords() - 200) / 100] = 0;
				tempPtr->setXYCoords(ox, oy);
				boolToggleShowMovement = false;
				showPieces[oy / 100][(ox - 200) / 100] = 2;
				for (int i = 0; i < 16; i++) {
					if ((p2[i]->getXCoords() == ox) && (p2[i]->getYCoords() == oy)) {
						p2[i]->setXYCoords(whiteOutXAxis, whiteOutYAxis);
						showPieces[oy / 100][(ox - 200) / 100] = 2;
						if (whiteOutXAxis >= 1100) {
							whiteOutXAxis -= 100;
						}
						else {
							whiteOutXAxis = 1100;
							whiteOutYAxis -= 100;
						}
					}
				}
				player1->setTurn(false);
				player2->setTurn();
				p2[0]->toggleShowMovement();
				int count = 0;
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						if (showMovement[i][j] == 1) {
							count++;
						}
					}
				}
				if (count == 0) {
					endGame();
				}
			}
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (showMovement[i][j] == 1)
						showMovement[i][j] = 0;
				}
			}
		}
		else if (boolToggleShowMovement && screen == 1 && player2->getTurn()) {
			if ((ox - 200) / 100 >= 0 && (ox - 200) / 100 <= 1000 && oy / 100 >= 0 && oy / 100 <= 800 && showMovement[oy / 100][(ox - 200) / 100] == 1) {
				showPieces[tempPtr->getYCoords() / 100][(tempPtr->getXCoords() - 200) / 100] = 0;
				tempPtr->setXYCoords(ox, oy);
				boolToggleShowMovement = false;
				showPieces[oy / 100][(ox - 200) / 100] = 3;
				for (int i = 0; i < 16; i++) {
					if ((p1[i]->getXCoords() == ox) && (p1[i]->getYCoords() == oy)) {
						p1[i]->setXYCoords(blackOutXAxis, blackOutYAxis);
						showPieces[oy / 100][(ox - 200) / 100] = 3;
						if (blackOutXAxis == 0) {
							blackOutXAxis += 100;
						}
						else {
							blackOutXAxis = 0;
							blackOutYAxis += 100;
						}
					}
				}
				player2->setTurn(false);
				player1->setTurn();
				int count = 0;
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						if (showMovement[i][j] == 1) {
							count++;
						}
					}
				}
				if (count == 0) {
					endGame();
				}
			}
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (showMovement[i][j] == 1)
						showMovement[i][j] = 0;
				}
			}
		}



		//////////////////////////////////////////////////
		if(player1->getTurn())
			for (int i = 0; i < 16; i++) {
				x_axis = p1[i]->getXCoords();
				y_axis = p1[i]->getYCoords();
				if (oy >= y_axis && oy < (y_axis + 100) && x >= x_axis && x < (x_axis + 100) && x_axis >= 200 && x_axis < 1000) {
					cout << "Player 1 Piece Moved";
					p1[i]->toggleShowMovement();
					tempPtr = p1[i];
					break;
				}
			}
		else if (player2->getTurn()) {
			for (int i = 0; i < 16; i++) {
				x_axis = p2[i]->getXCoords();
				y_axis = p2[i]->getYCoords();
				if (oy >= y_axis && oy < (y_axis + 100) && x >= x_axis && x <(x_axis + 100) && x_axis >= 200 && x_axis < 1000) {
					cout << "Player 2 Piece Moved";
					p2[i]->toggleShowMovement();
					tempPtr = p2[i];
					break;
				}
			}
		}
		
		cout << "Left Mouse Button Pressed at " << x << "\t" << y << '\t' << state << endl;
	}
	else if (button == GLUT_LEFT_BUTTON && x >= 20 && x <= 600 && y >= 50 && y <= 100 && screen == 0) {
		name1Enter = true;
		name2Enter = false;
	} else if (button == GLUT_LEFT_BUTTON && x >= 20 && x <= 600 && y >= 120 && y <= 170 && screen == 0) {
		name1Enter = false;
		name2Enter = true;
	} else if (button == GLUT_LEFT_BUTTON && x >= 615 && x <= 820 && y >= 55 && y <= 165 && screen == 0) {
		classical = true;
		fast = false;
	} else if (button == GLUT_LEFT_BUTTON && x >= 840 && x <= 1045 && y >= 55 && y <= 165 && screen == 0) {
		classical = false;
		fast = true;
	}
	else if (button == GLUT_LEFT_BUTTON && x >= 1065 && x <= 1175 && y >= 55 && y <= 165 && screen == 0) {
	startGame();
	}
	else if (button == GLUT_LEFT_BUTTON) {
	}
	glutPostRedisplay();
}

void startGame() {
	screen = 1;
	p1[0] = new King(4, 0, colors[BLACK]);
	p1[1] = new Queen(3, 0, colors[BLACK]);
	p1[2] = new Rook(0, 0, colors[BLACK]);
	p1[3] = new Rook(7, 0, colors[BLACK]);
	p1[4] = new Knight(1, 0, colors[BLACK]);
	p1[5] = new Knight(6, 0, colors[BLACK]);
	p1[6] = new Bishop(2, 0, colors[BLACK]);
	p1[7] = new Bishop(5, 0, colors[BLACK]);
	for (int i = 8, j = 0; i < 16; i++, j++) {
		p1[i] = new Pawn(j, 1, colors[BLACK]);
	}
	p2[0] = new King	(4, 7, colors[WHITE]);
	p2[1] = new Queen	(3, 7, colors[WHITE]);
	p2[2] = new Rook	(0, 7, colors[WHITE]);
	p2[3] = new Rook	(7, 7, colors[WHITE]);
	p2[4] = new Knight	(1, 7, colors[WHITE]);
	p2[5] = new Knight	(6, 7, colors[WHITE]);
	p2[6] = new Bishop	(2, 7, colors[WHITE]);
	p2[7] = new Bishop	(5, 7, colors[WHITE]);
	for (int i = 8, j = 0; i < 16; i++, j++) {
		p2[i] = new Pawn(j, 6, colors[WHITE]);
	}
	if (classical) {
		player1->setTime(35);
		player2->setTime(35);
	}else if(fast) {
		player1->setTime(4);
		player2->setTime(4);
	}
	player1->setTurn();
}
void endGame() {
	for (int i = 0; i < 16; i++) {
		delete p1[i];
		delete p2[i];
	}
	screen = 0;
}

/*
 * our gateway main function
 * */
int main(int argc, char* argv[]) {
	
	int width = 1200, height = 800;
	player1 = new Player(0, "");
	player2 = new Player(0, "");
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(0, 0); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("CHESS GAME"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...


	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);
	glutMouseFunc(MouseClicked);



	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* RushHour_CPP_ */
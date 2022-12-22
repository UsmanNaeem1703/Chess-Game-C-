#include <string>
#include "util.h"

using namespace std;
class ChessPiece;
bool boolToggleShowMovement = false;
ChessPiece* p1[16];
ChessPiece* p2[16];
int showMovement[8][8] = { 0 };
int showPieces[8][8] = { 0 };
bool check= false;
class Time {
private:
	int sec;
	int min;
public:
	Time(int m) {
		min = m;
		sec = 0;
	}
	int getSec() {
		return sec;
	}
	int getMin() {
		return min;
	}
	void setTimer(int m) {
		min = m;
		sec = 0;
	}
	void timeDecrement() {
		if (sec == 0) {
			sec = 59;
			min--;
		}
		else {
			sec--;
		}
	}
	void operator--() {
		if (sec == 0) {
			sec = 59;
			min--;
		}
		else {
			sec--;
		}
	}
};


class Player {
private:
	static int playerID;
	string playerName;
	int playerWins;
	int playerLooses;
	int playerDraw;
	Time* t;
	bool turn;
public:
	Player(int minutes, string name = "") {
		playerName = name;
		playerWins = 0;
		playerLooses = 0;
		playerDraw = 0;
		t = new Time(0);
		turn = false;
	};
	void setTurn(bool toggleTurn = true) {
		turn = toggleTurn;
	};
	bool getTurn() {
		return turn;
	}
	void append(char ch) {
		playerName += ch;
	}
	void popBack() {
		playerName.pop_back();
	}
	string getName() {
		return playerName;
	}
	void setTime(int minutes) {
		t->setTimer(minutes);
	}
	int getMin() {
		return t->getMin();
	}
	int getSec() {
		return t->getSec();
	}
	void timeDecrement() {
		this->t->timeDecrement();
	}
	~Player() {
		delete t;
	}
};
int Player::playerID = 0;
Player* player1;
Player* player2;


class ChessPiece{
protected:
	float* pieceColor;
	char* pieceName;
	int x;
	int y;
public:
	ChessPiece(int x, int y, char* ch, float* c, bool isVirtual) {
		pieceColor = c;
		this->x = (x * 100) + 200;
		this->y = y * 100;
		pieceName = ch;
		if(c == colors[BLACK] && !isVirtual)
			showPieces[y][x] = 2;
		else if(!isVirtual)
			showPieces[y][x] = 3;
	};
	int getXCoords() {
		return x;
	}
	int getYCoords() {
		return y;
	}
	void setXYCoords(int a, int b) {
		//showPieces[y / 100][(x-200) / 100] = 0;
		x = a;
		y = b;
		/*if(pieceColor == colors[BLACK])
			showPieces[y / 100][(x-200) / 100] = 2;
		else
			showPieces[y / 100][(x-200) / 100] = 3;*/
	}
	virtual void toggleShowMovement() {

	}
	virtual void drawPiece() {

	}
	virtual char* getPieceName(int a, int b) {
		return (char*)"";
	}
	/*virtual bool checkCheck(int showPieces[][8]) {
		return false;
	}*/
	float* getPieceColor() {
		return pieceColor;
	}
};

//bool causeCheck(ChessPiece* ptr, int x, int y) {
//	int x0, y0;
//	x0 = ptr->getXCoords();
//	y0 = ptr->getYCoords();
//	showPieces[y0 / 100][((x0 - 200) / 100)] = 0;
//	showPieces[y / 100][(x - 200) / 100] = 2;
//	ptr->setXYCoords(x, y);
//	if (ptr->getPieceColor() == colors[BLACK]) {
//		for (int i = (p1[0]->getYCoords() / 100) - 1, j = ((p1[0]->getXCoords() - 200) / 100); i >= 0; i--) {
//			if (showPieces[i][j] == 2)
//				break;
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
//						cout << "BLACK check With Queen or Rook in BL\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//		}
//		for (int i = (p1[0]->getYCoords() / 100) + 1, j = ((p1[0]->getXCoords() - 200) / 100); i < 8; i++) {
//			if (showPieces[i][j] == 2) {
//				break;
//			}
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
//						cout << "BLACK check With Queen or Rook in TL\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//		}
//		for (int i = (p1[0]->getYCoords() / 100), j = ((p1[0]->getXCoords() - 200) / 100) + 1; j < 8; j++) {
//			if (showPieces[i][j] == 2)
//				break;
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
//						cout << "BLACK check With Queen or Rook in RL\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//		}
//		for (int i = (p1[0]->getYCoords() / 100), j = ((p1[0]->getXCoords() - 200) / 100) - 1; j >= 0; j--) {
//			if (showPieces[i][j] == 2)
//				break;
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
//						cout << "BLACK check With Queen or Rook in LL\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//		}
//		for (int i = (p1[0]->getYCoords() / 100) - 1, j = ((p1[0]->getXCoords() - 200) / 100) - 1; i >= 0 && j >= 0; i--, j--) {
//			if (showPieces[i][j] == 2)
//				break;
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
//						cout << "BLACK check With Queen or Bishop in LBD\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//		}
//		for (int i = (p1[0]->getYCoords() / 100) + 1, j = ((p1[0]->getXCoords() - 200) / 100) + 1; i < 8 && j < 8; i++, j++) {
//			if (showPieces[i][j] == 2)
//				break;
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
//						cout << "BLACK check With Queen or Bishop in RTD\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//		}
//		for (int i = (p1[0]->getYCoords() / 100) + 1, j = ((p1[0]->getXCoords() - 200) / 100) - 1; j >= 0 && i < 8; i++, j--) {
//			if (showPieces[i][j] == 2)
//				break;
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
//						cout << "-------------BLACK check With Queen or Bishop in LTD\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//			else {
//				break;
//			}
//		}
//		for (int i = (p1[0]->getYCoords() / 100) - 1, j = ((p1[0]->getXCoords() - 200) / 100) + 1; j < 8 && i >= 0; i--, j++) {
//			if (showPieces[i][j] == 2)
//				break;
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
//						cout << "BLACK check With Queen or Bishop in RBD\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//		}
//
//		// Knight
//		int i = p1[0]->getYCoords() / 100;
//		int j = (p1[0]->getXCoords() / 100) - 200;
//		for (int k = 0; k < 16; k++) {
//			if (/*Down Left L*/(p2[k]->getPieceName(((j - 1) * 100) + 200, (i - 2) * 100) == (char*)"Knight" && (i - 2 >= 0) && (j - 1 >= 0)) || /*Down Right L*/(p2[k]->getPieceName(((j + 1) * 100) + 200, (i - 2) * 100) == (char*)"Knight" && (i - 2 >= 0) && (j + 1 < 8)) || /*Up left L*/(p2[k]->getPieceName(((j - 1) * 100) + 200, (i + 2) * 100) == (char*)"Knight" && (i + 2 < 8) && (j - 1 >= 0)) || /*Up Right L*/(p2[k]->getPieceName(((j + 1) * 100) + 200, (i + 2) * 100) == (char*)"Knight" && (i + 2 < 8) && (j + 1 < 8)) || /*Right Up L*/(p2[k]->getPieceName(((j + 2) * 100) + 200, (i + 1) * 100) == (char*)"Knight" && (i + 1 < 8) && (j + 2 < 8)) || /*Right Down*/(p2[k]->getPieceName(((j + 2) * 100) + 200, (i - 1) * 100) == (char*)"Knight" && (i - 1 >= 0) && (j + 2 < 8)) || /*Left Up*/(p2[k]->getPieceName(((j - 2) * 100) + 200, (i + 1) * 100) == (char*)"Knight" && (i + 1 < 8) && (j - 2 >= 0)) || /*Left Down*/(p2[k]->getPieceName(((j - 2) * 100) + 200, (i - 1) * 100) == (char*)"Knight" && (i - 1 >= 0) && (j - 2 >= 0))) {
//				cout << "BLACK check With Knight\n";
//				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//				showPieces[y / 100][((x - 200) / 100)] = 0;
//				ptr->setXYCoords(x0, y0);
//				return false;
//			}
//		}
//		// Pawn
//		i = p1[0]->getYCoords() / 100;
//		j = (p1[0]->getXCoords() / 100) - 200;
//		for (int k = 0; k < 16; k++) {
//			if (/*Up left*/(p2[k]->getPieceName(((j - 1) * 100) + 200, (i + 1) * 100) == (char*)"Pawn" && (i + 1 < 8) && (j - 1 >= 0)) || /*Up Right*/(p2[k]->getPieceName(((j + 1) * 100) + 200, (i + 1) * 100) == (char*)"Pawn" && (i + 1 < 8) && (j + 1 < 8))) {
//				cout << "BLACK check With Pawn\n";
//				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//				showPieces[y / 100][((x - 200) / 100)] = 0;
//				ptr->setXYCoords(x0, y0);
//				return false;
//			}
//		}
//		showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//		showPieces[y / 100][((x - 200) / 100)] = 0;
//		ptr->setXYCoords(x0, y0);
//		return true;
//	}
//	else if (ptr->getPieceColor() == colors[WHITE]) {
//	//for (int i = (p1[0]->getYCoords() / 100) - 1, j = ((p1[0]->getXCoords() - 200) / 100); i >= 0; i--) {
//	//	if (showPieces[i][j] == 3)
//	//		break;
//	//	if (showPieces[i][j] == 2 || showPieces[i][j] == 0) {
//	//		for (int k = 0; k < 16; k++) {
//	//			if (p1[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p1[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
//	//				cout << "BLACK check With Queen or Rook in BL\n";
//	//				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//	//				showPieces[y / 100][((x - 200) / 100)] = 0;
//	//				ptr->setXYCoords(x0, y0);
//	//				return false;
//	//			}
//	//		}
//	//	}
//	//}
//	//for (int i = (p1[0]->getYCoords() / 100) + 1, j = ((p1[0]->getXCoords() - 200) / 100); i < 8; i++) {
//	//	if (showPieces[i][j] == 3) {
//	//		break;
//	//	}
//	//	if (showPieces[i][j] == 2 || showPieces[i][j] == 0) {
//	//		for (int k = 0; k < 16; k++) {
//	//			if (p1[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p1[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
//	//				cout << "BLACK check With Queen or Rook in TL\n";
//	//				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//	//				showPieces[y / 100][((x - 200) / 100)] = 0;
//	//				ptr->setXYCoords(x0, y0);
//	//				return false;
//	//			}
//	//		}
//	//	}
//	//}
//	//for (int i = (p1[0]->getYCoords() / 100), j = ((p1[0]->getXCoords() - 200) / 100) + 1; j < 8; j++) {
//	//	if (showPieces[i][j] == 3)
//	//		break;
//	//	if (showPieces[i][j] == 2 || showPieces[i][j] == 0) {
//	//		for (int k = 0; k < 16; k++) {
//	//			if (p1[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p1[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
//	//				cout << "BLACK check With Queen or Rook in RL\n";
//	//				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//	//				showPieces[y / 100][((x - 200) / 100)] = 0;
//	//				ptr->setXYCoords(x0, y0);
//	//				return false;
//	//			}
//	//		}
//	//	}
//	//}
//	//for (int i = (p1[0]->getYCoords() / 100), j = ((p1[0]->getXCoords() - 200) / 100) - 1; j >= 0; j--) {
//	//	if (showPieces[i][j] == 3)
//	//		break;
//	//	if (showPieces[i][j] == 2 || showPieces[i][j] == 0) {
//	//		for (int k = 0; k < 16; k++) {
//	//			if (p1[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p1[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
//	//				cout << "BLACK check With Queen or Rook in LL\n";
//	//				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//	//				showPieces[y / 100][((x - 200) / 100)] = 0;
//	//				ptr->setXYCoords(x0, y0);
//	//				return false;
//	//			}
//	//		}
//	//	}
//	//}
//	//for (int i = (p1[0]->getYCoords() / 100) - 1, j = ((p1[0]->getXCoords() - 200) / 100) - 1; i >= 0 && j >= 0; i--, j--) {
//	//	if (showPieces[i][j] == 3)
//	//		break;
//	//	if (showPieces[i][j] == 2 || showPieces[i][j] == 0) {
//	//		for (int k = 0; k < 16; k++) {
//	//			if (p1[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p1[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
//	//				cout << "BLACK check With Queen or Bishop in LBD\n";
//	//				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//	//				showPieces[y / 100][((x - 200) / 100)] = 0;
//	//				ptr->setXYCoords(x0, y0);
//	//				return false;
//	//			}
//	//		}
//	//	}
//	//}
//	//for (int i = (p1[0]->getYCoords() / 100) + 1, j = ((p1[0]->getXCoords() - 200) / 100) + 1; i < 8 && j < 8; i++, j++) {
//	//	if (showPieces[i][j] == 3)
//	//		break;
//	//	if (showPieces[i][j] == 2 || showPieces[i][j] == 0) {
//	//		for (int k = 0; k < 16; k++) {
//	//			if (p1[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p1[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
//	//				cout << "BLACK check With Queen or Bishop in RTD\n";
//	//				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//	//				showPieces[y / 100][((x - 200) / 100)] = 0;
//	//				ptr->setXYCoords(x0, y0);
//	//				return false;
//	//			}
//	//		}
//	//	}
//	//}
//	//for (int i = (p1[0]->getYCoords() / 100) + 1, j = ((p1[0]->getXCoords() - 200) / 100) - 1; j >= 0 && i < 8; i++, j--) {
//	//	if (showPieces[i][j] == 3)
//	//		break;
//	//	if (showPieces[i][j] == 2 || showPieces[i][j] == 0) {
//	//		for (int k = 0; k < 16; k++) {
//	//			if (p1[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p1[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
//	//				cout << "-------------BLACK check With Queen or Bishop in LTD\n";
//	//				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//	//				showPieces[y / 100][((x - 200) / 100)] = 0;
//	//				ptr->setXYCoords(x0, y0);
//	//				return false;
//	//			}
//	//		}
//	//	}
//	//	else {
//	//		break;
//	//	}
//	//}
//	//for (int i = (p1[0]->getYCoords() / 100) - 1, j = ((p1[0]->getXCoords() - 200) / 100) + 1; j < 8 && i >= 0; i--, j++) {
//	//	if (showPieces[i][j] == 3)
//	//		break;
//	//	if (showPieces[i][j] == 2 || showPieces[i][j] == 0) {
//	//		for (int k = 0; k < 16; k++) {
//	//			if (p1[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p1[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
//	//				cout << "BLACK check With Queen or Bishop in RBD\n";
//	//				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//	//				showPieces[y / 100][((x - 200) / 100)] = 0;
//	//				ptr->setXYCoords(x0, y0);
//	//				return false;
//	//			}
//	//		}
//	//	}
//	//}
//
//	//// Knight
//	//int i = p1[0]->getYCoords() / 100;
//	//int j = (p1[0]->getXCoords() / 100) - 200;
//	//for (int k = 0; k < 16; k++) {
//	//	if (/*Down Left L*/(p1[k]->getPieceName(((j - 1) * 100) + 200, (i - 2) * 100) == (char*)"Knight" && (i - 2 >= 0) && (j - 1 >= 0)) || /*Down Right L*/(p1[k]->getPieceName(((j + 1) * 100) + 200, (i - 2) * 100) == (char*)"Knight" && (i - 2 >= 0) && (j + 1 < 8)) || /*Up left L*/(p1[k]->getPieceName(((j - 1) * 100) + 200, (i + 2) * 100) == (char*)"Knight" && (i + 2 < 8) && (j - 1 >= 0)) || /*Up Right L*/(p1[k]->getPieceName(((j + 1) * 100) + 200, (i + 2) * 100) == (char*)"Knight" && (i + 2 < 8) && (j + 1 < 8)) || /*Right Up L*/(p1[k]->getPieceName(((j + 2) * 100) + 200, (i + 1) * 100) == (char*)"Knight" && (i + 1 < 8) && (j + 2 < 8)) || /*Right Down*/(p1[k]->getPieceName(((j + 2) * 100) + 200, (i - 1) * 100) == (char*)"Knight" && (i - 1 >= 0) && (j + 2 < 8)) || /*Left Up*/(p1[k]->getPieceName(((j - 2) * 100) + 200, (i + 1) * 100) == (char*)"Knight" && (i + 1 < 8) && (j - 2 >= 0)) || /*Left Down*/(p1[k]->getPieceName(((j - 2) * 100) + 200, (i - 1) * 100) == (char*)"Knight" && (i - 1 >= 0) && (j - 2 >= 0))) {
//	//		cout << "BLACK check With Knight\n";
//	//		showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//	//		showPieces[y / 100][((x - 200) / 100)] = 0;
//	//		ptr->setXYCoords(x0, y0);
//	//		return false;
//	//	}
//	//}
//	//// Pawn
//	//i = p1[0]->getYCoords() / 100;
//	//j = (p1[0]->getXCoords() / 100) - 200;
//	//for (int k = 0; k < 16; k++) {
//	//	if (/*Up left*/(p1[k]->getPieceName(((j - 1) * 100) + 200, (i + 1) * 100) == (char*)"Pawn" && (i + 1 < 8) && (j - 1 >= 0)) || /*Up Right*/(p1[k]->getPieceName(((j + 1) * 100) + 200, (i + 1) * 100) == (char*)"Pawn" && (i + 1 < 8) && (j + 1 < 8))) {
//	//		cout << "BLACK check With Pawn\n";
//	//		showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//	//		showPieces[y / 100][((x - 200) / 100)] = 0;
//	//		ptr->setXYCoords(x0, y0);
//	//		return false;
//	//	}
//	//}
//	showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//	showPieces[y / 100][((x - 200) / 100)] = 0;
//	ptr->setXYCoords(x0, y0);
//	return true;
//	}
//}
bool causeCheck(ChessPiece* ptr, int x, int y) {
	int x0, y0;
	x0 = ptr->getXCoords();
	y0 = ptr->getYCoords();
	ptr->setXYCoords(x, y);
	if (ptr->getPieceColor() == colors[BLACK]) {
		for (int i = (p1[0]->getYCoords() / 100) - 1, j = ((p1[0]->getXCoords() - 200) / 100); i >= 0; i--) {
			if (showPieces[i][j] == 2)
				break;
			if (showPieces[i][j] == 3) {
				for (int k = 0; k < 16; k++) {
					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
						cout << "BLACK check With Queen or Rook in BL\n";
						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
						showPieces[y / 100][((x - 200) / 100)] = 0;
						ptr->setXYCoords(x0, y0);
						return false;
					}
				}
			}
		}
		for (int i = (p1[0]->getYCoords() / 100) + 1, j = ((p1[0]->getXCoords() - 200) / 100); i < 8; i++) {
			if (showPieces[i][j] == 2) {
				break;
			}
			if (showPieces[i][j] == 3) {
				for (int k = 0; k < 16; k++) {
					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
						cout << "BLACK check With Queen or Rook in TL\n";
						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
						showPieces[y / 100][((x - 200) / 100)] = 0;
						ptr->setXYCoords(x0, y0);
						return false;
					}
				}
			}
		}
		for (int i = (p1[0]->getYCoords() / 100), j = ((p1[0]->getXCoords() - 200) / 100) + 1; j < 8; j++) {
			if (showPieces[i][j] == 2)
				break;
			if (showPieces[i][j] == 3) {
				for (int k = 0; k < 16; k++) {
					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
						cout << "BLACK check With Queen or Rook in RL\n";
						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
						showPieces[y / 100][((x - 200) / 100)] = 0;
						ptr->setXYCoords(x0, y0);
						return false;
					}
				}
			}
		}
		for (int i = (p1[0]->getYCoords() / 100), j = ((p1[0]->getXCoords() - 200) / 100) - 1; j >= 0; j--) {
			if (showPieces[i][j] == 2)
				break;
			if (showPieces[i][j] == 3) {
				for (int k = 0; k < 16; k++) {
					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
						cout << "BLACK check With Queen or Rook in LL\n";
						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
						showPieces[y / 100][((x - 200) / 100)] = 0;
						ptr->setXYCoords(x0, y0);
						return false;
					}
				}
			}
		}
		for (int i = (p1[0]->getYCoords() / 100) - 1, j = ((p1[0]->getXCoords() - 200) / 100) - 1; i >= 0 && j >= 0; i--, j--) {
			if (showPieces[i][j] == 2)
				break;
			if (showPieces[i][j] == 3) {
				for (int k = 0; k < 16; k++) {
					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
						cout << "BLACK check With Queen or Bishop in LBD\n";
						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
						showPieces[y / 100][((x - 200) / 100)] = 0;
						ptr->setXYCoords(x0, y0);
						return false;
					}
				}
			}
		}
		for (int i = (p1[0]->getYCoords() / 100) + 1, j = ((p1[0]->getXCoords() - 200) / 100) + 1; i < 8 && j < 8; i++, j++) {
			if (showPieces[i][j] == 2)
				break;
			if (showPieces[i][j] == 3) {
				for (int k = 0; k < 16; k++) {
					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
						cout << "BLACK check With Queen or Bishop in RTD\n";
						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
						showPieces[y / 100][((x - 200) / 100)] = 0;
						ptr->setXYCoords(x0, y0);
						return false;
					}
				}
			}
		}
		for (int i = (p1[0]->getYCoords() / 100) + 1, j = ((p1[0]->getXCoords() - 200) / 100) - 1; j >= 0 && i < 8; i++, j--) {
			if (showPieces[i][j] == 2)
				break;
			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
				for (int k = 0; k < 16; k++) {
					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
						cout << "-------------BLACK check With Queen or Bishop in LTD\n";
						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
						showPieces[y / 100][((x - 200) / 100)] = 0;
						ptr->setXYCoords(x0, y0);
						return false;
					}
				}
			}
			else {
				break;
			}
		}
		for (int i = (p1[0]->getYCoords() / 100) - 1, j = ((p1[0]->getXCoords() - 200) / 100) + 1; j < 8 && i >= 0; i--, j++) {
			if (showPieces[i][j] == 2)
				break;
			if (showPieces[i][j] == 3) {
				for (int k = 0; k < 16; k++) {
					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
						cout << "BLACK check With Queen or Bishop in RBD\n";
						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
						showPieces[y / 100][((x - 200) / 100)] = 0;
						ptr->setXYCoords(x0, y0);
						return false;
					}
				}
			}
		}

		// Knight
		int i = p1[0]->getYCoords() / 100;
		int j = (p1[0]->getXCoords() / 100) - 200;
		for (int k = 0; k < 16; k++) {
			if (/*Down Left L*/(p2[k]->getPieceName(((j - 1) * 100) + 200, (i - 2) * 100) == (char*)"Knight" && (i - 2 >= 0) && (j - 1 >= 0)) || /*Down Right L*/(p2[k]->getPieceName(((j + 1) * 100) + 200, (i - 2) * 100) == (char*)"Knight" && (i - 2 >= 0) && (j + 1 < 8)) || /*Up left L*/(p2[k]->getPieceName(((j - 1) * 100) + 200, (i + 2) * 100) == (char*)"Knight" && (i + 2 < 8) && (j - 1 >= 0)) || /*Up Right L*/(p2[k]->getPieceName(((j + 1) * 100) + 200, (i + 2) * 100) == (char*)"Knight" && (i + 2 < 8) && (j + 1 < 8)) || /*Right Up L*/(p2[k]->getPieceName(((j + 2) * 100) + 200, (i + 1) * 100) == (char*)"Knight" && (i + 1 < 8) && (j + 2 < 8)) || /*Right Down*/(p2[k]->getPieceName(((j + 2) * 100) + 200, (i - 1) * 100) == (char*)"Knight" && (i - 1 >= 0) && (j + 2 < 8)) || /*Left Up*/(p2[k]->getPieceName(((j - 2) * 100) + 200, (i + 1) * 100) == (char*)"Knight" && (i + 1 < 8) && (j - 2 >= 0)) || /*Left Down*/(p2[k]->getPieceName(((j - 2) * 100) + 200, (i - 1) * 100) == (char*)"Knight" && (i - 1 >= 0) && (j - 2 >= 0))) {
				cout << "BLACK check With Knight\n";
				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
				showPieces[y / 100][((x - 200) / 100)] = 0;
				ptr->setXYCoords(x0, y0);
				return false;
			}
		}
		// Pawn
		i = p1[0]->getYCoords() / 100;
		j = (p1[0]->getXCoords() / 100) - 200;
		for (int k = 0; k < 16; k++) {
			if (/*Up left*/(p2[k]->getPieceName(((j - 1) * 100) + 200, (i + 1) * 100) == (char*)"Pawn" && (i + 1 < 8) && (j - 1 >= 0)) || /*Up Right*/(p2[k]->getPieceName(((j + 1) * 100) + 200, (i + 1) * 100) == (char*)"Pawn" && (i + 1 < 8) && (j + 1 < 8))) {
				cout << "BLACK check With Pawn\n";
				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
				showPieces[y / 100][((x - 200) / 100)] = 0;
				ptr->setXYCoords(x0, y0);
				return false;
			}
		}
		showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
		showPieces[y / 100][((x - 200) / 100)] = 0;
		ptr->setXYCoords(x0, y0);
		return true;


	}
	else if (ptr->getPieceColor() == colors[WHITE]) {
		ptr->setXYCoords(x0, y0);
		return true;
	}
}
class King :public ChessPiece {
public:
	King(int x = 5, int y = 0, float* c = colors[BLACK], bool isVirtual = false, char* ch = (char*)"King") :ChessPiece(x, y, ch, c, isVirtual) {
	}
	void toggleShowMovement() {
		if (pieceColor == colors[BLACK]) {
			boolToggleShowMovement = true;
			int i = y / 100;
			int j = ((x - 200) / 100);
			//UP
			if (showPieces[(y / 100) + 1][((x - 200) / 100)] != 2 && showPieces[(y / 100) + 1][((x - 200) / 100)] != 3 && ((y / 100) + 1 < 8) && causeCheck(this, (j * 100)+200, ((i + 1) * 100))) {
				showMovement[(y / 100) + 1][((x - 200) / 100)] = 1;
			}
			else if (showPieces[(y / 100) + 1][((x - 200) / 100)] == 3 && ((y / 100) + 1 < 8) && causeCheck(this, (j * 100) + 200, ((i + 1) * 100))) {
				showMovement[(y / 100) + 1][((x - 200) / 100)] = 1;
			}
			// Down
			if (showPieces[(y / 100) - 1][((x - 200) / 100)] != 2 && showPieces[(y / 100) - 1][((x - 200) / 100)] != 3 && ((y / 100) - 1 >= 0) && causeCheck(this, (j * 100) + 200, ((i - 1) * 100))) {
				showMovement[(y / 100) - 1][((x - 200) / 100)] = 1;
			}
			else if (showPieces[(y / 100) - 1][((x - 200) / 100)] == 3 && ((y / 100) - 1 >= 0) && causeCheck(this, (j * 100) + 200, ((i - 1) * 100))) {
				showMovement[(y / 100) - 1][((x - 200) / 100)] = 1;
			}
			// Right
			if (showPieces[(y / 100)][((x - 200) / 100 + 1)] != 2 && showPieces[(y / 100)][((x - 200) / 100 + 1)] != 3 && (((x - 200) / 100 + 1) < 8) && causeCheck(this, ((j+1) * 100) + 200, (i * 100))) {
				showMovement[(y / 100)][((x - 200) / 100 + 1)] = 1;
			}
			else if (showPieces[(y / 100)][((x - 200) / 100 + 1)] == 3 && (((x - 200) / 100 + 1) < 8) && causeCheck(this, ((j + 1) * 100) + 200, (i * 100))) {
				showMovement[(y / 100)][((x - 200) / 100 + 1)] = 1;
			}
			//Left
			if (showPieces[(y / 100)][((x - 200) / 100 - 1)] != 2 && showPieces[(y / 100)][((x - 200) / 100 - 1)] != 3 && (((x - 200) / 100 - 1) >= 0) && causeCheck(this, ((j - 1) * 100) + 200, (i * 100))) {
				showMovement[(y / 100)][((x - 200) / 100 - 1)] = 1;
			}
			else if (showPieces[(y / 100)][((x - 200) / 100 - 1)] == 3 && (((x - 200) / 100 - 1) >= 0) && causeCheck(this, ((j - 1) * 100) + 200, (i * 100))) {
				showMovement[(y / 100)][((x - 200) / 100 - 1)] = 1;
			}
			//Left Top
			if (showPieces[(y / 100) + 1][((x - 200) / 100 - 1)] != 2 && showPieces[(y / 100) + 1][((x - 200) / 100 - 1)] != 3 && ((y / 100) + 1 < 8) && (((x - 200) / 100 - 1) >= 0) && causeCheck(this, ((j - 1) * 100) + 200, ((i+1) * 100))) {
				showMovement[(y / 100) + 1][((x - 200) / 100 - 1)] = 1;
			}
			else if (showPieces[(y / 100) + 1][((x - 200) / 100 - 1)] == 3 && ((y / 100) + 1 < 8) && (((x - 200) / 100 - 1) >= 0) && causeCheck(this, ((j - 1) * 100) + 200, ((i + 1) * 100))) {
				showMovement[(y / 100) + 1][((x - 200) / 100 - 1)] = 1;
			}
			//Right Top
			if (showPieces[(y / 100) + 1][((x - 200) / 100 + 1)] != 2 && showPieces[(y / 100) + 1][((x - 200) / 100 + 1)] != 3 && ((y / 100) + 1 < 8) && (((x - 200) / 100 + 1) < 8) && causeCheck(this, ((j + 1) * 100) + 200, ((i + 1) * 100))) {
				showMovement[(y / 100) + 1][((x - 200) / 100 + 1)] = 1;
			}
			else if (showPieces[(y / 100) + 1][((x - 200) / 100 + 1)] == 3 && ((y / 100) + 1 < 8) && (((x - 200) / 100 + 1) < 8) && causeCheck(this, ((j + 1) * 100) + 200, ((i + 1) * 100))) {
				showMovement[(y / 100) + 1][((x - 200) / 100 + 1)] = 1;
			}
			//Left Bottom
			if (showPieces[(y / 100) - 1][((x - 200) / 100 - 1)] != 2 && showPieces[(y / 100) - 1][((x - 200) / 100 - 1)] != 3 && (((x - 200) / 100 - 1) >= 0) && ((y / 100) - 1 >= 0) && causeCheck(this, ((j - 1) * 100) + 200, ((i - 1) * 100))) {
				showMovement[(y / 100) - 1][((x - 200) / 100 - 1)] = 1;
			}
			else if (showPieces[(y / 100) - 1][((x - 200) / 100 - 1)] == 3 && (((x - 200) / 100 - 1) >= 0) && ((y / 100) - 1 >= 0) && causeCheck(this, ((j - 1) * 100) + 200, ((i - 1) * 100))) {
				showMovement[(y / 100) - 1][((x - 200) / 100 - 1)] = 1;
			}
			//Right Bottom
			if (showPieces[(y / 100) - 1][((x - 200) / 100 + 1)] != 2 && showPieces[(y / 100) - 1][((x - 200) / 100 + 1)] != 3 && (((x - 200) / 100 + 1) < 8) && ((y / 100) - 1 >= 0) && causeCheck(this, ((j + 1) * 100) + 200, ((i - 1) * 100))) {
				showMovement[(y / 100) - 1][((x - 200) / 100 + 1)] = 1;
			}
			else if (showPieces[(y / 100) - 1][((x - 200) / 100 + 1)] == 3 && (((x - 200) / 100 + 1) < 8) && ((y / 100) - 1 >= 0) && causeCheck(this, ((j + 1) * 100) + 200, ((i - 1) * 100))) {
				showMovement[(y / 100) - 1][((x - 200) / 100 + 1)] = 1;
			}
		}
		else if (pieceColor == colors[WHITE]) {
			boolToggleShowMovement = true;
			int i = y / 100;
			int j = ((x - 200) / 100);
			//UP
			if (showPieces[(y / 100) + 1][((x - 200) / 100)] != 2 && showPieces[(y / 100) + 1][((x - 200) / 100)] != 3 && ((y / 100) + 1 < 8) && causeCheck(this, (j * 100) + 200, ((i + 1) * 100))) {
				showMovement[(y / 100) + 1][((x - 200) / 100)] = 1;
			}
			else if (showPieces[(y / 100) + 1][((x - 200) / 100)] == 2 && ((y / 100) + 1 < 8) && causeCheck(this, (j * 100) + 200, ((i + 1) * 100))) {
				showMovement[(y / 100) + 1][((x - 200) / 100)] = 1;
			}
			// Down
			if (showPieces[(y / 100) - 1][((x - 200) / 100)] != 2 && showPieces[(y / 100) - 1][((x - 200) / 100)] != 3 && ((y / 100) - 1 >= 0) && causeCheck(this, (j * 100) + 200, ((i - 1) * 100))) {
				showMovement[(y / 100) - 1][((x - 200) / 100)] = 1;
			}
			else if (showPieces[(y / 100) - 1][((x - 200) / 100)] == 2 && ((y / 100) - 1 >= 0) && causeCheck(this, (j * 100) + 200, ((i - 1) * 100))) {
				showMovement[(y / 100) - 1][((x - 200) / 100)] = 1;
			}
			// Right
			if (showPieces[(y / 100)][((x - 200) / 100 + 1)] != 2 && showPieces[(y / 100)][((x - 200) / 100 + 1)] != 3 && (((x - 200) / 100 + 1) < 8) && causeCheck(this, ((j + 1) * 100) + 200, (i * 100))) {
				showMovement[(y / 100)][((x - 200) / 100 + 1)] = 1;
			}
			else if (showPieces[(y / 100)][((x - 200) / 100 + 1)] == 2 && (((x - 200) / 100 + 1) < 8) && causeCheck(this, ((j + 1) * 100) + 200, (i * 100))) {
				showMovement[(y / 100)][((x - 200) / 100 + 1)] = 1;
			}
			//Left
			if (showPieces[(y / 100)][((x - 200) / 100 - 1)] != 2 && showPieces[(y / 100)][((x - 200) / 100 - 1)] != 3 && (((x - 200) / 100 - 1) >= 0) && causeCheck(this, ((j - 1) * 100) + 200, (i * 100))) {
				showMovement[(y / 100)][((x - 200) / 100 - 1)] = 1;
			}
			else if (showPieces[(y / 100)][((x - 200) / 100 - 1)] == 2 && (((x - 200) / 100 - 1) >= 0) && causeCheck(this, ((j - 1) * 100) + 200, (i * 100))) {
				showMovement[(y / 100)][((x - 200) / 100 - 1)] = 1;
			}
			//Left Top
			if (showPieces[(y / 100) + 1][((x - 200) / 100 - 1)] != 2 && showPieces[(y / 100) + 1][((x - 200) / 100 - 1)] != 3 && ((y / 100) + 1 < 8) && (((x - 200) / 100 - 1) >= 0) && causeCheck(this, ((j - 1) * 100) + 200, ((i + 1) * 100))) {
				showMovement[(y / 100) + 1][((x - 200) / 100 - 1)] = 1;
			}
			else if (showPieces[(y / 100) + 1][((x - 200) / 100 - 1)] == 2 && ((y / 100) + 1 < 8) && (((x - 200) / 100 - 1) >= 0) && causeCheck(this, ((j - 1) * 100) + 200, ((i + 1) * 100))) {
				showMovement[(y / 100) + 1][((x - 200) / 100 - 1)] = 1;
			}
			//Right Top
			if (showPieces[(y / 100) + 1][((x - 200) / 100 + 1)] != 2 && showPieces[(y / 100) + 1][((x - 200) / 100 + 1)] != 3 && ((y / 100) + 1 < 8) && (((x - 200) / 100 + 1) < 8) && causeCheck(this, ((j + 1) * 100) + 200, ((i + 1) * 100))) {
				showMovement[(y / 100) + 1][((x - 200) / 100 + 1)] = 1;
			}
			else if (showPieces[(y / 100) + 1][((x - 200) / 100 + 1)] == 2 && ((y / 100) + 1 < 8) && (((x - 200) / 100 + 1) < 8) && causeCheck(this, ((j + 1) * 100) + 200, ((i + 1) * 100))) {
				showMovement[(y / 100) + 1][((x - 200) / 100 + 1)] = 1;
			}
			//Left Bottom
			if (showPieces[(y / 100) - 1][((x - 200) / 100 - 1)] != 2 && showPieces[(y / 100) - 1][((x - 200) / 100 - 1)] != 3 && (((x - 200) / 100 - 1) >= 0) && ((y / 100) - 1 >= 0) && causeCheck(this, ((j - 1) * 100) + 200, ((i - 1) * 100))) {
				showMovement[(y / 100) - 1][((x - 200) / 100 - 1)] = 1;
			}
			else if (showPieces[(y / 100) - 1][((x - 200) / 100 - 1)] == 2 && (((x - 200) / 100 - 1) >= 0) && ((y / 100) - 1 >= 0) && causeCheck(this, ((j - 1) * 100) + 200, ((i - 1) * 100))) {
				showMovement[(y / 100) - 1][((x - 200) / 100 - 1)] = 1;
			}
			//Right Bottom
			if (showPieces[(y / 100) - 1][((x - 200) / 100 + 1)] != 2 && showPieces[(y / 100) - 1][((x - 200) / 100 + 1)] != 3 && (((x - 200) / 100 + 1) < 8) && ((y / 100) - 1 >= 0) && causeCheck(this, ((j + 1) * 100) + 200, ((i - 1) * 100))) {
				showMovement[(y / 100) - 1][((x - 200) / 100 + 1)] = 1;
			}
			else if (showPieces[(y / 100) - 1][((x - 200) / 100 + 1)] == 2 && (((x - 200) / 100 + 1) < 8) && ((y / 100) - 1 >= 0) && causeCheck(this, ((j + 1) * 100) + 200, ((i - 1) * 100))) {
				showMovement[(y / 100) - 1][((x - 200) / 100 + 1)] = 1;
			}
		}
		else {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					showMovement[i][j] = 0;
				}
			}
			boolToggleShowMovement = false;
		}
	}
	void drawPiece() {
		int i = x; int j = y;
		DrawRoundRect(i + 25, j + 10, 50, 8, pieceColor, 6);
		DrawRoundRect(i + 32, j + 18, 36, 2, pieceColor, 4);
		DrawLine(i + 34, j + 23, i + 65, j + 23, 2, pieceColor);
		DrawLine(i + 33, j + 25, i + 67, j + 25, 2, pieceColor);
		DrawLine(i + 31, j + 27, i + 69, j + 27, 2, pieceColor);
		DrawLine(i + 33, j + 29, i + 67, j + 29, 2, pieceColor);
		DrawLine(i + 35, j + 31, i + 65, j + 31, 2, pieceColor);
		DrawLine(i + 37, j + 33, i + 63, j + 33, 2, pieceColor);
		DrawLine(i + 39, j + 35, i + 61, j + 35, 2, pieceColor);
		DrawLine(i + 37, j + 37, i + 63, j + 37, 2, pieceColor);
		DrawLine(i + 39, j + 39, i + 61, j + 39, 2, pieceColor);
		DrawLine(i + 40, j + 41, i + 60, j + 41, 2, pieceColor);
		DrawLine(i + 41, j + 43, i + 59, j + 43, 2, pieceColor);
		DrawLine(i + 42, j + 45, i + 58, j + 45, 2, pieceColor);
		DrawLine(i + 43, j + 47, i + 57, j + 47, 2, pieceColor);
		DrawLine(i + 44, j + 49, i + 56, j + 49, 2, pieceColor);
		DrawLine(i + 44, j + 51, i + 56, j + 51, 2, pieceColor);
		DrawLine(i + 43, j + 53, i + 57, j + 53, 2, pieceColor);
		DrawLine(i + 42, j + 55, i + 58, j + 55, 2, pieceColor);
		DrawLine(i + 40, j + 57, i + 60, j + 57, 4, pieceColor);
		DrawLine(i + 37, j + 62, i + 63, j + 62, 6, pieceColor);
		DrawLine(i + 43, j + 65, i + 57, j + 65, 2, pieceColor);
		DrawLine(i + 42, j + 66, i + 58, j + 66, 2, pieceColor);
		DrawLine(i + 41, j + 68, i + 59, j + 68, 2, pieceColor);
		DrawLine(i + 40, j + 70, i + 60, j + 70, 2, pieceColor);
		DrawLine(i + 39, j + 72, i + 61, j + 72, 2, pieceColor);
		DrawLine(i + 38, j + 74, i + 62, j + 74, 2, pieceColor);
		DrawLine(i + 37, j + 76, i + 63, j + 76, 2, pieceColor);
		DrawLine(i + 36, j + 78, i + 64, j + 78, 2, pieceColor);
		DrawLine(i + 35, j + 80, i + 65, j + 80, 2, pieceColor);
		DrawLine(i + 44, j + 82, i + 56, j + 82, 3, pieceColor);
		DrawString(i + 43, j + 82, "+",	pieceColor);
	}
};

class Queen :public ChessPiece {
private:
public:
	Queen(int x = 4, int y = 0, float* c = colors[BLACK], bool isVirtual = false, char* ch = (char*)"Queen") :ChessPiece(x, y, ch, c, isVirtual) {
	}
	char* getPieceName(int a, int b) {
		if (a == x && b == y)
			return pieceName;
		return (char*)"";
	}
	void toggleShowMovement() {
		if (!boolToggleShowMovement) {
			boolToggleShowMovement = true;
			// Down
			for (int i = (y / 100)-1, j = ((x-200) / 100); i >= 0; i--) {
				if (pieceColor == colors[BLACK]) {
					if (showPieces[i][j] != 2 && showPieces[i][j] != 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}else if (showPieces[i][j] == 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if(showPieces[i][j] == 2) {
						break;
					}
				}
				else if (pieceColor == colors[WHITE]) {
					if (showPieces[i][j] != 3 && showPieces[i][j] != 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					} else if (showPieces[i][j] == 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 3) {
						break;
					}
				}
			}
			// UP
			for (int i = (y / 100) + 1, j = (x - 200) / 100; i < 8 && j >= 0; i++) {
				if (pieceColor == colors[BLACK]) {
					if (showPieces[i][j] != 2 && showPieces[i][j] != 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 2) {
						break;
					}
				}
				else if (pieceColor == colors[WHITE]) {
					if (showPieces[i][j] != 3 && showPieces[i][j] != 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 3) {
						break;
					}
				}
			}
			// Right
			for (int i = (y / 100), j = ((x - 200) / 100)+1; j < 8; j++) {
				if (pieceColor == colors[BLACK]) {
					if (showPieces[i][j] != 2 && showPieces[i][j] != 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 2) {
						break;
					}
				}
				else if (pieceColor == colors[WHITE]) {
					if (showPieces[i][j] != 3 && showPieces[i][j] != 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 3) {
						break;
					}
				}
			}
			// Left
			for (int i = (y / 100), j = ((x - 200) / 100) - 1; j >= 0; j--) {
				if (pieceColor == colors[BLACK]) {
					if (showPieces[i][j] != 2 && showPieces[i][j] != 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 2) {
						break;
					}
				}
				else if (pieceColor == colors[WHITE]) {
					if (showPieces[i][j] != 3 && showPieces[i][j] != 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 3) {
						break;
					}
				}
			}
			for (int i = (y/100)-1, j = ((x - 200) / 100)-1; i >= 0 && j >= 0; i--, j--) {
				if (pieceColor == colors[BLACK]) {
					if (showPieces[i][j] != 2 && showPieces[i][j] != 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 2) {
						break;
					}
				}
				else if (pieceColor == colors[WHITE]) {
					if (showPieces[i][j] != 3 && showPieces[i][j] != 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 3) {
						break;
					}
				}
			}
			for (int i = (y / 100) + 1, j = ((x - 200) / 100)+1; i < 8 && j < 8; i++, j++) {
				if (pieceColor == colors[BLACK]) {
					if (showPieces[i][j] != 2 && showPieces[i][j] != 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 2) {
						break;
					}
				}
				else if (pieceColor == colors[WHITE]) {
					if (showPieces[i][j] != 3 && showPieces[i][j] != 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 3) {
						break;
					}
				}
			}
			for (int i = (y / 100)+1, j = ((x - 200) / 100)-1; j >= 0 && i < 8; i++, j--) {
				if (pieceColor == colors[BLACK]) {
					if (showPieces[i][j] != 2 && showPieces[i][j] != 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 2) {
						break;
					}
				}
				else if (pieceColor == colors[WHITE]) {
					if (showPieces[i][j] != 3 && showPieces[i][j] != 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 3) {
						break;
					}
				}
			}
			for (int i = (y / 100)-1, j = ((x - 200) / 100)+1; j < 8 && i >=0; i--, j++) {
				if (pieceColor == colors[BLACK]) {
					if (showPieces[i][j] != 2 && showPieces[i][j] != 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 2) {
						break;
					}
				}
				else if (pieceColor == colors[WHITE]) {
					if (showPieces[i][j] != 3 && showPieces[i][j] != 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 3) {
						break;
					}
				}
			}
		}
		else {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if(showMovement[i][j] == 1)
						showMovement[i][j] = 0;
				}
			}
			boolToggleShowMovement = false;
		}
	}

	void drawPiece() {
		DrawRoundRect(x + 25, y + 10, 50, 8, pieceColor, 6);
		DrawRoundRect(x + 32, y + 18, 36, 2, pieceColor, 4);
		DrawLine(x + 34, y + 23, x + 65, y + 23, 2, pieceColor);
		DrawLine(x + 33, y + 25, x + 67, y + 25, 2, pieceColor);
		DrawLine(x + 31, y + 27, x + 69, y + 27, 2, pieceColor);
		DrawLine(x + 33, y + 29, x + 67, y + 29, 2, pieceColor);
		DrawLine(x + 35, y + 31, x + 65, y + 31, 2, pieceColor);
		DrawLine(x + 37, y + 33, x + 63, y + 33, 2, pieceColor);
		DrawLine(x + 39, y + 35, x + 61, y + 35, 2, pieceColor);
		DrawLine(x + 37, y + 37, x + 63, y + 37, 2, pieceColor);
		DrawLine(x + 39, y + 39, x + 61, y + 39, 2, pieceColor);
		DrawLine(x + 40, y + 41, x + 60, y + 41, 2, pieceColor);
		DrawLine(x + 41, y + 43, x + 59, y + 43, 2, pieceColor);
		DrawLine(x + 42, y + 45, x + 58, y + 45, 2, pieceColor);
		DrawLine(x + 43, y + 47, x + 57, y + 47, 2, pieceColor);
		DrawLine(x + 44, y + 49, x + 56, y + 49, 2, pieceColor);
		DrawLine(x + 44, y + 51, x + 56, y + 51, 2, pieceColor);
		DrawLine(x + 43, y + 53, x + 57, y + 53, 2, pieceColor);
		DrawLine(x + 42, y + 55, x + 58, y + 55, 2, pieceColor);
		DrawLine(x + 40, y + 58, x + 60, y + 58, 4, pieceColor);
		DrawLine(x + 40, y + 61, x + 60, y + 61, 4, pieceColor);
		DrawLine(x + 43, y + 64, x + 57, y + 64, 2, pieceColor);
		DrawLine(x + 42, y + 66, x + 58, y + 66, 2, pieceColor);
		DrawLine(x + 41, y + 68, x + 59, y + 68, 2, pieceColor);
		DrawLine(x + 40, y + 70, x + 60, y + 70, 2, pieceColor);
		DrawLine(x + 39, y + 72, x + 61, y + 72, 2, pieceColor);
		DrawLine(x + 38, y + 74, x + 62, y + 74, 2, pieceColor);
		DrawLine(x + 37, y + 76, x + 63, y + 76, 2, pieceColor);
		DrawLine(x + 36, y + 78, x + 64, y + 78, 2, pieceColor);
		DrawLine(x + 35, y + 80, x + 65, y + 80, 2, pieceColor);
		DrawString(x + 34, y + 74, "vvv", pieceColor);
		DrawCircle(x + 50, y + 80, 10, pieceColor);
		DrawCircle(x + 50, y + 93, 5, pieceColor);
	}
};

class Rook:public ChessPiece {
public:
	Rook(int x = 0, int y = 0, float* c = colors[BLACK], bool isVirtual = false, char* ch = (char*)"Rook") :ChessPiece(x, y, ch, c, isVirtual) {
	}
	char* getPieceName(int a, int b) {
		if (a == x && b == y)
			return pieceName;
		return (char*)"";
	}
	void toggleShowMovement() {
		if (!boolToggleShowMovement) {
			boolToggleShowMovement = true;
			// Down
			for (int i = (y / 100) - 1, j = ((x - 200) / 100); i >= 0; i--) {
				if (pieceColor == colors[BLACK]) {
					if (showPieces[i][j] != 2 && showPieces[i][j] != 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 2) {
						break;
					}
				}
				else if (pieceColor == colors[WHITE]) {
					if (showPieces[i][j] != 3 && showPieces[i][j] != 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 3) {
						break;
					}
				}
			}
			// UP
			for (int i = (y / 100) + 1, j = (x - 200) / 100; i < 8 && j >= 0; i++) {
				if (pieceColor == colors[BLACK]) {
					if (showPieces[i][j] != 2 && showPieces[i][j] != 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 2) {
						break;
					}
				}
				else if (pieceColor == colors[WHITE]) {
					if (showPieces[i][j] != 3 && showPieces[i][j] != 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 3) {
						break;
					}
				}
			}
			// Right
			for (int i = (y / 100), j = ((x - 200) / 100) + 1; j < 8; j++) {
				if (pieceColor == colors[BLACK]) {
					if (showPieces[i][j] != 2 && showPieces[i][j] != 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 2) {
						break;
					}
				}
				else if (pieceColor == colors[WHITE]) {
					if (showPieces[i][j] != 3 && showPieces[i][j] != 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 3) {
						break;
					}
				}
			}
			// Left
			for (int i = (y / 100), j = ((x - 200) / 100) - 1; j >= 0; j--) {
				if (pieceColor == colors[BLACK]) {
					if (showPieces[i][j] != 2 && showPieces[i][j] != 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 2) {
						break;
					}
				}
				else if (pieceColor == colors[WHITE]) {
					if (showPieces[i][j] != 3 && showPieces[i][j] != 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 3) {
						break;
					}
				}
			}
		}
		else {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (showMovement[i][j] == 1)
						showMovement[i][j] = 0;
				}
			}
			boolToggleShowMovement = false;
		}
	}
	void drawPiece() {
		int i = x; int j = y;
		DrawRoundRect(i + 25, j + 10, 50, 9, pieceColor, 6);
		DrawRoundRect(i + 32, j + 18, 36, 3, pieceColor, 4);
		DrawLine(i + 34, j + 21, i + 65, j + 21, 2, pieceColor);
		DrawLine(i + 33, j + 23, i + 66, j + 23, 2, pieceColor);
		DrawLine(i + 32, j + 25, i + 67, j + 25, 2, pieceColor);
		DrawLine(i + 31, j + 27, i + 68, j + 27, 2, pieceColor);
		DrawLine(i + 32, j + 29, i + 67, j + 29, 2, pieceColor);
		DrawLine(i + 34, j + 31, i + 65, j + 31, 2, pieceColor);
		DrawLine(i + 36, j + 33, i + 63, j + 33, 2, pieceColor);
		DrawRoundRect(i + 33, j + 33, 33, 6, pieceColor, 4);
		DrawLine(i + 37, j + 35, i + 62, j + 35, 2, pieceColor);
		DrawLine(i + 38, j + 37, i + 61, j + 37, 2, pieceColor);
		DrawLine(i + 39, j + 39, i + 60, j + 39, 2, pieceColor);
		DrawLine(i + 40, j + 41, i + 59, j + 41, 2, pieceColor);
		DrawLine(i + 40, j + 43, i + 59, j + 43, 2, pieceColor);
		DrawLine(i + 41, j + 45, i + 58, j + 45, 2, pieceColor);
		DrawLine(i + 41, j + 47, i + 58, j + 47, 2, pieceColor);
		DrawLine(i + 42, j + 49, i + 57, j + 49, 2, pieceColor);
		DrawLine(i + 42, j + 51, i + 57, j + 51, 2, pieceColor);
		DrawLine(i + 43, j + 53, i + 56, j + 53, 2, pieceColor);
		DrawLine(i + 43, j + 55, i + 56, j + 55, 2, pieceColor);
		DrawLine(i + 44, j + 57, i + 55, j + 57, 2, pieceColor);
		DrawLine(i + 44, j + 59, i + 55, j + 59, 2, pieceColor);
		DrawLine(i + 43, j + 61, i + 56, j + 61, 2, pieceColor);
		DrawLine(i + 42, j + 63, i + 57, j + 63, 2, pieceColor);
		DrawRoundRect(i + 35, j + 64, 30, 7, pieceColor, 3);
		DrawRectangle(i + 35, j + 70, 31, 7, pieceColor);
		DrawRectangle(i + 35, j + 70, 7, 15, pieceColor);
		DrawRectangle(i + 43, j + 70, 7, 15, pieceColor);
		DrawRectangle(i + 51, j + 70, 7, 15, pieceColor);
		DrawRectangle(i + 59, j + 70, 7, 15, pieceColor);
	}
};

class Bishop :public ChessPiece {
public:
	Bishop(int x = 2, int y = 0, float* c = colors[BLACK], bool isVirtual = false, char* ch = (char*)"Bishop") :ChessPiece(x, y, ch, c, isVirtual) {
	}
	char* getPieceName(int a, int b) {
		if (a == x && b == y)
			return pieceName;
		return (char*)"";
	}
	void toggleShowMovement() {
		if (!boolToggleShowMovement) {
			boolToggleShowMovement = true;
			for (int i = (y / 100) - 1, j = ((x - 200) / 100) - 1; i >= 0 && j >= 0; i--, j--) {
				if (pieceColor == colors[BLACK]) {
					if (showPieces[i][j] != 2 && showPieces[i][j] != 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 2) {
						break;
					}
				}
				else if (pieceColor == colors[WHITE]) {
					if (showPieces[i][j] != 3 && showPieces[i][j] != 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 3) {
						break;
					}
				}
			}
			for (int i = (y / 100) + 1, j = ((x - 200) / 100) + 1; i < 8 && j < 8; i++, j++) {
				if (pieceColor == colors[BLACK]) {
					if (showPieces[i][j] != 2 && showPieces[i][j] != 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 2) {
						break;
					}
				}
				else if (pieceColor == colors[WHITE]) {
					if (showPieces[i][j] != 3 && showPieces[i][j] != 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 3) {
						break;
					}
				}
			}
			for (int i = (y / 100) + 1, j = ((x - 200) / 100) - 1; j >= 0 && i < 8; i++, j--) {
				if (pieceColor == colors[BLACK]) {
					if (showPieces[i][j] != 2 && showPieces[i][j] != 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 2) {
						break;
					}
				}
				else if (pieceColor == colors[WHITE]) {
					if (showPieces[i][j] != 3 && showPieces[i][j] != 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 3) {
						break;
					}
				}
			}
			for (int i = (y / 100) - 1, j = ((x - 200) / 100) + 1; j < 8 && i >= 0; i--, j++) {
				if (pieceColor == colors[BLACK]) {
					if (showPieces[i][j] != 2 && showPieces[i][j] != 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 3 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 2) {
						break;
					}
				}
				else if (pieceColor == colors[WHITE]) {
					if (showPieces[i][j] != 3 && showPieces[i][j] != 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
					}
					else if (showPieces[i][j] == 2 && causeCheck(this, (j * 100) + 200, ((i) * 100))) {
						showMovement[i][j] = 1;
						break;
					}
					else if (showPieces[i][j] == 3) {
						break;
					}
				}
			}
		}
		else {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (showMovement[i][j] == 1)
						showMovement[i][j] = 0;
				}
			}
			boolToggleShowMovement = false;
		}
	}
	void drawPiece() {
		int i = x; int j = y;
		DrawRoundRect(i + 25, j + 10, 50, 8, pieceColor, 6);
		DrawRoundRect(i + 32, j + 18, 36, 2, pieceColor, 4);
		DrawLine(i + 34, j + 23, i + 65, j + 23, 2, pieceColor);
		DrawLine(i + 33, j + 25, i + 67, j + 25, 2, pieceColor);
		DrawLine(i + 31, j + 27, i + 69, j + 27, 2, pieceColor);
		DrawLine(i + 33, j + 29, i + 67, j + 29, 2, pieceColor);
		DrawLine(i + 35, j + 31, i + 65, j + 31, 2, pieceColor);
		DrawLine(i + 37, j + 33, i + 63, j + 33, 2, pieceColor);
		DrawLine(i + 39, j + 35, i + 61, j + 35, 2, pieceColor);
		DrawLine(i + 42, j + 37, i + 58, j + 37, 2, pieceColor);
		DrawLine(i + 39, j + 39, i + 61, j + 39, 2, pieceColor);
		DrawLine(i + 39, j + 41, i + 61, j + 41, 2, pieceColor);
		DrawLine(i + 40, j + 43, i + 60, j + 43, 2, pieceColor);
		DrawLine(i + 41, j + 45, i + 59, j + 45, 2, pieceColor);
		DrawLine(i + 42, j + 47, i + 58, j + 47, 2, pieceColor);
		DrawLine(i + 43, j + 49, i + 57, j + 49, 2, pieceColor);
		DrawLine(i + 44, j + 51, i + 56, j + 51, 2, pieceColor);
		DrawLine(i + 44, j + 53, i + 56, j + 53, 2, pieceColor);
		DrawLine(i + 43, j + 55, i + 57, j + 55, 2, pieceColor);
		DrawLine(i + 42, j + 57, i + 58, j + 57, 2, pieceColor);
		DrawRoundRect(i + 39, j + 58, 22, 6, pieceColor, 3);
		DrawRoundRect(i + 42, j + 64, 16, 4, pieceColor, 3);
		DrawLine(i + 42, j + 69, i + 58, j + 69, 2, pieceColor);
		DrawLine(i + 40, j + 71, i + 60, j + 71, 2, pieceColor);
		DrawLine(i + 38, j + 73, i + 62, j + 73, 2, pieceColor);
		DrawLine(i + 36, j + 75, i + 64, j + 75, 2, pieceColor);
		DrawLine(i + 37, j + 77, i + 63, j + 77, 2, pieceColor);
		DrawLine(i + 38, j + 79, i + 62, j + 79, 2, pieceColor);
		DrawLine(i + 39, j + 81, i + 45, j + 81, 2, pieceColor);
		DrawLine(i + 47, j + 81, i + 61, j + 81, 2, pieceColor);
		DrawLine(i + 40, j + 83, i + 44, j + 83, 2, pieceColor);
		DrawLine(i + 46, j + 83, i + 60, j + 83, 2, pieceColor);
		DrawLine(i + 41, j + 85, i + 43, j + 85, 2, pieceColor);
		DrawLine(i + 45, j + 85, i + 59, j + 85, 2, pieceColor);
		DrawLine(i + 42, j + 87, i + 42, j + 87, 2, pieceColor);
		DrawLine(i + 44, j + 87, i + 58, j + 87, 2, pieceColor);
		DrawLine(i + 41, j + 89, i + 59, j + 89, 3, pieceColor);
	}
};
class Knight :public ChessPiece {
public:
	Knight(int x = 1, int y = 0, float* c = colors[BLACK], bool isVirtual = false, char* ch = (char*)"Knight") :ChessPiece(x, y, ch, c, isVirtual) {
	}
	char* getPieceName(int a, int b) {
		if (a == x && b == y)
			return pieceName;
		return (char*)"";
	}
	void toggleShowMovement() {
		if (!boolToggleShowMovement) {
			boolToggleShowMovement = true;
			int i = y / 100, j = (x - 200) / 100;
			if (pieceColor == colors[BLACK]) {
				// Down Left L Black
				if (showPieces[i-2][j-1] != 2 && showPieces[i-2][j-1] != 3 && (i - 2 >= 0) && (j-1 >= 0) && causeCheck(this, ((j-1)*100)+200, (i-2)*100)) {
					showMovement[i-2][j-1] = 1;
				}
				else if (showPieces[i-2][j-1] == 3 && (i - 2 >= 0) && (j - 1 >= 0) && causeCheck(this, ((j - 1) * 100) + 200, (i - 2) * 100)) {
					showMovement[i-2][j-1] = 1;
				}
				// Down Right L Black
				if (showPieces[i - 2][j + 1] != 2 && showPieces[i - 2][j - 1] != 3 && (i - 2 >= 0) && (j + 1 < 8) && causeCheck(this, ((j + 1) * 100) + 200, (i - 2) * 100)) {
					showMovement[i - 2][j + 1] = 1;
				}
				else if (showPieces[i - 2][j + 1] == 3 && (i - 2 >= 0) && (j + 1 < 8) && causeCheck(this, ((j + 1) * 100) + 200, (i - 2) * 100)) {
					showMovement[i - 2][j + 1] = 1;
				}
			}
			else if (pieceColor == colors[WHITE]) {
				// Down Left L White
				if (showPieces[i - 2][j - 1] != 2 && showPieces[i - 2][j - 1] != 3 && (i - 2 >= 0) && (j - 1 >= 0) && causeCheck(this, ((j - 1) * 100) + 200, (i - 2) * 100)) {
					showMovement[i - 2][j - 1] = 1;
				}
				else if (showPieces[i - 2][j - 1] == 2 && (i - 2 >= 0) && (j - 1 >= 0) && causeCheck(this, ((j - 1) * 100) + 200, (i - 2) * 100)) {
					showMovement[i - 2][j - 1] = 1;
				}
				// Down Right L White
				if (showPieces[i - 2][j + 1] != 2 && showPieces[i - 2][j - 1] != 3 && (i - 2 >= 0) && (j + 1 < 8) && causeCheck(this, ((j + 1) * 100) + 200, (i - 2) * 100)) {
					showMovement[i - 2][j + 1] = 1;
				}
				else if (showPieces[i - 2][j + 1] == 2 && (i - 2 >= 0) && (j + 1 < 8) && causeCheck(this, ((j + 1) * 100) + 200, (i - 2) * 100)) {
					showMovement[i - 2][j + 1] = 1;
				}
			}



			if (pieceColor == colors[BLACK]) {
				// Up Left L Black
				if (showPieces[i + 2][j - 1] != 2 && showPieces[i + 2][j - 1] != 3 && (i + 2 < 8) && (j - 1 >= 0) && causeCheck(this, ((j - 1) * 100) + 200, (i + 2) * 100)) {
					showMovement[i + 2][j - 1] = 1;
				}
				else if (showPieces[i + 2][j - 1] == 3 && (i + 2 < 8) && (j - 1 >= 0) && causeCheck(this, ((j - 1) * 100) + 200, (i + 2) * 100)) {
					showMovement[i + 2][j - 1] = 1;
				}
				// Up Right L Black
				if (showPieces[i + 2][j + 1] != 2 && showPieces[i + 2][j + 1] != 3 && (i + 2 < 8) && (j + 1 < 8) && causeCheck(this, ((j + 1) * 100) + 200, (i + 2) * 100)) {
					showMovement[i + 2][j + 1] = 1;
				}
				else if (showPieces[i + 2][j + 1] == 3 && (i + 2 < 8) && (j + 1 < 8) && causeCheck(this, ((j + 1) * 100) + 200, (i + 2) * 100)) {
					showMovement[i + 2][j + 1] = 1;
				}
			}
			else if (pieceColor == colors[WHITE]) {
				// Up Left L Black
				if (showPieces[i + 2][j - 1] != 2 && showPieces[i + 2][j - 1] != 3 && (i + 2 < 8) && (j - 1 >= 0) && causeCheck(this, ((j - 1) * 100) + 200, (i + 2) * 100)) {
					showMovement[i + 2][j - 1] = 1;
				}
				else if (showPieces[i + 2][j - 1] == 2 && (i + 2 < 8) && (j - 1 >= 0) && causeCheck(this, ((j - 1) * 100) + 200, (i + 2) * 100)) {
					showMovement[i + 2][j - 1] = 1;
				}
				// Up Right L Black
				if (showPieces[i + 2][j + 1] != 2 && showPieces[i + 2][j + 1] != 3 && (i + 2 < 8) && (j + 1 < 8) && causeCheck(this, ((j + 1) * 100) + 200, (i + 2) * 100)) {
					showMovement[i + 2][j + 1] = 1;
				}
				else if (showPieces[i + 2][j + 1] == 2 && (i + 2 < 8) && (j + 1 < 8) && causeCheck(this, ((j + 1) * 100) + 200, (i + 2) * 100)) {
					showMovement[i + 2][j + 1] = 1;
				}
			}



			if (pieceColor == colors[BLACK]) {
				// Right Up L Black
				if (showPieces[i + 1][j + 2] != 2 && showPieces[i + 1][j + 2] != 3 && (i + 1 < 8) && (j + 2 < 8) && causeCheck(this, ((j + 2) * 100) + 200, (i + 1) * 100)) {
					showMovement[i + 1][j + 2] = 1;
				}
				else if (showPieces[i + 1][j + 2] == 3 && (i + 1 < 8) && (j + 2 < 8) && causeCheck(this, ((j + 2) * 100) + 200, (i + 1) * 100)) {
					showMovement[i + 1][j + 2] = 1;
				}
				// Right Down L Black
				if (showPieces[i - 1][j + 2] != 2 && showPieces[i - 1][j + 2] != 3 && (i - 1 >= 0) && (j + 2 < 8) && causeCheck(this, ((j + 2) * 100) + 200, (i - 1) * 100)) {
					showMovement[i - 1][j + 2] = 1;
				}
				else if (showPieces[i - 1][j + 2] == 3 && (i - 1 >= 0) && (j + 2 < 8) && causeCheck(this, ((j + 2) * 100) + 200, (i - 1) * 100)) {
					showMovement[i - 1][j + 2] = 1;
				}
			}
			else if (pieceColor == colors[WHITE]) {
				// Right Up L Black
				if (showPieces[i + 1][j + 2] != 2 && showPieces[i + 1][j + 2] != 3 && (i + 1 < 8) && (j + 2 < 8) && causeCheck(this, ((j + 2) * 100) + 200, (i + 1) * 100)) {
					showMovement[i + 1][j + 2] = 1;
				}
				else if (showPieces[i + 1][j + 2] == 2 && (i + 1 < 8) && (j + 2 < 8) && causeCheck(this, ((j + 2) * 100) + 200, (i + 1) * 100)) {
					showMovement[i + 1][j + 2] = 1;
				}
				// Right Down L Black
				if (showPieces[i - 1][j + 2] != 2 && showPieces[i - 1][j + 2] != 3 && (i - 1 >= 0) && (j + 2 < 8) && causeCheck(this, ((j + 2) * 100) + 200, (i - 1) * 100)) {
					showMovement[i - 1][j + 2] = 1;
				}
				else if (showPieces[i - 1][j + 2] == 2 && (i - 1 >= 0) && (j + 2 < 8) && causeCheck(this, ((j + 2) * 100) + 200, (i - 1) * 100)) {
					showMovement[i - 1][j + 2] = 1;
				}
			}


			if (pieceColor == colors[BLACK]) {
				// Left Up L Black
				if (showPieces[i + 1][j - 2] != 2 && showPieces[i + 1][j - 2] != 3 && (i + 1 < 8) && (j - 2 >= 0) && causeCheck(this, ((j - 2) * 100) + 200, (i + 1) * 100)) {
					showMovement[i + 1][j - 2] = 1;
				}
				else if (showPieces[i + 1][j - 2] == 3 && (i + 1 < 8) && (j - 2 >= 0) && causeCheck(this, ((j - 2) * 100) + 200, (i + 1) * 100)) {
					showMovement[i + 1][j - 2] = 1;
				}
				// Left Down L Black
				if (showPieces[i - 1][j - 2] != 2 && showPieces[i - 1][j - 2] != 3 && (i - 1 >= 0) && (j - 2 >= 0) && causeCheck(this, ((j - 2) * 100) + 200, (i - 1) * 100)) {
					showMovement[i - 1][j - 2] = 1;
				}
				else if (showPieces[i - 1][j - 2] == 3 && (i - 1 >= 0) && (j - 2 >= 0) && causeCheck(this, ((j - 2) * 100) + 200, (i - 1) * 100)) {
					showMovement[i - 1][j - 2] = 1;
				}
			}
			else if (pieceColor == colors[WHITE]) {
				// Left Up L Black
				if (showPieces[i + 1][j - 2] != 2 && showPieces[i + 1][j - 2] != 3 && (i + 1 < 8) && (j - 2 >= 0) && causeCheck(this, ((j - 2) * 100) + 200, (i + 1) * 100)) {
					showMovement[i + 1][j - 2] = 1;
				}
				else if (showPieces[i + 1][j - 2] == 2 && (i + 1 < 8) && (j - 2 >= 0) && causeCheck(this, ((j - 2) * 100) + 200, (i + 1) * 100)) {
					showMovement[i + 1][j - 2] = 1;
				}
				// Left Down L Black
				if (showPieces[i - 1][j - 2] != 2 && showPieces[i - 1][j - 2] != 3 && (i - 1 >= 0) && (j - 2 >= 0) && causeCheck(this, ((j - 2) * 100) + 200, (i - 1) * 100)) {
					showMovement[i - 1][j - 2] = 1;
				}
				else if (showPieces[i - 1][j - 2] == 2 && (i - 1 >= 0) && (j - 2 >= 0) && causeCheck(this, ((j - 2) * 100) + 200, (i - 1) * 100)) {
					showMovement[i - 1][j - 2] = 1;
				}
			}
		}
		else {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (showMovement[i][j] == 1)
						showMovement[i][j] = 0;
				}
			}
			boolToggleShowMovement = false;
		}
	}
	void drawPiece() {
		int i = x; int j = y;

		DrawRoundRect(i + 25, j + 10, 50, 8, pieceColor, 6);
		DrawRoundRect(i + 32, j + 18, 36, 2, pieceColor, 4);
		DrawLine(i + 34, j + 21, i + 65, j + 21, 2, pieceColor);
		DrawLine(i + 33, j + 23, i + 66, j + 23, 2, pieceColor);
		DrawLine(i + 32, j + 25, i + 67, j + 25, 2, pieceColor);
		DrawLine(i + 31, j + 27, i + 68, j + 27, 2, pieceColor);
		DrawLine(i + 32, j + 29, i + 67, j + 29, 2, pieceColor);
		DrawLine(i + 34, j + 31, i + 65, j + 31, 2, pieceColor);
		DrawLine(i + 36, j + 33, i + 63, j + 33, 2, pieceColor);
		DrawRoundRect(i + 33, j + 33, 33, 5, pieceColor, 4);
		DrawLine(i + 35, j + 35, i + 62, j + 35, 2, pieceColor);
		DrawLine(i + 33, j + 37, i + 60, j + 37, 2, pieceColor);
		DrawLine(i + 31, j + 39, i + 58, j + 39, 2, pieceColor);
		DrawLine(i + 29, j + 41, i + 56, j + 41, 2, pieceColor);
		DrawLine(i + 29, j + 43, i + 56, j + 43, 2, pieceColor);
		DrawLine(i + 31, j + 45, i + 58, j + 45, 2, pieceColor);
		DrawLine(i + 33, j + 47, i + 60, j + 47, 2, pieceColor);
		DrawLine(i + 35, j + 49, i + 62, j + 49, 2, pieceColor);
		DrawLine(i + 35, j + 51, i + 62, j + 51, 2, pieceColor);
		DrawLine(i + 32, j + 53, i + 65, j + 53, 2, pieceColor);
		DrawLine(i + 29, j + 55, i + 63, j + 55, 2, pieceColor);
		DrawLine(i + 26, j + 57, i + 61, j + 57, 2, pieceColor);
		DrawLine(i + 23, j + 59, i + 59, j + 59, 2, pieceColor);
		DrawLine(i + 20, j + 61, i + 57, j + 61, 2, pieceColor);
		DrawLine(i + 22, j + 63, i + 55, j + 63, 2, pieceColor);
		DrawLine(i + 24, j + 65, i + 53, j + 65, 2, pieceColor);
		DrawLine(i + 25, j + 67, i + 38, j + 67, 2, pieceColor);
		DrawLine(i + 26, j + 67, i + 80, j + 67, 2, pieceColor);
		DrawLine(i + 27, j + 69, i + 77, j + 69, 2, pieceColor);
		DrawLine(i + 28, j + 71, i + 75, j + 71, 2, pieceColor);
		DrawLine(i + 29, j + 73, i + 73, j + 73, 2, pieceColor);
		DrawLine(i + 30, j + 75, i + 71, j + 75, 2, pieceColor);
		DrawLine(i + 32, j + 77, i + 69, j + 77, 2, pieceColor);
		DrawLine(i + 34, j + 79, i + 72, j + 79, 2, pieceColor);
		DrawLine(i + 36, j + 81, i + 74, j + 81, 2, pieceColor);
		DrawLine(i + 38, j + 83, i + 76, j + 83, 2, pieceColor);
		DrawLine(i + 40, j + 85, i + 78, j + 85, 2, pieceColor);
		DrawLine(i + 43, j + 87, i + 75, j + 87, 2, pieceColor);
		DrawLine(i + 46, j + 89, i + 72, j + 89, 2, pieceColor);
		DrawCircle(i + 67, j + 73, 2, pieceColor);
		DrawLine(i + 62, j + 65, i + 79, j + 65, 2, pieceColor);
		DrawLine(i + 63, j + 63, i + 78, j + 63, 2, pieceColor);
		DrawLine(i + 65, j + 61, i + 77, j + 61, 2, pieceColor);
		DrawLine(i + 67, j + 59, i + 75, j + 59, 2, pieceColor);
		DrawLine(i + 70, j + 57, i + 75, j + 57, 2, pieceColor);
		DrawLine(i + 75, j + 59, i + 77, j + 59, 2, pieceColor);
		DrawLine(i + 76, j + 57, i + 78, j + 57, 2, pieceColor);
	}
};

class Pawn :public ChessPiece {
public:
	Pawn(int x = 0, int y = 1, float* c = colors[BLACK], bool isVirtual = false, char* ch = (char*)"Pawn") :ChessPiece(x, y, ch, c, isVirtual) {
	}

	void toggleShowMovement() {
		if (!boolToggleShowMovement) {
			boolToggleShowMovement = true;
			int i = y / 100, j = (x - 200) / 100;

			if (pieceColor == colors[BLACK]) {
				if (showPieces[i + 1][j] != 2 && showPieces[i + 1][j] != 3 && (i == 1) && causeCheck(this, (j*100), ((i+1)*100)+200)) {
					showMovement[i + 1][j] = 1;
				}
				if (showPieces[i + 1][j] != 2 && showPieces[i + 1][j] != 3 && showPieces[i + 2][j] != 2 && showPieces[i + 2][j] != 3 && (i == 1) && causeCheck(this, (j * 100), ((i + 2) * 100) + 200)) {
					showMovement[i + 2][j] = 1;
				}
				if (showPieces[i + 1][j] != 2 && showPieces[i + 1][j] != 3 && causeCheck(this, (j * 100), ((i + 1) * 100)+200)) {
					showMovement[i + 1][j] = 1;
				}
				if (showPieces[i + 1][j - 1] == 3 && causeCheck(this, ((j-1) * 100), ((i + 1) * 100) + 200)) {
					showMovement[i + 1][j - 1] = 1;
				}
				if (showPieces[i + 1][j + 1] == 3 && causeCheck(this, ((j+1) * 100), ((i + 1) * 100) + 200)) {
					showMovement[i + 1][j + 1] = 1;
				}
			}
			else if (pieceColor == colors[WHITE]) {
				if (showPieces[i - 1][j] != 2 && showPieces[i - 1][j] != 3 && (i == 6) && causeCheck(this, (j * 100), ((i - 1) * 100) + 200)) {
					showMovement[i - 1][j] = 1;
				}
				if (showPieces[i - 1][j] != 2 && showPieces[i - 1][j] != 3 && showPieces[i - 2][j] != 2 && showPieces[i - 2][j] != 3 && (i == 6) && causeCheck(this, (j * 100), ((i - 2) * 100) + 200)) {
					showMovement[i - 2][j] = 1;
				}
				if (showPieces[i - 1][j] != 2 && showPieces[i - 1][j] != 3 && causeCheck(this, (j * 100), ((i - 1) * 100) + 200)) {
					showMovement[i - 1][j] = 1;
				}
				if (showPieces[i - 1][j - 1] == 2 && causeCheck(this, ((j - 1) * 100), ((i - 1) * 100) + 200)) {
					showMovement[i - 1][j - 1] = 1;
				}
				if (showPieces[i - 1][j + 1] == 2 && causeCheck(this, ((j + 1) * 100), ((i - 1) * 100) + 200)) {
					showMovement[i - 1][j + 1] = 1;
				}
			}
		}
		else {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (showMovement[i][j] == 1)
						showMovement[i][j] = 0;
				}
			}
			boolToggleShowMovement = false;
		}
	}
	
	void drawPiece() {
		int i = x; int j = y;
		DrawRoundRect(i + 25, j + 15, 50, 8, pieceColor, 6);
		DrawRoundRect(i + 32, j + 22, 36, 2, pieceColor, 4);
		DrawRoundRect(i + 30, j + 25, 40, 17, pieceColor, 10);
		DrawLine(i + 39, j + 42, i + 61, j + 42, 2, pieceColor);
		DrawLine(i + 40, j + 44, i + 60, j + 44, 2, pieceColor);
		DrawLine(i + 41, j + 46, i + 59, j + 46, 2, pieceColor);
		DrawLine(i + 42, j + 48, i + 58, j + 48, 2, pieceColor);
		DrawLine(i + 43, j + 50, i + 57, j + 50, 2, pieceColor);
		DrawLine(i + 44, j + 52, i + 56, j + 52, 2, pieceColor);
		DrawLine(i + 42, j + 54, i + 58, j + 54, 2, pieceColor);
		DrawLine(i + 40, j + 56, i + 60, j + 56, 2, pieceColor);
		DrawLine(i + 38, j + 58, i + 62, j + 58, 2, pieceColor);
		DrawLine(i + 40, j + 60, i + 60, j + 60, 2, pieceColor);
		DrawLine(i + 42, j + 62, i + 58, j + 62, 2, pieceColor);
		DrawLine(i + 44, j + 64, i + 56, j + 64, 2, pieceColor);
		DrawCircle(i + 50, j + 69, 10, pieceColor);
	}
};

//bool causeCheck(ChessPiece* ptr, int x, int y) {
//	int x0, y0, temp = 0;
//	x0 = ptr->getXCoords();
//	y0 = ptr->getYCoords();
//	/*ChessPiece* tempPiece;
//	char* piece;
//	piece = ptr->getPieceName(x0, y0);
//
//
//	int showPiecesCpy[8][8];
//	int showMovementCpy[8][8];
//	for (int i = 0; i < 8; i++) {
//		for (int j = 0; j < 8; j++) {
//			showPiecesCpy[i][j] = showPieces[i][j];
//			showMovementCpy[i][j] = showMovement[i][j];
//		}
//	}*/
//
//	if (ptr->getPieceColor() == colors[BLACK]) {
//		/*if (piece == (char*)"King") {
//			tempPiece = new King((x - 200) / 100, y / 100, colors[BLACK], true);
//		}
//		else if (piece == (char*)"Queen") {
//			tempPiece = new Queen((x - 200) / 100, y / 100, colors[BLACK], true);
//		}
//		else if (piece == (char*)"Rook") {
//			tempPiece = new Rook((x - 200) / 100, y / 100, colors[BLACK], true);
//		}
//		else if (piece == (char*)"Knight") {
//			tempPiece = new Knight((x - 200) / 100, y / 100, colors[BLACK], true);
//		}
//		else if (piece == (char*)"Bishop") {
//			tempPiece = new Bishop((x - 200) / 100, y / 100, colors[BLACK], true);
//		}
//		else if (piece == (char*)"Pawn") {
//			tempPiece = new Pawn((x - 200) / 100, y / 100, colors[BLACK], true);
//		}
//		showPiecesCpy[y0 / 100][((x0 - 200) / 100)] = 0;
//		showPiecesCpy[y / 100][((x - 200) / 100)] = 2;*/
//		for (int i = (p1[0]->getYCoords() / 100) - 1, j = ((p1[0]->getXCoords() - 200) / 100); i >= 0; i--) {
//			if (showPieces[i][j] == 2)
//				break;
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
//						cout << "BLACK check With Queen or Rook in BL\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//		}
//		for (int i = (p1[0]->getYCoords() / 100) + 1, j = ((p1[0]->getXCoords() - 200) / 100); i < 8; i++) {
//			if (showPieces[i][j] == 2) {
//				break;
//			}
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
//						cout << "BLACK check With Queen or Rook in TL\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//		}
//		for (int i = (p1[0]->getYCoords() / 100), j = ((p1[0]->getXCoords() - 200) / 100) + 1; j < 8; j++) {
//			if (showPieces[i][j] == 2)
//				break;
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
//						cout << "BLACK check With Queen or Rook in RL\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//		}
//		for (int i = (p1[0]->getYCoords() / 100), j = ((p1[0]->getXCoords() - 200) / 100) - 1; j >= 0; j--) {
//			if (showPieces[i][j] == 2)
//				break;
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
//						cout << "BLACK check With Queen or Rook in LL\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//		}
//		for (int i = (p1[0]->getYCoords() / 100) - 1, j = ((p1[0]->getXCoords() - 200) / 100) - 1; i >= 0 && j >= 0; i--, j--) {
//			if (showPieces[i][j] == 2)
//				break;
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
//						cout << "BLACK check With Queen or Bishop in LBD\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//		}
//		for (int i = (p1[0]->getYCoords() / 100) + 1, j = ((p1[0]->getXCoords() - 200) / 100) + 1; i < 8 && j < 8; i++, j++) {
//			if (showPieces[i][j] == 2)
//				break;
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
//						cout << "BLACK check With Queen or Bishop in RTD\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//		}
//		for (int i = (p1[0]->getYCoords() / 100) + 1, j = ((p1[0]->getXCoords() - 200) / 100) - 1; j >= 0 && i < 8; i++, j--) {
//			if (showPieces[i][j] == 2)
//				break;
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
//						cout << "-------------BLACK check With Queen or Bishop in LTD\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//			else {
//				break;
//			}
//		}
//		for (int i = (p1[0]->getYCoords() / 100) - 1, j = ((p1[0]->getXCoords() - 200) / 100) + 1; j < 8 && i >= 0; i--, j++) {
//			if (showPieces[i][j] == 2)
//				break;
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
//						cout << "BLACK check With Queen or Bishop in RBD\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//		}
//
//		int i = p1[0]->getYCoords() / 100;
//		int j = (p1[0]->getXCoords() / 100) - 200;
//		for (int k = 0; k < 16; k++) {
//			if (/*Down Left L*/(p2[k]->getPieceName(((j - 1) * 100) + 200, (i - 2) * 100) == (char*)"Knight" && (i - 2 >= 0) && (j - 1 >= 0)) || /*Down Right L*/(p2[k]->getPieceName(((j + 1) * 100) + 200, (i - 2) * 100) == (char*)"Knight" && (i - 2 >= 0) && (j + 1 < 8)) || /*Up left L*/(p2[k]->getPieceName(((j - 1) * 100) + 200, (i + 2) * 100) == (char*)"Knight" && (i + 2 < 8) && (j - 1 >= 0)) || /*Up Right L*/(p2[k]->getPieceName(((j + 1) * 100) + 200, (i + 2) * 100) == (char*)"Knight" && (i + 2 < 8) && (j + 1 < 8)) || /*Right Up L*/(p2[k]->getPieceName(((j + 2) * 100) + 200, (i + 1) * 100) == (char*)"Knight" && (i + 1 < 8) && (j + 2 < 8)) || /*Right Down*/(p2[k]->getPieceName(((j + 2) * 100) + 200, (i - 1) * 100) == (char*)"Knight" && (i - 1 >= 0) && (j + 2 < 8)) || /*Left Up*/(p2[k]->getPieceName(((j - 2) * 100) + 200, (i + 1) * 100) == (char*)"Knight" && (i + 1 < 8) && (j - 2 >= 0)) || /*Left Down*/(p2[k]->getPieceName(((j - 2) * 100) + 200, (i - 1) * 100) == (char*)"Knight" && (i - 1 >= 0) && (j - 2 >= 0))) {
//				cout << "BLACK check With Knight\n";
//				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//				showPieces[y / 100][((x - 200) / 100)] = 0;
//				ptr->setXYCoords(x0, y0);
//				return false;
//			}
//		}
//		// Pawn
//		i = p1[0]->getYCoords() / 100;
//		j = (p1[0]->getXCoords() / 100) - 200;
//		for (int k = 0; k < 16; k++) {
//			if (/*Up left*/(p2[k]->getPieceName(((j - 1) * 100) + 200, (i + 1) * 100) == (char*)"Pawn" && (i + 1 < 8) && (j - 1 >= 0)) || /*Up Right*/(p2[k]->getPieceName(((j + 1) * 100) + 200, (i + 1) * 100) == (char*)"Pawn" && (i + 1 < 8) && (j + 1 < 8))) {
//				cout << "BLACK check With Pawn\n";
//				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//				showPieces[y / 100][((x - 200) / 100)] = 0;
//				ptr->setXYCoords(x0, y0);
//				return false;
//			}
//		}
//		showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//		showPieces[y / 100][((x - 200) / 100)] = 0;
//		ptr->setXYCoords(x0, y0);
//		return true;
//	}
//	else if (ptr->getPieceColor() == colors[WHITE]) {
//		/*if (piece == (char*)"King") {
//			tempPiece = new King((x - 200) / 100, y / 100, colors[WHITE], true);
//		}
//		else if (piece == (char*)"Queen") {
//			tempPiece = new Queen((x - 200) / 100, y / 100, colors[WHITE], true);
//		}
//		else if (piece == (char*)"Rook") {
//			tempPiece = new Rook((x - 200) / 100, y / 100, colors[WHITE], true);
//		}
//		else if (piece == (char*)"Knight") {
//			tempPiece = new Knight((x - 200) / 100, y / 100, colors[WHITE], true);
//		}
//		else if (piece == (char*)"Bishop") {
//			tempPiece = new Bishop((x - 200) / 100, y / 100, colors[WHITE], true);
//		}
//		else if (piece == (char*)"Pawn") {
//			tempPiece = new Pawn((x - 200) / 100, y / 100, colors[WHITE], true);
//		}
//		showPiecesCpy[y0 / 100][((x0 - 200) / 100)] = 0;
//		showPiecesCpy[y0 / 100][((x0 - 200) / 100)] = 3;*/
//		for (int i = (p1[0]->getYCoords() / 100) - 1, j = ((p1[0]->getXCoords() - 200) / 100); i >= 0; i--) {
//			if (showPieces[i][j] == 2)
//				break;
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
//						cout << "BLACK check With Queen or Rook in BL\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//		}
//		for (int i = (p1[0]->getYCoords() / 100) + 1, j = ((p1[0]->getXCoords() - 200) / 100); i < 8; i++) {
//			if (showPieces[i][j] == 2) {
//				break;
//			}
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
//						cout << "BLACK check With Queen or Rook in TL\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//		}
//		for (int i = (p1[0]->getYCoords() / 100), j = ((p1[0]->getXCoords() - 200) / 100) + 1; j < 8; j++) {
//			if (showPieces[i][j] == 2)
//				break;
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
//						cout << "BLACK check With Queen or Rook in RL\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//		}
//		for (int i = (p1[0]->getYCoords() / 100), j = ((p1[0]->getXCoords() - 200) / 100) - 1; j >= 0; j--) {
//			if (showPieces[i][j] == 2)
//				break;
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
//						cout << "BLACK check With Queen or Rook in LL\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//		}
//		for (int i = (p1[0]->getYCoords() / 100) - 1, j = ((p1[0]->getXCoords() - 200) / 100) - 1; i >= 0 && j >= 0; i--, j--) {
//			if (showPieces[i][j] == 2)
//				break;
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
//						cout << "BLACK check With Queen or Bishop in LBD\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//		}
//		for (int i = (p1[0]->getYCoords() / 100) + 1, j = ((p1[0]->getXCoords() - 200) / 100) + 1; i < 8 && j < 8; i++, j++) {
//			if (showPieces[i][j] == 2)
//				break;
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
//						cout << "BLACK check With Queen or Bishop in RTD\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//		}
//		for (int i = (p1[0]->getYCoords() / 100) + 1, j = ((p1[0]->getXCoords() - 200) / 100) - 1; j >= 0 && i < 8; i++, j--) {
//			if (showPieces[i][j] == 2)
//				break;
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
//						cout << "-------------BLACK check With Queen or Bishop in LTD\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//			else {
//				break;
//			}
//		}
//		for (int i = (p1[0]->getYCoords() / 100) - 1, j = ((p1[0]->getXCoords() - 200) / 100) + 1; j < 8 && i >= 0; i--, j++) {
//			if (showPieces[i][j] == 2)
//				break;
//			if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//				for (int k = 0; k < 16; k++) {
//					if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
//						cout << "BLACK check With Queen or Bishop in RBD\n";
//						showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//						showPieces[y / 100][((x - 200) / 100)] = 0;
//						ptr->setXYCoords(x0, y0);
//						return false;
//					}
//				}
//			}
//		}
//
//		int i = p1[0]->getYCoords() / 100;
//		int j = (p1[0]->getXCoords() / 100) - 200;
//		for (int k = 0; k < 16; k++) {
//			if (/*Down Left L*/(p2[k]->getPieceName(((j - 1) * 100) + 200, (i - 2) * 100) == (char*)"Knight" && (i - 2 >= 0) && (j - 1 >= 0)) || /*Down Right L*/(p2[k]->getPieceName(((j + 1) * 100) + 200, (i - 2) * 100) == (char*)"Knight" && (i - 2 >= 0) && (j + 1 < 8)) || /*Up left L*/(p2[k]->getPieceName(((j - 1) * 100) + 200, (i + 2) * 100) == (char*)"Knight" && (i + 2 < 8) && (j - 1 >= 0)) || /*Up Right L*/(p2[k]->getPieceName(((j + 1) * 100) + 200, (i + 2) * 100) == (char*)"Knight" && (i + 2 < 8) && (j + 1 < 8)) || /*Right Up L*/(p2[k]->getPieceName(((j + 2) * 100) + 200, (i + 1) * 100) == (char*)"Knight" && (i + 1 < 8) && (j + 2 < 8)) || /*Right Down*/(p2[k]->getPieceName(((j + 2) * 100) + 200, (i - 1) * 100) == (char*)"Knight" && (i - 1 >= 0) && (j + 2 < 8)) || /*Left Up*/(p2[k]->getPieceName(((j - 2) * 100) + 200, (i + 1) * 100) == (char*)"Knight" && (i + 1 < 8) && (j - 2 >= 0)) || /*Left Down*/(p2[k]->getPieceName(((j - 2) * 100) + 200, (i - 1) * 100) == (char*)"Knight" && (i - 1 >= 0) && (j - 2 >= 0))) {
//				cout << "BLACK check With Knight\n";
//				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//				showPieces[y / 100][((x - 200) / 100)] = 0;
//				ptr->setXYCoords(x0, y0);
//				return false;
//			}
//		}
//		// Pawn
//		i = p1[0]->getYCoords() / 100;
//		j = (p1[0]->getXCoords() / 100) - 200;
//		for (int k = 0; k < 16; k++) {
//			if (/*Up left*/(p2[k]->getPieceName(((j - 1) * 100) + 200, (i + 1) * 100) == (char*)"Pawn" && (i + 1 < 8) && (j - 1 >= 0)) || /*Up Right*/(p2[k]->getPieceName(((j + 1) * 100) + 200, (i + 1) * 100) == (char*)"Pawn" && (i + 1 < 8) && (j + 1 < 8))) {
//				cout << "BLACK check With Pawn\n";
//				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//				showPieces[y / 100][((x - 200) / 100)] = 0;
//				ptr->setXYCoords(x0, y0);
//				return false;
//			}
//		}
//		showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//		showPieces[y / 100][((x - 200) / 100)] = 0;
//		ptr->setXYCoords(x0, y0);
//		return true;
//	}
//	if (ptr->getPieceColor() == colors[BLACK]) {
//		
//
//
//
//
//		////////////////////////////////////////////////////////////
//		//showPieces[y0 / 100][((x0 - 200) / 100)] = 0;
//		//showPieces[y / 100][(x - 200) / 100] = 2;
//		//for (int i = (p1[0]->getYCoords() / 100) - 1, j = ((p1[0]->getXCoords() - 200) / 100); i >= 0; i--) {
//		//	if (showPieces[i][j] == 2)
//		//		break;
//		//	if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//		//		for (int k = 0; k < 16; k++) {
//		//			if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
//		//				cout << "BLACK check With Queen or Rook in BL\n";
//		//				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//		//				showPieces[y / 100][((x - 200) / 100)] = 0;
//		//				ptr->setXYCoords(x0, y0);
//		//				return false;
//		//			}
//		//		}
//		//	}
//		//}
//		//for (int i = (p1[0]->getYCoords() / 100) + 1, j = ((p1[0]->getXCoords() - 200) / 100); i < 8; i++) {
//		//	if (showPieces[i][j] == 2) {
//		//		break;
//		//	}
//		//	if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//		//		for (int k = 0; k < 16; k++) {
//		//			if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
//		//				cout << "BLACK check With Queen or Rook in TL\n";
//		//				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//		//				showPieces[y / 100][((x - 200) / 100)] = 0;
//		//				ptr->setXYCoords(x0, y0);
//		//				return false;
//		//			}
//		//		}
//		//	}
//		//}
//		//for (int i = (p1[0]->getYCoords() / 100), j = ((p1[0]->getXCoords() - 200) / 100) + 1; j < 8; j++) {
//		//	if (showPieces[i][j] == 2)
//		//		break;
//		//	if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//		//		for (int k = 0; k < 16; k++) {
//		//			if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
//		//				cout << "BLACK check With Queen or Rook in RL\n";
//		//				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//		//				showPieces[y / 100][((x - 200) / 100)] = 0;
//		//				ptr->setXYCoords(x0, y0);
//		//				return false;
//		//			}
//		//		}
//		//	}
//		//}
//		//for (int i = (p1[0]->getYCoords() / 100), j = ((p1[0]->getXCoords() - 200) / 100) - 1; j >= 0; j--) {
//		//	if (showPieces[i][j] == 2)
//		//		break;
//		//	if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//		//		for (int k = 0; k < 16; k++) {
//		//			if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Rook") {
//		//				cout << "BLACK check With Queen or Rook in LL\n";
//		//				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//		//				showPieces[y / 100][((x - 200) / 100)] = 0;
//		//				ptr->setXYCoords(x0, y0);
//		//				return false;
//		//			}
//		//		}
//		//	}
//		//}
//		//for (int i = (p1[0]->getYCoords() / 100) - 1, j = ((p1[0]->getXCoords() - 200) / 100) - 1; i >= 0 && j >= 0; i--, j--) {
//		//	if (showPieces[i][j] == 2)
//		//		break;
//		//	if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//		//		for (int k = 0; k < 16; k++) {
//		//			if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
//		//				cout << "BLACK check With Queen or Bishop in LBD\n";
//		//				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//		//				showPieces[y / 100][((x - 200) / 100)] = 0;
//		//				ptr->setXYCoords(x0, y0);
//		//				return false;
//		//			}
//		//		}
//		//	}
//		//}
//		//for (int i = (p1[0]->getYCoords() / 100) + 1, j = ((p1[0]->getXCoords() - 200) / 100) + 1; i < 8 && j < 8; i++, j++) {
//		//	if (showPieces[i][j] == 2)
//		//		break;
//		//	if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//		//		for (int k = 0; k < 16; k++) {
//		//			if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
//		//				cout << "BLACK check With Queen or Bishop in RTD\n";
//		//				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//		//				showPieces[y / 100][((x - 200) / 100)] = 0;
//		//				ptr->setXYCoords(x0, y0);
//		//				return false;
//		//			}
//		//		}
//		//	}
//		//}
//		//for (int i = (p1[0]->getYCoords() / 100) + 1, j = ((p1[0]->getXCoords() - 200) / 100) - 1; j >= 0 && i < 8; i++, j--) {
//		//	if (showPieces[i][j] == 2)
//		//		break;
//		//	if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//		//		for (int k = 0; k < 16; k++) {
//		//			if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
//		//				cout << "-------------BLACK check With Queen or Bishop in LTD\n";
//		//				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//		//				showPieces[y / 100][((x - 200) / 100)] = 0;
//		//				ptr->setXYCoords(x0, y0);
//		//				return false;
//		//			} 
//		//		}
//		//	}
//		//	else {
//		//		break;
//		//	}
//		//}
//		//for (int i = (p1[0]->getYCoords() / 100) - 1, j = ((p1[0]->getXCoords() - 200) / 100) + 1; j < 8 && i >= 0; i--, j++) {
//		//	if (showPieces[i][j] == 2)
//		//		break;
//		//	if (showPieces[i][j] == 3 || showPieces[i][j] == 0) {
//		//		for (int k = 0; k < 16; k++) {
//		//			if (p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Queen" || p2[k]->getPieceName((j * 100) + 200, i * 100) == (char*)"Bishop") {
//		//				cout << "BLACK check With Queen or Bishop in RBD\n";
//		//				showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//		//				showPieces[y / 100][((x - 200) / 100)] = 0;
//		//				ptr->setXYCoords(x0, y0);
//		//				return false;
//		//			}
//		//		}
//		//	}
//		//}
//
//		//// Knight
//		//int i = p1[0]->getYCoords()/100;
//		//int j = (p1[0]->getXCoords()/100) - 200;
//		//for (int k = 0; k < 16; k++) {
//		//	if (/*Down Left L*/(p2[k]->getPieceName(((j - 1) * 100) + 200, (i - 2) * 100) == (char*)"Knight" && (i - 2 >= 0) && (j - 1 >= 0)) || /*Down Right L*/(p2[k]->getPieceName(((j + 1) * 100) + 200, (i - 2) * 100) == (char*)"Knight" && (i - 2 >= 0) && (j + 1 < 8)) || /*Up left L*/(p2[k]->getPieceName(((j - 1) * 100) + 200, (i + 2) * 100) == (char*)"Knight" && (i + 2 < 8) && (j - 1 >= 0)) || /*Up Right L*/(p2[k]->getPieceName(((j + 1) * 100) + 200, (i + 2) * 100) == (char*)"Knight" && (i + 2 < 8) && (j + 1 < 8)) || /*Right Up L*/(p2[k]->getPieceName(((j + 2) * 100) + 200, (i + 1) * 100) == (char*)"Knight" && (i + 1 < 8) && (j + 2 < 8)) || /*Right Down*/(p2[k]->getPieceName(((j + 2) * 100) + 200, (i - 1) * 100) == (char*)"Knight" && (i - 1 >= 0) && (j + 2 < 8)) || /*Left Up*/(p2[k]->getPieceName(((j - 2) * 100) + 200, (i + 1) * 100) == (char*)"Knight" && (i + 1 < 8) && (j - 2 >= 0)) || /*Left Down*/(p2[k]->getPieceName(((j - 2) * 100) + 200, (i - 1) * 100) == (char*)"Knight" && (i - 1 >= 0) && (j - 2 >= 0))) {
//		//		cout << "BLACK check With Knight\n";
//		//		showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//		//		showPieces[y / 100][((x - 200) / 100)] = 0;
//		//		ptr->setXYCoords(x0, y0);
//		//		return false;
//		//	}
//		//}
//		//// Pawn
//		//i = p1[0]->getYCoords() / 100;
//		//j = (p1[0]->getXCoords() / 100) - 200;
//		//for (int k = 0; k < 16; k++) {
//		//	if (/*Up left*/(p2[k]->getPieceName(((j - 1) * 100) + 200, (i + 1) * 100) == (char*)"Pawn" && (i + 1 < 8) && (j - 1 >= 0)) || /*Up Right*/(p2[k]->getPieceName(((j + 1) * 100) + 200, (i + 1) * 100) == (char*)"Pawn" && (i + 1 < 8) && (j + 1 < 8))) {
//		//		cout << "BLACK check With Pawn\n";
//		//		showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//		//		showPieces[y / 100][((x - 200) / 100)] = 0;
//		//		ptr->setXYCoords(x0, y0);
//		//		return false;
//		//	}
//		//}
//		//showPieces[y0 / 100][((x0 - 200) / 100)] = 2;
//		//showPieces[y / 100][((x - 200) / 100)] = 0;
//		//ptr->setXYCoords(x0, y0);
//		//return true;
//	/*}
//	else if (ptr->getPieceColor() == colors[WHITE]) {
//		showPieces[y0 / 100][((x0 - 200) / 100)] = 3;
//		showPieces[y / 100][((x - 200) / 100)] = 0;
//		ptr->setXYCoords(x0, y0);
//		return true;
//	}*/
//}
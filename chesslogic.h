#ifndef CHESSLOGIC_H
#define CHESSLOGIC_H

#include <bits/stdc++.h>

const int sz = 8;

extern int board[sz][sz];
extern bool ColorNow;
extern bool ColorUser;

enum Piece {
    EMPTY = -1,
    WPAWN = 0, WKNIGHT, WBISHOP, WROOK, WQUEEN, WKING,
    BPAWN, BKNIGHT, BBISHOP, BROOK, BQUEEN, BKING
};

using Move = std::array<int, 4>;

void InitBoard();
bool isWhite(int p);
bool isBlack(int p);
bool is_good(int i, int j);
std::vector <int> GenerateWMoves(const int board[sz][sz]);
std::vector <int> GenerateBMoves(const int board[sz][sz]);
Move decodeMove(int move);
int addMove(int fx, int fy, int tx, int ty, bool isCapture);

extern std::vector<int> moves;
extern std::vector<int> captures;
#endif // CHESSLOGIC_H

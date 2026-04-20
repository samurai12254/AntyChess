#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <bits/stdc++.h>
using namespace std;
const int sz = 8;
int board[sz][sz];
bool ColorNow = 0;
bool ColorUser;
#define Move array<int,4>
enum Piece {
    EMPTY = -1,

    WPAWN = 0,
    WKNIGHT,
    WBISHOP,
    WROOK,
    WQUEEN,
    WKING,

    BPAWN,
    BKNIGHT,
    BBISHOP,
    BROOK,
    BQUEEN,
    BKING
};
void InitBoard(){
    for(int i = 0;i < sz;i++){
        for(int j = 0;j < sz;j++){
            board[i][j] = -1;
        }
    }
    for(int i = 0;i < sz;i++){
        board[1][i] = BPAWN;
        board[6][i] = WPAWN;
    }
    board[0][0] = board[0][sz-1] = BROOK;
    board[0][1] = board[0][sz-2] = BKNIGHT;
    board[0][2] = board[0][sz-3] = BBISHOP;
    board[0][3] = BQUEEN;
    board[0][sz-4] = BKING;

    board[7][0] = board[7][sz-1] = WROOK;
    board[7][1] = board[7][sz-2] = WKNIGHT;
    board[7][2] = board[7][sz-3] = WBISHOP;
    board[7][3] = WQUEEN;
    board[7][sz-4] = WKING;

}
bool isWhite(int p) {
    return p >= WPAWN && p <= WKING;
}

bool isBlack(int p) {
    return p >= BPAWN && p <= BKING;
}
vector <int> BMoves,WMoves;
bool is_good(int i,int j){
    if(i < 0 || i >= sz)return 0;
    if(j < 0 || j >= sz)return 0;
    return 1;
}
vector<int> moves;
vector<int> captures;
int addMove(int fx, int fy, int tx, int ty, bool isCapture){
    int move = (fx << 9) | (fy << 6) | (tx << 3) | ty;
    if(isCapture) captures.push_back(move);
    else moves.push_back(move);
}
Move decodeMove(int move){
    int mask = 7;
    Move now;
    for(int i = 3;i >= 0;i--){
        now[i] = move & mask;
        move >>= 3;
    }
    return now;
}
void GenerateBMoves(){
    moves.clear();
    captures.clear();
    for(int i = 0; i < sz; i++){
        for(int j = 0; j < sz; j++){
            if(!isBlack(board[i][j])) continue;

            int now = board[i][j];
            int in, jn;

            if(now == BPAWN){
                in = i + 1;

                for(int d = -1; d <= 1; d += 2){
                    jn = j + d;
                    if(is_good(in, jn) && isWhite(board[in][jn])){
                        addMove(i, j, in, jn, true);
                    }
                }

                if(is_good(in, j) && board[in][j] == EMPTY){
                    addMove(i, j, in, j, false);

                    if(i == 1 && board[in+1][j] == EMPTY){
                        addMove(i, j, in+1, j, false);
                    }
                }
            }

            else if(now == BKING){
                for(int s1 = -1; s1 <= 1; s1++){
                    for(int s2 = -1; s2 <= 1; s2++){
                        if(s1 == 0 && s2 == 0) continue;

                        in = i + s1;
                        jn = j + s2;

                        if(!is_good(in, jn)) continue;

                        if(isWhite(board[in][jn]))
                            addMove(i, j, in, jn, true);
                        else if(board[in][jn] == EMPTY)
                            addMove(i, j, in, jn, false);
                    }
                }
            }

            else if(now == BROOK){
                int dx[4] = {0, 0, 1, -1};
                int dy[4] = {1, -1, 0, 0};

                for(int d = 0; d < 4; d++){
                    in = i + dx[d];
                    jn = j + dy[d];

                    while(is_good(in, jn)){
                        if(isWhite(board[in][jn])){
                            addMove(i, j, in, jn, true);
                            break;
                        }
                        if(isBlack(board[in][jn])) break;

                        addMove(i, j, in, jn, false);

                        in += dx[d];
                        jn += dy[d];
                    }
                }
            }

            else if(now == BKNIGHT){
                for(int s1 = -2; s1 <= 2; s1++){
                    for(int s2 = -2; s2 <= 2; s2++){
                        if(abs(s1) + abs(s2) != 3) continue;

                        in = i + s1;
                        jn = j + s2;

                        if(!is_good(in, jn)) continue;

                        if(isWhite(board[in][jn]))
                            addMove(i, j, in, jn, true);
                        else if(board[in][jn] == EMPTY)
                            addMove(i, j, in, jn, false);
                    }
                }
            }

            else if(now == BBISHOP){
                int dx[4] = {1, 1, -1, -1};
                int dy[4] = {1, -1, 1, -1};

                for(int d = 0; d < 4; d++){
                    in = i + dx[d];
                    jn = j + dy[d];

                    while(is_good(in, jn)){
                        if(isWhite(board[in][jn])){
                            addMove(i, j, in, jn, true);
                            break;
                        }
                        if(isBlack(board[in][jn])) break;

                        addMove(i, j, in, jn, false);

                        in += dx[d];
                        jn += dy[d];
                    }
                }
            }

            else if(now == BQUEEN){
                int dx[8] = {1,1,-1,-1,0,0,1,-1};
                int dy[8] = {1,-1,1,-1,1,-1,0,0};

                for(int d = 0; d < 8; d++){
                    in = i + dx[d];
                    jn = j + dy[d];

                    while(is_good(in, jn)){
                        if(isWhite(board[in][jn])){
                            addMove(i, j, in, jn, true);
                            break;
                        }
                        if(isBlack(board[in][jn])) break;

                        addMove(i, j, in, jn, false);

                        in += dx[d];
                        jn += dy[d];
                    }
                }
            }
        }
    }
    if(!captures.empty()) BMoves = captures;
    else BMoves = moves;
}
void GenerateWMoves(){
    moves.clear();
    captures.clear();
    for(int i = 0; i < sz; i++){
        for(int j = 0; j < sz; j++){
            if(!isWhite(board[i][j])) continue;
            int now = board[i][j];
            int in, jn;

            if(now == WPAWN){
                in = i + 1;

                for(int d = -1; d <= 1; d += 2){
                    jn = j + d;
                    if(is_good(in, jn) && isBlack(board[in][jn])){
                        addMove(i, j, in, jn, true);
                    }
                }

                if(is_good(in, j) && board[in][j] == EMPTY){
                    addMove(i, j, in, j, false);

                    if(i == 1 && board[in+1][j] == EMPTY){
                        addMove(i, j, in+1, j, false);
                    }
                }
            }

            else if(now == WKING){
                for(int s1 = -1; s1 <= 1; s1++){
                    for(int s2 = -1; s2 <= 1; s2++){
                        if(s1 == 0 && s2 == 0) continue;

                        in = i + s1;
                        jn = j + s2;

                        if(!is_good(in, jn)) continue;

                        if(isBlack(board[in][jn]))
                            addMove(i, j, in, jn, true);
                        else if(board[in][jn] == EMPTY)
                            addMove(i, j, in, jn, false);
                    }
                }
            }

            else if(now == WROOK){
                int dx[4] = {0, 0, 1, -1};
                int dy[4] = {1, -1, 0, 0};

                for(int d = 0; d < 4; d++){
                    in = i + dx[d];
                    jn = j + dy[d];

                    while(is_good(in, jn)){
                        if(isBlack(board[in][jn])){
                            addMove(i, j, in, jn, true);
                            break;
                        }
                        if(isWhite(board[in][jn])) break;

                        addMove(i, j, in, jn, false);

                        in += dx[d];
                        jn += dy[d];
                    }
                }
            }

            else if(now == WKNIGHT){
                for(int s1 = -2; s1 <= 2; s1++){
                    for(int s2 = -2; s2 <= 2; s2++){
                        if(abs(s1) + abs(s2) != 3) continue;

                        in = i + s1;
                        jn = j + s2;

                        if(!is_good(in, jn)) continue;

                        if(isBlack(board[in][jn]))
                            addMove(i, j, in, jn, true);
                        else if(board[in][jn] == EMPTY)
                            addMove(i, j, in, jn, false);
                    }
                }
            }

            else if(now == WBISHOP){
                int dx[4] = {1, 1, -1, -1};
                int dy[4] = {1, -1, 1, -1};

                for(int d = 0; d < 4; d++){
                    in = i + dx[d];
                    jn = j + dy[d];

                    while(is_good(in, jn)){
                        if(isBlack(board[in][jn])){
                            addMove(i, j, in, jn, true);
                            break;
                        }
                        if(isWhite(board[in][jn])) break;

                        addMove(i, j, in, jn, false);

                        in += dx[d];
                        jn += dy[d];
                    }
                }
            }

            else if(now == BQUEEN){
                int dx[8] = {1,1,-1,-1,0,0,1,-1};
                int dy[8] = {1,-1,1,-1,1,-1,0,0};

                for(int d = 0; d < 8; d++){
                    in = i + dx[d];
                    jn = j + dy[d];

                    while(is_good(in, jn)){
                        if(isBlack(board[in][jn])){
                            addMove(i, j, in, jn, true);
                            break;
                        }
                        if(isWhite(board[in][jn])) break;

                        addMove(i, j, in, jn, false);

                        in += dx[d];
                        jn += dy[d];
                    }
                }
            }
        }
    }
    if(!captures.empty()) WMoves = captures;
    else WMoves = moves;
}

void Simmulate(){
    if(ColorNow){
        ColorNow = !ColorNow;
        GenerateBMoves();
        if(BMoves.empty())return;
        Move now = decodeMove(BMoves.front());
        auto [i,j,in,jn] = now;
        board[in][jn] = board[i][j];
        board[i][j] = EMPTY;
    }else{
        ColorNow = !ColorNow;
        GenerateWMoves();
        if(WMoves.empty())return;
        Move now = decodeMove(WMoves.front());
        auto [i,j,in,jn] = now;
        board[in][jn] = board[i][j];
        board[i][j] = EMPTY;
    }
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

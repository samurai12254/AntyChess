#include "bot.h"
using namespace std ;
bot::bot() {
    figure_cost = {10, 20, 60, 30, 50, 15};
}
int localBoard[sz][sz];
using dist = uniform_int_distribution<int>;
mt19937 rng(67);
int pieceIndex(int p){
    if(isWhite(p))return p - WPAWN;
    return p - BPAWN;
}
int bot::heuristicV1(){
    int result = 0;

    for(int i = 0; i < sz; i++){
        for(int j = 0; j < sz; j++){
            int p = localBoard[i][j];

            if(p == EMPTY) continue;

            int value = figure_cost[pieceIndex(p)];

            bool isBotPiece = isWhite(p) == (ColorNow == 0);
            if(isBotPiece){
                result -= value;
            }else{
                result += value;
            }
        }
    }

    return result;
}

int bot0::selectMove(const int board[sz][sz],bool color){
    vector <int> legal;
    if(!color){
        legal = GenerateWMoves(board);
    }else{
        legal = GenerateBMoves(board);
    }
    if(legal.size() == 0)return -1;
    return legal[dist(0,legal.size()-1)(rng)];
}
int bot1::selectMove(const int board[sz][sz],bool color){
    for(int i = 0;i < sz;i++){
        for(int j = 0;j < sz;j++){
            localBoard[i][j] = board[i][j];
        }
    }
    return minimax(MAXDEEP,0,color).first;
}
pair<int,int> bot1::minimax(int max_deep,bool is_mini,bool color_now){
    if(max_deep == 0){
        return {-1,heuristicV1()};
    }

    vector <int> moves;

    if(color_now == 0){
        moves = GenerateWMoves(localBoard);
    }else{
        moves = GenerateBMoves(localBoard);
    }

    if(moves.empty()){
        return {-1, heuristicV1()};
    }

    int result;

    if(is_mini){
        result = INF;
    }else{
        result = -INF;
    }

    int best_move = -1;
    int pred1,pred2;
    pair<int,int> tmp;

    for(auto el : moves){
        Move move = decodeMove(el);

        pred1 = localBoard[move[0]][move[1]];
        pred2 = localBoard[move[2]][move[3]];

        localBoard[move[2]][move[3]] = localBoard[move[0]][move[1]];
        localBoard[move[0]][move[1]] = EMPTY;

        tmp = minimax(max_deep-1,!is_mini,!color_now);

        if(is_mini){
            if(best_move == -1 || tmp.second < result){
                best_move = el;
                result = tmp.second;
            }
        }else{
            if(best_move == -1 || tmp.second > result){
                best_move = el;
                result = tmp.second;
            }
        }

        localBoard[move[0]][move[1]] = pred1;
        localBoard[move[2]][move[3]] = pred2;
    }

    return {best_move,result};
}

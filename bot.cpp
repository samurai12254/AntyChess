#include "bot.h"
using namespace std ;
bot::bot() {
    figure_cost = {10, 20, 60, 30, 50, 15};
}
int localBoard[sz][sz];
using dist = uniform_int_distribution<int>;
mt19937 rng(67);
int bot::heuristicV1(){
    int result = 0;
    for(int i = 0;i < sz;i++){
        for(int j = 0;j < sz;j++){
            if(localBoard[i][j] == EMPTY)continue;
            if(isWhite(localBoard[i][j]) == (ColorNow == 0)){
                if(ColorNow == 0){
                    result += figure_cost[localBoard[i][j] % 8];
                }else{
                    result += figure_cost[localBoard[i][j] - BPAWN];
                }
            }else{
                if(ColorNow == 0){
                    result -= figure_cost[localBoard[i][j] - WPAWN];
                }else{
                    result -= figure_cost[localBoard[i][j] - BPAWN];
                }
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
    return minimax(MAXDEEP,1,color).first;
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
    int result;
    if(is_mini){
        result = INF;
    }else{
        result = -INF;
    }
    int best_move = -1;
    int pred1,pred2;
    pair<int,int> tmp;
    //без превращений
    for(auto el : moves){
        Move move = decodeMove(el);
        pred1 = localBoard[move[0]][move[1]];
        pred2 = localBoard[move[2]][move[3]];
        localBoard[move[2]][move[3]] = localBoard[move[0]][move[1]];
        localBoard[move[0]][move[1]] = EMPTY;
        tmp = minimax(max_deep-1,!is_mini,!color_now);
        if(is_mini && result > tmp.second){
            best_move = el;
            result = tmp.second;
        }else if(!is_mini && result < tmp.second){
            best_move = el;
            result = tmp.second;
        }
        localBoard[move[0]][move[1]] = pred1;
        localBoard[move[2]][move[3]] = pred2;
    }
    return {best_move,result};
}

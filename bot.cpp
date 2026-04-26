#include "bot.h"
using namespace std ;
bot::bot() {}
using dist = uniform_int_distribution<int>;
mt19937 rng(67);
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

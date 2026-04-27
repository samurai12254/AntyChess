#ifndef BOT_H
#define BOT_H
#include "chesslogic.h"
extern std::mt19937 rng;
extern int localBoard[sz][sz];
const int MAXDEEP = 5;
const int INF = 1e9;
class bot
{
public:
    virtual ~bot() = default;
    virtual int selectMove(const int board[sz][sz],bool color) = 0;
    int heuristicV1();
    std::vector<int> figure_cost;
    bot();
};
class bot0 : public bot{
public :
    bot0() = default;
    int selectMove(const int board[sz][sz],bool color)override;
};
class bot1: public bot{
public :
    bot1() = default;
    int selectMove(const int board[sz][sz],bool color)override;
    std::pair<int,int> minimax(int max_deep,bool is_mini,bool color_now);
};

#endif // BOT_H

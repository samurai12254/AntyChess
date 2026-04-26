#ifndef BOT_H
#define BOT_H
#include "chesslogic.h"
extern std::mt19937 rng;
class bot
{
public:
    virtual ~bot() = default;
    virtual int selectMove(const int board[sz][sz],bool color) = 0;
    bot();
};
struct bot0 : public bot{
public :
    bot0() = default;
    int selectMove(const int board[sz][sz],bool color)override;
};
#endif // BOT_H

#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "boardview.h"
#include "bot.h"
class GameWidget : public QWidget {
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
    void newGame(int type = -1,bool color_player = 0);

signals:
    void escapePressed();
protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onCellClicked(int row, int col);

private:
    BoardView *m_boardView;
    int m_selectedRow, m_selectedCol;
    bool m_hasSelection;
    bool color_player;
    int type_game;
    bot0 Bot0;
    bool tryMakeMove(int fromRow, int fromCol, int toRow, int toCol);
    void switchTurn();
    void checkGameOver();
    void SimulGame();
    int promotePawn();
};

#endif // GAMEWIDGET_H

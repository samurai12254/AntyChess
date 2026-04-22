#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "boardview.h"

class GameWidget : public QWidget {
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
    void newGame();

signals:
    void escapePressed();   // новый сигнал

protected:
    void keyPressEvent(QKeyEvent *event) override;   // для обработки клавиш

private slots:
    void onCellClicked(int row, int col);

private:
    BoardView *m_boardView;
    int m_selectedRow, m_selectedCol;
    bool m_hasSelection;

    bool tryMakeMove(int fromRow, int fromCol, int toRow, int toCol);
    void switchTurn();
    void checkGameOver();
};

#endif // GAMEWIDGET_H

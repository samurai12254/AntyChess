#include "gamewidget.h"
#include "chesslogic.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QKeyEvent>

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent), m_hasSelection(false)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    m_boardView = new BoardView(this);
    layout->addWidget(m_boardView);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    // Чтобы виджет мог принимать клавиатурные события
    setFocusPolicy(Qt::StrongFocus);

    connect(m_boardView, &BoardView::cellClicked, this, &GameWidget::onCellClicked);
}

void GameWidget::newGame()
{
    InitBoard();
    ColorNow = 0;
    m_hasSelection = false;
    m_boardView->clearSelection();
    m_boardView->updateBoard();
}

void GameWidget::onCellClicked(int row, int col)
{
    if (!m_hasSelection) {
        int piece = board[row][col];
        if ((ColorNow == 0 && isWhite(piece)) || (ColorNow == 1 && isBlack(piece))) {
            m_selectedRow = row;
            m_selectedCol = col;
            m_hasSelection = true;
            m_boardView->setSelected(row, col);
        }
    } else {
        int fromRow = m_selectedRow;
        int fromCol = m_selectedCol;
        m_hasSelection = false;
        m_boardView->clearSelection();

        if (tryMakeMove(fromRow, fromCol, row, col)) {
            switchTurn();
            m_boardView->updateBoard();
            checkGameOver();
        }
    }
}

bool GameWidget::tryMakeMove(int fromRow, int fromCol, int toRow, int toCol)
{
    if (ColorNow == 0) {
        GenerateWMoves();
        for (int moveCode : WMoves) {
            Move m = decodeMove(moveCode);
            if (m[0] == fromRow && m[1] == fromCol && m[2] == toRow && m[3] == toCol) {
                board[toRow][toCol] = board[fromRow][fromCol];
                board[fromRow][fromCol] = EMPTY;
                return true;
            }
        }
    } else {
        GenerateBMoves();
        for (int moveCode : BMoves) {
            Move m = decodeMove(moveCode);
            if (m[0] == fromRow && m[1] == fromCol && m[2] == toRow && m[3] == toCol) {
                board[toRow][toCol] = board[fromRow][fromCol];
                board[fromRow][fromCol] = EMPTY;
                return true;
            }
        }
    }
    return false;
}

void GameWidget::switchTurn()
{
    ColorNow = !ColorNow;
}

void GameWidget::checkGameOver()
{
    if (ColorNow == 0) {
        GenerateWMoves();
        if (WMoves.empty()) {
            QMessageBox::information(this, "Конец игры", "Белые выиграли (у чёрных нет ходов)!");
            newGame();
            return;
        }
    } else {
        GenerateBMoves();
        if (BMoves.empty()) {
            QMessageBox::information(this, "Конец игры", "Чёрные выиграли (у белых нет ходов)!");
            newGame();
            return;
        }
    }

    bool whiteHas = false, blackHas = false;
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) {
            int p = board[i][j];
            if (isWhite(p)) whiteHas = true;
            if (isBlack(p)) blackHas = true;
        }
    }
    if (!whiteHas) {
        QMessageBox::information(this, "Конец игры", "Белые выиграли (избавились от фигур)!");
        newGame();
    } else if (!blackHas) {
        QMessageBox::information(this, "Конец игры", "Чёрные выиграли (избавились от фигур)!");
        newGame();
    }
}

void GameWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        emit escapePressed();
        event->accept();
    } else {
        QWidget::keyPressEvent(event);
    }
}

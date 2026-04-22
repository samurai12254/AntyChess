#include "boardview.h"
#include "chesslogic.h"
#include <QPainter>
#include <QMouseEvent>

BoardView::BoardView(QWidget *parent)
    : QWidget(parent), m_hasSelection(false)
{
    setMinimumSize(400, 400);
}

void BoardView::setSelected(int row, int col)
{
    m_selectedRow = row;
    m_selectedCol = col;
    m_hasSelection = true;
    update();
}

void BoardView::clearSelection()
{
    m_hasSelection = false;
    update();
}

void BoardView::updateBoard()
{
    update();
}

void BoardView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int cellSize = std::min(width(), height()) / 8;
    int offsetX = (width() - cellSize * 8) / 2;
    int offsetY = (height() - cellSize * 8) / 2;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            QRect rect(offsetX + j * cellSize, offsetY + i * cellSize, cellSize, cellSize);

            // цвета клеток
            QColor light(238, 238, 210);
            QColor dark(118, 150, 86);
            painter.fillRect(rect, (i + j) % 2 == 0 ? light : dark);

            // подсветка выбранной клетки
            if (m_hasSelection && i == m_selectedRow && j == m_selectedCol) {
                painter.fillRect(rect, QColor(255, 255, 0, 100));
            }

            // фигура
            int piece = board[i][j];
            if (piece != EMPTY) {
                painter.setFont(QFont("Arial", cellSize * 0.7, QFont::Bold));
                painter.setPen((piece >= WPAWN && piece <= WKING) ? Qt::white : Qt::black);
                painter.drawText(rect, Qt::AlignCenter, pieceToChar(piece));
            }
        }
    }
}

void BoardView::mousePressEvent(QMouseEvent *event)
{
    int cellSize = std::min(width(), height()) / 8;
    int offsetX = (width() - cellSize * 8) / 2;
    int offsetY = (height() - cellSize * 8) / 2;

    int x = event->pos().x() - offsetX;
    int y = event->pos().y() - offsetY;
    if (x < 0 || y < 0 || x >= cellSize * 8 || y >= cellSize * 8) return;

    int col = x / cellSize;
    int row = y / cellSize;
    emit cellClicked(row, col);
}

QString BoardView::pieceToChar(int piece) const
{
    switch (piece) {
    case WPAWN:   return "♙";
    case WKNIGHT: return "♘";
    case WBISHOP: return "♗";
    case WROOK:   return "♖";
    case WQUEEN:  return "♕";
    case WKING:   return "♔";
    case BPAWN:   return "♟";
    case BKNIGHT: return "♞";
    case BBISHOP: return "♝";
    case BROOK:   return "♜";
    case BQUEEN:  return "♛";
    case BKING:   return "♚";
    default:      return "";
    }
}

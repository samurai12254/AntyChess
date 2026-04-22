#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QWidget>

class BoardView : public QWidget
{
    Q_OBJECT
public:
    explicit BoardView(QWidget *parent = nullptr);
    void setSelected(int row, int col);
    void clearSelection();
    void updateBoard();

signals:
    void cellClicked(int row, int col);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    int m_selectedRow;
    int m_selectedCol;
    bool m_hasSelection;
    QString pieceToChar(int piece) const;
};

#endif // BOARDVIEW_H

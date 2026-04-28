#include "gamewidget.h"
#include "chesslogic.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QTimer>
#include <QInputDialog>
using namespace std;
using dist = uniform_int_distribution<int>;
GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent), m_hasSelection(false)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    m_boardView = new BoardView(this);
    layout->addWidget(m_boardView);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    setFocusPolicy(Qt::StrongFocus);

    connect(m_boardView, &BoardView::cellClicked, this, &GameWidget::onCellClicked);
}

void GameWidget::newGame(int type,bool player)
{
    type_game = type;
    color_player = player;
    InitBoard();
    ColorNow = 0;
    m_hasSelection = false;
    m_boardView->clearSelection();
    m_boardView->updateBoard();
    if(color_player != ColorNow || type_game == 3){
        cout << "kok";
        QTimer::singleShot(300, this, &GameWidget::SimulGame);
    }
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
        vector <int> WMoves = GenerateWMoves(board);
        for (int moveCode : WMoves) {
            Move m = decodeMove(moveCode);
            if (m[0] == fromRow && m[1] == fromCol && m[2] == toRow && m[3] == toCol) {
                board[toRow][toCol] = board[fromRow][fromCol];
                board[fromRow][fromCol] = EMPTY;
                if(toRow == 0 && board[toRow][toCol] == WPAWN){
                    board[toRow][toCol] = promotePawn();
                }
                return true;
            }
        }
    } else {
        vector <int> BMoves = GenerateBMoves(board);
        for (int moveCode : BMoves) {
            Move m = decodeMove(moveCode);
            if (m[0] == fromRow && m[1] == fromCol && m[2] == toRow && m[3] == toCol) {
                board[toRow][toCol] = board[fromRow][fromCol];
                board[fromRow][fromCol] = EMPTY;
                if(toRow == 7 && board[toRow][toCol] == BPAWN){
                    board[toRow][toCol] = promotePawn();
                }
                return true;
            }
        }
    }
    return false;
}

void GameWidget::switchTurn()
{
    ColorNow = !ColorNow;
    if(ColorNow != color_player){
        QTimer::singleShot(300, this, &GameWidget::SimulGame);
    }
}

void GameWidget::checkGameOver()
{
    if (ColorNow == 0) {
        vector <int> WMoves = GenerateWMoves(board);
        if (WMoves.empty()) {
            QMessageBox::information(this, "Конец игры", "Белые выиграли (у белых нет ходов)!");
            newGame(type_game,color_player);
            return;
        }
    } else {
        vector <int> BMoves = GenerateBMoves(board);
        if (BMoves.empty()) {
            QMessageBox::information(this, "Конец игры", "Чёрные выиграли (у чёрных нет ходов)!");
            newGame(type_game,color_player);
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
void GameWidget::SimulGame(){
    if(type_game == -1 || (ColorNow == color_player && type_game != 3))return;
    if(type_game == 0){
        int codeMove = Bot0.selectMove(board,ColorNow);
        if(codeMove == -1){
            checkGameOver();
            return;
        }
        Move move = decodeMove(codeMove);
        board[move[2]][move[3]] = board[move[0]][move[1]];
        board[move[0]][move[1]] = EMPTY;
        if(ColorNow == 0){
            if(board[move[2]][move[3]] == WPAWN && move[2] == 0){
                board[move[2]][move[3]] = WPAWN + dist(1,5)(rng);
            }
        }else{
            if(board[move[2]][move[3]] == BPAWN && move[2] == 7){
                board[move[2]][move[3]] = BPAWN + dist(1,5)(rng);
            }
        }

        ColorNow = !ColorNow;
        m_boardView ->updateBoard();
        checkGameOver();
    }else if(type_game == 1){
        int codeMove = Bot1.selectMove(board,ColorNow);
        if(codeMove == -1){
            checkGameOver();
            return;
        }
        Move move = decodeMove(codeMove);
        board[move[2]][move[3]] = board[move[0]][move[1]];
        board[move[0]][move[1]] = EMPTY;
        if(ColorNow == 0){
            if(board[move[2]][move[3]] == WPAWN && move[2] == 0){
                board[move[2]][move[3]] = WPAWN + dist(1,5)(rng);
            }
        }else{
            if(board[move[2]][move[3]] == BPAWN && move[2] == 7){
                board[move[2]][move[3]] = BPAWN + dist(1,5)(rng);
            }
        }
        ColorNow = !ColorNow;
        m_boardView ->updateBoard();
        checkGameOver();
    }else if(type_game == 2){
        int codeMove = Bot2.selectMove(board,ColorNow);
        if(codeMove == -1){
            checkGameOver();
            return;
        }
        Move move = decodeMove(codeMove);
        board[move[2]][move[3]] = board[move[0]][move[1]];
        board[move[0]][move[1]] = EMPTY;
        if(ColorNow == 0){
            if(board[move[2]][move[3]] == WPAWN && move[2] == 0){
                board[move[2]][move[3]] = WPAWN + dist(1,5)(rng);
            }
        }else{
            if(board[move[2]][move[3]] == BPAWN && move[2] == 7){
                board[move[2]][move[3]] = BPAWN + dist(1,5)(rng);
            }
        }
        ColorNow = !ColorNow;
        m_boardView ->updateBoard();
        checkGameOver();
    }else{
        int codeMove;
        if(ColorNow == 0){
            codeMove = Bot2.selectMove(board,ColorNow);
        }else{
            codeMove = Bot1.selectMove(board,ColorNow);
        }
        if(codeMove == -1){
            checkGameOver();
            return;
        }
        Move move = decodeMove(codeMove);
        board[move[2]][move[3]] = board[move[0]][move[1]];
        board[move[0]][move[1]] = EMPTY;
        if(ColorNow == 0){
            if(board[move[2]][move[3]] == WPAWN && move[2] == 0){
                board[move[2]][move[3]] = WPAWN + dist(1,5)(rng);
            }
        }else{
            if(board[move[2]][move[3]] == BPAWN && move[2] == 7){
                board[move[2]][move[3]] = BPAWN + dist(1,5)(rng);
            }
        }
        ColorNow = !ColorNow;
        m_boardView ->updateBoard();
        checkGameOver();
        QTimer::singleShot(300, this, &GameWidget::SimulGame);
    }
}
int GameWidget::promotePawn(){
    QStringList all_white = {"♕ Ферзь", "♖ Ладья", "♗ Слон", "♘ Конь","♔ Король"};
    QStringList all_black = {"♛ Ферзь", "♜ Ладья", "♝ Слон", "♞ Конь","♚ Король"};
    bool ok;
    QString choice;
    if(color_player){
        choice = QInputDialog::getItem(this, "Превращение пешки",
                                         "Выберите фигуру:", all_black, 0, false, &ok);
        if (!ok || choice.isEmpty()) {
            choice = all_black[0];
        }
    }else{
        choice = QInputDialog::getItem(this, "Превращение пешки",
                                         "Выберите фигуру:", all_white, 0, false, &ok);
        if (!ok || choice.isEmpty()) {
            choice = all_white[0];
        }
    }
    if (color_player == 0) {
        if (choice == all_white[0]) return WQUEEN;
        if (choice == all_white[1]) return WROOK;
        if (choice == all_white[2]) return WBISHOP;
        if (choice == all_white[3]) return WKNIGHT;
        return WKING;
    } else {
        if (choice == all_black[0]) return BQUEEN;
        if (choice == all_black[1]) return BROOK;
        if (choice == all_black[2]) return BBISHOP;
        if (choice == all_black[3]) return BKNIGHT;
        return BKING;
    }
}

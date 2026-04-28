#include "mainwindow.h"
#include "gamewidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Шахматные поддавки");

    m_stackedWidget = new QStackedWidget(this);
    setCentralWidget(m_stackedWidget);

    // Меню
    m_menuWidget = new QWidget;
    QVBoxLayout *menuLayout = new QVBoxLayout(m_menuWidget);
    QLabel *title = new QLabel("Шахматные поддавки");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 24px; font-weight: bold; margin: 20px;");
    menuLayout->addWidget(title);

    QPushButton *btnLocal = new QPushButton("Локальная игра 1 на 1");
    btnLocal->setFixedSize(200, 50);
    menuLayout->addWidget(btnLocal, 0, Qt::AlignCenter);

    QPushButton *btnRandom = new QPushButton("Игра с ботом уровня 0");
    btnRandom->setFixedSize(200, 50);
    menuLayout->addWidget(btnRandom, 0, Qt::AlignCenter);

    QPushButton *btnMedium = new QPushButton("Игра с ботом уровня 1");
    btnMedium->setFixedSize(200, 50);
    menuLayout->addWidget(btnMedium, 0, Qt::AlignCenter);

    QPushButton *btnHard = new QPushButton("Игра с ботом уровня 2");
    btnHard->setFixedSize(200, 50);
    menuLayout->addWidget(btnHard, 0, Qt::AlignCenter);

    QPushButton *btnExit = new QPushButton("Выход");
    btnExit->setFixedSize(200, 50);
    menuLayout->addWidget(btnExit, 0, Qt::AlignCenter);
    connect(btnExit, &QPushButton::clicked, this, &QMainWindow::close);
    connect(btnRandom, &QPushButton::clicked, this, &MainWindow::startBot0Game);
    connect(btnLocal, &QPushButton::clicked, this, &MainWindow::startLocalGame);
    connect(btnMedium, &QPushButton::clicked, this, &MainWindow::startBot1Game);
    connect(btnHard, &QPushButton::clicked, this, &MainWindow::startBot2Game);

    m_gameWidget = new GameWidget;
    connect(m_gameWidget, &GameWidget::escapePressed, this, &MainWindow::returnToMenu);

    m_stackedWidget->addWidget(m_menuWidget);
    m_stackedWidget->addWidget(m_gameWidget);
    m_stackedWidget->setCurrentWidget(m_menuWidget);

    resize(600, 500);
}

MainWindow::~MainWindow() {}

void MainWindow::startLocalGame()
{
    m_gameWidget->newGame();
    m_stackedWidget->setCurrentWidget(m_gameWidget);
    m_gameWidget->setFocus();
}
void MainWindow::startBot0Game()
{
    QStringList colors = {"Белые", "Чёрные"};
    bool ok;
    QString choice = QInputDialog::getItem(this, "Выбор цвета",
                                           "Играть за:", colors, 0, false, &ok);
    if (!ok) return;
    int playerColor = (choice == "Белые") ? 0 : 1;
    m_gameWidget->newGame(0, playerColor);
    m_stackedWidget->setCurrentWidget(m_gameWidget);
    m_gameWidget->setFocus();
}
void MainWindow::startBot1Game()
{
    QStringList colors = {"Белые", "Чёрные"};
    bool ok;
    QString choice = QInputDialog::getItem(this, "Выбор цвета",
                                           "Играть за:", colors, 0, false, &ok);
    if (!ok) return;
    int playerColor = (choice == "Белые") ? 0 : 1;
    m_gameWidget->newGame(1, playerColor);
    m_stackedWidget->setCurrentWidget(m_gameWidget);
    m_gameWidget->setFocus();
}
void MainWindow::startBot2Game()
{
    QStringList colors = {"Белые", "Чёрные"};
    bool ok;
    QString choice = QInputDialog::getItem(this, "Выбор цвета",
                                           "Играть за:", colors, 0, false, &ok);
    if (!ok) return;
    int playerColor = (choice == "Белые") ? 0 : 1;
    m_gameWidget->newGame(2, playerColor);
    m_stackedWidget->setCurrentWidget(m_gameWidget);
    m_gameWidget->setFocus();
}
void MainWindow::returnToMenu()
{
    m_stackedWidget->setCurrentWidget(m_menuWidget);
    // m_gameWidget->newGame();
}

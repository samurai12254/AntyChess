#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

class GameWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startLocalGame();
    void startBot0Game();
    void returnToMenu();
private:
    QStackedWidget *m_stackedWidget;
    GameWidget *m_gameWidget;
    QWidget *m_menuWidget;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:


    void setupMenu();

    void createGrid();

    void clearGrid();

    void lay_mines();
    void count_around_mine();
    void show_button(int r, int c, int num);
    void fail();
    void is_win();
    void open_around(int x, int y);
    template<typename T>
    void reset_graph(QVector<QVector<T>>& , int, int);

    QVector<QVector<QPushButton*>> buttons;
    QVector<QVector<int>> mineField;
    QVector<QVector<bool>> flag;
    QVector<QVector<bool>> open;
    int rows = 9;
    int cols = 9;
    int numMines = 10;
    bool win = false;
    bool lose = false;

    int dx[8] = {-1, 1, -1, 1, 0, 1, -1, 0};
    int dy[8] = {-1, 1, 1, -1, 1, 0, 0, -1};
    Ui::MainWindow *ui;

private slots:


    void restartGame();
    void setEasyMode();
    void setMediumMode();

    void handleLeftClick(int, int);
    void handleRightClick(int, int);
};
#endif // MAINWINDOW_H

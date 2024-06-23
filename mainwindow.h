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
//    void placeMines();
//    void calculateNumbers();
    void clearGrid();

    void lay_mines();
    void count_around_mine();
    void show_button(int r, int c, int num);


    QVector<QVector<QPushButton*>> buttons; // 用于存储按钮的二维数组
    QVector<QVector<int>> mineField; // 用于存储地雷和数字的二维数组
    QVector<QVector<bool>> flag;
    QVector<QVector<bool>> open;
    int rows = 9; // 行数
    int cols = 9; // 列数
    int numMines = 10; // 地雷数量

    int dx[8] = {-1, 1, -1, 1, 0, 1, -1, 0};
    int dy[8] = {-1, 1, 1, -1, 1, 0, 0, -1};
    Ui::MainWindow *ui;

private slots:


    void restartGame();
    void setEasyMode();
    void setMediumMode();

//    void handleLeftClick();
    void handleLeftClick(int, int);
    void handleRightClick(int, int);
};
#endif // MAINWINDOW_H

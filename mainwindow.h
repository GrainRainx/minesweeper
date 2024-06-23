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

protected:
    void mousePressEvent(QMouseEvent *event) override;


private:


    void setupMenu();

    void createGrid();
//    void placeMines();
//    void calculateNumbers();
    void clearGrid();
    QVector<QVector<QPushButton*>> buttons; // 用于存储按钮的二维数组
    QVector<QVector<int>> mineField; // 用于存储地雷和数字的二维数组
    int rows = 9; // 行数
    int cols = 9; // 列数
    int numMines = 10; // 地雷数量

    Ui::MainWindow *ui;

private slots:


    void handleButtonClick();
    void restartGame();
    void setEasyMode();
    void setMediumMode();

//    void handleLeftClick();
    void handleLeftClick(int, int);
    void handleRightClick(int, int);
};
#endif // MAINWINDOW_H

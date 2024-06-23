#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGridLayout>
#include <QMessageBox>
#include <QMouseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *centralWidget = new QWidget(this);
    QGridLayout *layout = new QGridLayout(centralWidget);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);
    layout->setSpacing(0); // 设置按钮之间的间隙为0
    layout->setContentsMargins(0, 0, 0, 0);
    setupMenu();
    setEasyMode();
//    placeMines();
//    calculateNumbers();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearGrid() {
    QGridLayout *layout = qobject_cast<QGridLayout*>(centralWidget()->layout());
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    buttons.clear();
    mineField.clear();
}


void MainWindow::restartGame() {
    clearGrid();
    createGrid();
//    placeMines();
//    calculateNumbers();
}

void MainWindow::setEasyMode() {
    rows = 9;
    cols = 9;
    numMines = 10;
    setFixedSize(360, 360); // 根据新的网格大小调整窗口大小
    restartGame();

}

void MainWindow::setMediumMode() {
    rows = 16;
    cols = 16;
    numMines = 20;
    restartGame();
    setFixedSize(560, 560); // 根据新的网格大小调整窗口大小
}

void MainWindow::setupMenu() {
    QMenuBar *menuBar = new QMenuBar(this);

    QMenu *gameMenu = new QMenu("Game", this);
    QAction *restartAction = new QAction("Restart", this);
    connect(restartAction, &QAction::triggered, this, &MainWindow::restartGame);

    QAction *easyAction = new QAction("Easy", this);
    connect(easyAction, &QAction::triggered, this, &MainWindow::setEasyMode);

    QAction *mediumAction = new QAction("Medium", this);
    connect(mediumAction, &QAction::triggered, this, &MainWindow::setMediumMode);

    gameMenu->addAction(restartAction);
    gameMenu->addAction(easyAction);
    gameMenu->addAction(mediumAction);

    menuBar->addMenu(gameMenu);
    setMenuBar(menuBar);
}


void MainWindow::createGrid() {
    QGridLayout *layout = qobject_cast<QGridLayout*>(centralWidget()->layout());
    for (int i = 0; i < rows; ++i) {
        QVector<QPushButton*> rowButtons;
        for (int j = 0; j < cols; ++j) {
            QPushButton *button = new QPushButton(this);
            button->setFixedSize(40, 40); // 设置按钮为固定大小
            rowButtons.append(button);
            layout->addWidget(button, i, j);
            connect(button, &QPushButton::clicked, this, &MainWindow::handleLeftClick);
//            connect(button, &QPushButton::clicked, this, &MainWindow::handleRightClick);
        }
        buttons.append(rowButtons);
    }

    mineField.resize(rows);
    for (int i = 0; i < rows; ++i) {
        mineField[i].resize(cols);
        for (int j = 0; j < cols; ++j) {
            mineField[i][j] = 0; // 初始化为0
        }
    }
}


void MainWindow::handleButtonClick() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) {
        return;
    }

    int row, col;
    bool found = false;
    for (row = 0; row < rows; ++row) {
        for (col = 0; col < cols; ++col) {
            if (buttons[row][col] == button) {
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }

    if (mineField[row][col] == -1) {
        button->setText("X"); // 显示地雷
        button->setStyleSheet("color: red;");
        QMessageBox::information(this, "Game Over", "You clicked on a mine!");
        qApp->quit();
    } else {
        button->setText(QString::number(mineField[row][col])); // 显示邻近地雷数量
        button->setEnabled(false);
    }
}


void MainWindow::mousePressEvent(QMouseEvent *event) {
    qDebug() << "i am click event\n";
    buttons[1][1]->setIcon(QIcon(":/SaoLei/flag"));
    // 实现鼠标点击事件处理逻辑
}
void MainWindow::handleLeftClick() {
//    QPushButton *button = qobject_cast<QPushButton*>(sender());
    buttons[1][1]->setIcon(QIcon(":/SaoLei/1"));
//    Qt::MouseButton buttonPressed = event->button();
    qDebug() << "i am left click\n";
}

void MainWindow::handleRightClick() {
    qDebug() << "i am right click\n";
}





















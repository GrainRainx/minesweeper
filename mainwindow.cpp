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
    clearGrid();
    createGrid();
    setEasyMode();
    lay_mines();
    count_around_mine();
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
    lay_mines();
    count_around_mine();
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
//            connect(button, &QPushButton::clicked, this, &MainWindow::handleLeftClick);
            connect(button, &QPushButton::clicked, [this, i, j]() { handleLeftClick(i, j); });
//            connect(button, &QPushButton::clicked, this, &MainWindow::handleRightClick);
            button->setContextMenuPolicy(Qt::CustomContextMenu);
            connect(button, &QPushButton::customContextMenuRequested, [this, i, j](const QPoint &pos) { handleRightClick(i, j); });
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
    flag.resize(rows);
    for (int i = 0; i < rows; ++i) {
        flag[i].resize(cols);
        for (int j = 0; j < cols; ++j) {
            flag[i][j] = false;
        }
    }
    open.resize(rows);
    for (int i = 0; i < rows; ++i) {
        open[i].resize(cols);
        for (int j = 0; j < cols; ++j) {
            open[i][j] = false;
        }
    }
}



void MainWindow::handleLeftClick(int r, int c) {
    if(open[r][c]) return;
    open[r][c] = true;

    qDebug() << "i am left click\n";
    qDebug() << "x = " << r << " y = " << c << "\n";
//    QPushButton *button = qobject_cast<QPushButton*>(sender());

    buttons[r][c]->setIcon(QIcon(":/SaoLei/1"));
//    Qt::MouseButton buttonPressed = event->button();

}

void MainWindow::handleRightClick(int r, int c) {
    if(open[r][c]) return ;
    buttons[r][c]->setIcon(QIcon(""));
    flag[r][c] = !flag[r][c];
    if(flag[r][c]) {
        buttons[r][c]->setIcon(QIcon(":/SaoLei/flag"));
    }
    qDebug() << "i am right click\n";
    qDebug() << "x = " << r << " y = " << c << "\n";
}


void MainWindow::lay_mines() {
    int k = numMines;
    while(k--) {
        srand(time(nullptr));
        while (true) {
            int r = rand() % rows;
            int c = rand() % cols;
            if(mineField[r][c] == -1) continue;
            mineField[r][c] = -1;
            break;
        }
    }

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(mineField[i][j] == -1) {
                handleRightClick(i, j);
            }
        }
    }
}


void MainWindow::show_button(int r, int c, int num) {

    switch(num)
    {
        case 0 : break;
        case 1 : buttons[r][c]->setIcon(QIcon(":/SaoLei/1"));break;
        case 2 : buttons[r][c]->setIcon(QIcon(":/SaoLei/2"));break;
        case 3 : buttons[r][c]->setIcon(QIcon(":/SaoLei/3"));break;
        case 4 : buttons[r][c]->setIcon(QIcon(":/SaoLei/4"));break;
        case 5 : buttons[r][c]->setIcon(QIcon(":/SaoLei/5"));break;
        case 6 : buttons[r][c]->setIcon(QIcon(":/SaoLei/6"));break;
        case 7 : buttons[r][c]->setIcon(QIcon(":/SaoLei/7"));break;
        case 8 : buttons[r][c]->setIcon(QIcon(":/SaoLei/8"));break;
    }
}



void MainWindow::count_around_mine() {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(mineField[i][j] == -1) continue;
            int sum = 0;
            for(int k = 0; k < 8; k++) {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if(nx < 0 || nx >= rows || ny < 0 || ny >= cols) continue;
                if(mineField[nx][ny] == -1) sum++;
            }
            mineField[i][j] = sum;
        }
    }


    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(mineField[i][j] == -1) continue;
            int c = mineField[i][j];
//            buttons[i][j]->setIcon(QIcon(":/SaoLei/flag"));break;
            show_button(i, j, c);
        }
    }

}


















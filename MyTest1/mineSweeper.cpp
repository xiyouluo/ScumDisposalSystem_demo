#include "mineSweeper.h"
#include <QRandomGenerator>
#include <QSignalMapper>
#include <QIcon>

MineSweeper::MineSweeper(QWidget *parent) : QWidget(parent), unrevealedSafeCells(SIZE * SIZE - numMines)
{
    layout = new QGridLayout(this);
    reset();
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    this->setWindowTitle("Mine Sweeper");
    //setStyleSheet("background-image: url(:/images/images/lab_2.png);");
}

void MineSweeper::reset() {
    for(int i = 0; i < SIZE; i ++ ) {
        for(int j = 0; j < SIZE; j ++ ) {
            mines[i][j] = false;
            revealed[i][j] = false;
            buttons[i][j] = new QPushButton(this);
            buttons[i][j]->setFixedSize(20, 20);
            buttons[i][j]->setIcon(QIcon(":/mypic/blank.jpg"));
            buttons[i][j]->setIconSize(QSize(20, 20));
            buttons[i][j]->setStyleSheet("border:none; padding:0px; margin:0px;");
            layout->addWidget(buttons[i][j], i, j);
            connect(buttons[i][j], &QPushButton::clicked, this, &MineSweeper::onButtonClicked);
        }
    }
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    setMines();
}

void MineSweeper::onButtonClicked() {
    QPushButton* button = (QPushButton*)sender();
    int row, col;
    for(row = 0; row < SIZE; row ++ ) {
        for(col = 0; col < SIZE; col ++ ) {
            if(buttons[row][col] == button) break;
        }
        if(col < SIZE) break;
    }

    if(mines[row][col]) gameOver(row, col);
    else {
        expand(row, col);
        if(unrevealedSafeCells == 0) // win
        {
            QMessageBox::information(this, "Congratulations", "You've won!");
            //reset();
            this->close();
        }
    }
}

void MineSweeper::setMines() {
    for(int i = 0; i < numMines; i ++ ) {
        while (true) {
            int row = QRandomGenerator::global()->bounded(SIZE);
            int col = QRandomGenerator::global()->bounded(SIZE);
            if (mines[row][col]) continue;
            else {
                mines[row][col] = true;
                break;
            }
        }
    }
}

int MineSweeper::countMines(int row, int col) {
    int count = 0;
    for(int i = -1; i <= 1; i ++ ) {
        for(int j = -1; j <= 1; j ++ ) {
            if(i == 0 && j == 0) continue;
            if(row + i >= 0 && row + i < SIZE && col + j >= 0 && col + j < SIZE && mines[row + i][col + j]) count ++ ;
        }
    }
    return count;
}

void MineSweeper::expand(int row, int col) {
    if(row < 0 || row >= SIZE || col < 0 || col >= SIZE || revealed[row][col]) return;

    revealed[row][col] = true;
    int count = countMines(row, col);
    if(count > 0) {
        QString imagePath = QString(":/mypic/number%1.jpg").arg(count);
        buttons[row][col]->setIcon(QIcon(imagePath));
        buttons[row][col]->update();
        unrevealedSafeCells -- ;
    }
    else {
        buttons[row][col]->setIcon(QIcon(":/mypic/number0.jpg"));
        buttons[row][col]->update();
        for(int i = -1; i <= 1; i ++ ) {
            for(int j = -1; j <= 1; j ++ ) {
                expand(row + i, col + j);
            }
        }
    }
}

void MineSweeper::gameOver(int row, int col) {
    buttons[row][col]->setIcon(QIcon(":/mypic/mine_step.jpg"));
    for(int i = 0; i < SIZE; i ++ ) {
        for(int j = 0; j < SIZE; j ++ ) {
            //buttons[i][j]->setDisabled(true);
            if(mines[i][j] && !(i == row && j == col))
                buttons[i][j]->setIcon(QIcon(":/mypic/mine.jpg"));
        }
    }
    QMessageBox::information(this, "Game Over", "哈哈哈，你不会真的以为我会给你赢的机会吧？");
    //reset();
    this->close();
}

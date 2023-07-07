#include "mineSweeper.h"
#include <QRandomGenerator>
#include <QSignalMapper>
#include <QIcon>

MineSweeper::MineSweeper(QWidget *parent) : QWidget(parent), unrevealedSafeCells(100 - numMines)
{
    layout = new QGridLayout(this);
    reset();
}

void MineSweeper::reset() {
    for(int i = 0; i < 10; i ++ ) {
        for(int j = 0; j < 10; j ++ ) {
            mines[i][j] = false;
            revealed[i][j] = false;
            buttons[i][j] = new QPushButton(this);
            buttons[i][j]->setFixedSize(20,20);
            buttons[i][j]->setIcon(QIcon(":/images/images/blank.jpg"));
            layout->addWidget(buttons[i][j], i, j);
            connect(buttons[i][j], &QPushButton::clicked, this, &MineSweeper::onButtonClicked);
        }
    }
    setMines();
}

void MineSweeper::onButtonClicked() {
    QPushButton* button = (QPushButton*)sender();
    int row, col;
    for(row = 0; row < 10; row ++ ) {
        for(col = 0; col < 10; col ++ ) {
            if(buttons[row][col] == button) break;
        }
        if(col < 10) break;
    }

    if(mines[row][col]) gameOver(row, col);
    else {
        expand(row, col);
        if(unrevealedSafeCells == 0) // win
        {
            QMessageBox::information(this, "Congratulations", "You've won!");
            reset();
        }
    }
}

void MineSweeper::setMines() {
    for(int i = 0; i < numMines; i ++ ) {
        while (true) {
            int row = QRandomGenerator::global()->bounded(10);
            int col = QRandomGenerator::global()->bounded(10);
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
            if(row + i >= 0 && row + i < 10 && col + j >= 0 && col + j < 10 && mines[row + i][col + j]) count ++ ;
        }
    }
    return count;
}

void MineSweeper::expand(int row, int col) {
    if(row < 0 || row >= 10 || col < 0 || col >= 10 || revealed[row][col]) return;

    revealed[row][col] = true;
    int count = countMines(row, col);
    if(count > 0) {
        QString imagePath = QString(":/images/images/number%1.jpg").arg(count);
        buttons[row][col]->setIcon(QIcon(imagePath));
        buttons[row][col]->update();
        unrevealedSafeCells -- ;
    }
    else {
        buttons[row][col]->setIcon(QIcon(":/images/images/number0.jpg"));
        buttons[row][col]->update();
        for(int i = -1; i <= 1; i ++ ) {
            for(int j = -1; j <= 1; j ++ ) {
                expand(row + i, col + j);
            }
        }
    }
}

void MineSweeper::gameOver(int row, int col) {
    buttons[row][col]->setIcon(QIcon(":/images/images/mine_step.jpg"));
    for(int i = 0; i < 10; i ++ ) {
        for(int j = 0; j < 10; j ++ ) {
            //buttons[i][j]->setDisabled(true);
            if(mines[i][j] && !(i == row && j == col)) {
                buttons[i][j]->setIcon(QIcon(":/images/images/mine.jpg"));
            }
        }
    }
    QMessageBox::information(this, "Game Over", "You've hit a mine!");
    reset();
}

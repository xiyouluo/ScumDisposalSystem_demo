#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>

class MineSweeper : public QWidget
{
    Q_OBJECT
public:
    static const int SIZE = 35;
    static const int numMines = SIZE * SIZE; // set the number of mines here
    explicit MineSweeper(QWidget *parent = nullptr);
    void reset();

private slots:
    void onButtonClicked();

private:
    QPushButton *buttons[SIZE][SIZE];
    bool mines[SIZE][SIZE];
    bool revealed[SIZE][SIZE];
    int unrevealedSafeCells;
    QGridLayout *layout;

    void setMines();
    int countMines(int row, int col);
    void expand(int row, int col);
    void gameOver(int row, int j);
};

#endif // MINESWEEPER_H

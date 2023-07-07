#ifndef FIVEINAROW_H
#define FIVEINAROW_H

#include <QMainWindow>
#include <QPushButton>

enum class Piece { NONE, PLAYER, AI };

class FiveInARow : public QMainWindow
{
    Q_OBJECT

private:
    static const int SIZE = 15;
    QPushButton *buttons[SIZE][SIZE];
    Piece board[SIZE][SIZE] = {};
    Piece initialBoard[SIZE][SIZE] = {};
public:
    FiveInARow(QWidget *parent = nullptr);

private slots:
    void buttonClicked();

private:
    int evaluateBoard();
    QPair<int, int> minimax();
    void makeAIMove();
    bool checkWin(Piece piece);
    void resetGame();
};

#endif // FIVEINAROW_H

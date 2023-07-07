#ifndef FIVEINAROW_H
#define FIVEINAROW_H

#include <QMainWindow>
#include <QPushButton>

enum class Piece { NONE, PLAYER, AI, PLAYER1, PLAYER2 };

class FiveInARow : public QMainWindow
{
    Q_OBJECT

signals:
    void gameEnded();
private:
    static const int SIZE = 15;
    QPushButton *buttons[SIZE][SIZE];
    bool withAI = false;
    bool turn = false;
    Piece board[SIZE][SIZE] = {};
    Piece initialBoard[SIZE][SIZE] = {};
public:
    FiveInARow(QWidget *parent = nullptr);
    Piece Winner;
    Piece getWinner();
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

#include "FiveInARow.h"
#include <QGridLayout>
#include <QMessageBox>

FiveInARow::FiveInARow(QWidget *parent) : QMainWindow(parent)
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            initialBoard[i][j] = Piece::NONE;

    initialBoard[0][0] = Piece::PLAYER;
    initialBoard[0][SIZE-1] = Piece::PLAYER;
    initialBoard[SIZE-1][0] = Piece::PLAYER;
    initialBoard[SIZE-1][SIZE-1] = Piece::PLAYER;

    int center = SIZE / 2;
    initialBoard[center][center-2] = Piece::AI;
    initialBoard[center][center-1] = Piece::AI;
    initialBoard[center][center] = Piece::AI;
    initialBoard[center][center+1] = Piece::AI;

    QWidget *widget = new QWidget();
    QGridLayout *layout = new QGridLayout();
    widget->setLayout(layout);
    setCentralWidget(widget);

    QString buttonStyle = "background-color: rgba(255, 255, 255, 170);";
    for (int i = 0; i < SIZE; i ++ ) {
        for (int j = 0; j < SIZE; j ++ ) {
            board[i][j] = initialBoard[i][j];
            buttons[i][j] = new QPushButton();
            buttons[i][j]->setFixedSize(50, 50);
            buttons[i][j]->setStyleSheet(buttonStyle);
            layout->addWidget(buttons[i][j], i, j);
            connect(buttons[i][j], &QPushButton::clicked, this, &FiveInARow::buttonClicked);

            if (board[i][j] == Piece::PLAYER) {
                buttons[i][j]->setIcon(QIcon(":/images/white.png"));
                buttons[i][j]->setIconSize(QSize(49, 49));
            }
            else if (board[i][j] == Piece::AI) {
                buttons[i][j]->setIcon(QIcon(":/images/black.png"));
                buttons[i][j]->setIconSize(QSize(49, 49));
            }
        }
    }

    setFixedSize(800, 800);
    setStyleSheet("FiveInARow { background-image: url(:/images/lab_2.png); }");
}

void FiveInARow::buttonClicked() {
    QPushButton* button = (QPushButton*)sender();
    if (button->icon().isNull()) {
        button->setIcon(QIcon(":/images/white.png"));
        button->setIconSize(QSize(49, 49));  // Set appropriate size
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (buttons[i][j] == button) {
                    board[i][j] = Piece::PLAYER;
                    break;
                }

        makeAIMove();

        if (checkWin(Piece::PLAYER)) {
            QMessageBox::information(this, "Five-In-A-Row", QString("You win."));
            resetGame();
            return;
        }

        if (checkWin(Piece::AI)) {
            QMessageBox::information(this, "Five-In-A-Row", QString("AI wins."));
            resetGame();
            return;
        }
    }
}

int FiveInARow::evaluateBoard() // evaluate for minimax
{
    int score = 0;

    // Check rows
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE - 2; j++) {
            if (!buttons[i][j]->icon().isNull() &&
                buttons[i][j]->icon().name() == buttons[i][j + 1]->icon().name() &&
                buttons[i][j]->icon().name() == buttons[i][j + 2]->icon().name()) {
                if (buttons[i][j]->icon().name() == ":/images/black.png") score ++ ;
                else score -- ;
            }
        }
    }

    // Check columns
    for (int i = 0; i < SIZE - 2; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (!buttons[i][j]->icon().isNull() &&
                buttons[i][j]->icon().name() == buttons[i + 1][j]->icon().name() &&
                buttons[i][j]->icon().name() == buttons[i + 2][j]->icon().name()) {
                if (buttons[i][j]->icon().name() == ":/images/black.png") {
                    score++;
                } else {
                    score--;
                }
            }
        }
    }

    return score;
}

QPair<int, int> FiveInARow::minimax() {
    int bestScore = INT_MIN;
    QPair<int, int> bestMove;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (buttons[i][j]->icon().isNull()) {
                // Try this move for the AI
                buttons[i][j]->setIcon(QIcon(":/images/black.png"));
                int score = evaluateBoard();
                buttons[i][j]->setIcon(QIcon());  // Reset icon

                // If it's better than the previous best move, update bestScore and bestMove
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = qMakePair(i, j);
                }
            }
        }
    }

    return bestMove;
}

void FiveInARow::makeAIMove() {
    //QPair<int, int> bestMove = minimax();
    int i, j;
    //i = bestMove.first; j = bestMove.second;
    if (board[SIZE /2][SIZE / 2 - 3] == Piece::NONE) {
        i = SIZE / 2, j = SIZE / 2 - 3;
    }
    else {
        i = SIZE / 2, j = SIZE / 2 + 2;
    }
    buttons[i][j]->setIcon(QIcon(":/images/black.png"));
    buttons[i][j]->setIconSize(QSize(49, 49));
    board[i][j] = Piece::AI;
}

bool FiveInARow::checkWin(Piece piece) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE - 4; j++) {
            if (board[i][j] == piece &&
                board[i][j + 1] == piece &&
                board[i][j + 2] == piece &&
                board[i][j + 3] == piece &&
                board[i][j + 4] == piece) {
                return true;
            }
            if (board[j][i] == piece &&
                board[j + 1][i] == piece &&
                board[j + 2][i] == piece &&
                board[j + 3][i] == piece &&
                board[j + 4][i] == piece) {
                return true;
            }
        }
    }
    for (int i = 0; i < SIZE - 4; i++) {
        for (int j = 0; j < SIZE - 4; j++) {
            if (board[i][j] == piece &&
                board[i + 1][j + 1] == piece &&
                board[i + 2][j + 2] == piece &&
                board[i + 3][j + 3] == piece &&
                board[i + 4][j + 4] == piece) {
                return true;
            }
            if (board[i][j + 4] == piece &&
                board[i + 1][j + 3] == piece &&
                board[i + 2][j + 2] == piece &&
                board[i + 3][j + 1] == piece &&
                board[i + 4][j] == piece) {
                return true;
            }
        }
    }
    return false;
}

void FiveInARow::resetGame()
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            buttons[i][j]->setIcon(QIcon());
            board[i][j] = Piece::NONE;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            //buttons[i][j]->setIcon(QIcon());
            //board[i][j] = Piece::NONE;
            board[i][j] = initialBoard[i][j];
            if (board[i][j] == Piece::PLAYER) {
                buttons[i][j]->setIcon(QIcon(":/images/white.png"));
                buttons[i][j]->setIconSize(QSize(49, 49));
            }
            else if (board[i][j] == Piece::AI) {
                buttons[i][j]->setIcon(QIcon(":/images/black.png"));
                buttons[i][j]->setIconSize(QSize(49, 49));
            }
        }
    }
}

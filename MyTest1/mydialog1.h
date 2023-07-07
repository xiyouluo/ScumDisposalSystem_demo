#ifndef MYDIALOG1_H
#define MYDIALOG1_H

#include <QDialog>

namespace Ui {
class MyDialog1;
}

class MyDialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog1(QWidget *parent = nullptr);
    ~MyDialog1();
    void setPerson(int n);
    void MakeChoice();
    void UpdateHeartRegret();
    void setBackground();
    void End();
    void Begin();
    void Begin2();
    void StartGame();

private slots:

    void on_NexSenBtn_clicked();
    void on_BtnC1_clicked();
    void on_BtnC2_clicked();
    void on_BtnC3_clicked();
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void on_Start_clicked();

private:
    Ui::MyDialog1 *ui;
};

void MySleep(unsigned int msec);
void InitChoice();
void ReadText1();

#endif // MYDIALOG1_H

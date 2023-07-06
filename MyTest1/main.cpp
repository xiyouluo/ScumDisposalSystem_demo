#include "mydialog.h"
#include "mydialog1.h"
#include <QApplication>
#include <QFileInfo>
#include <QDateTime>
#include <QTextStream>
#include <QMessageBox>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QtWidgets/QApplication>
using namespace std;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyDialog1 *dlg = new MyDialog1();
    dlg->setWindowTitle(QString("渣男处理系统"));
    dlg->show();
    dlg->StartGame();


    /*
    MyDialog w;
    w.show();
    */
    return a.exec();
}

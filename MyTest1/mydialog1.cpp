#include "FiveInARow.h"
#include "mineSweeper.h"
#include "mydialog1.h"
#include "ui_mydialog1.h"
#include <QFileInfo>
#include <QDateTime>
#include <QTextStream>
#include <QMessageBox>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QProgressBar>
#include <QtWidgets/QApplication>
#include <QTime>
#include <QTimer>
#include <QSoundEffect>
using namespace std;

const int N = 1000008;
const int n = 58;
int warn = 0;
QString text1[N];
QChar text_flag1[N];
bool CPD_flag = false;
int count_text1 = 0;
int input_text_flag = 0;
int output_text_flag = 0;
int input_picture_flag = 0;
int choice_id = 0;
int choice_num[n] = {2, 2, 2, 3, 3, 2, 2, 2};
QString choice_content[n][4];
int heart_change[n][3] = {{5, -10}, {2, -10}, {2, -10}, {10, -20, -5}, {0, 0, 0}, {0, -5}, {-1000, -1000}, {0, 10}};
//int regret_change[n][3] = {{0, 0}, {0, 0}, {0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0}, {0, 0}, {10, 0}, {0, 0}, {0, 9}};
int is_making_choice = 0;
int heart = 60;
int regret = 0;
int background = 0;
int endflag = 0;
int startflag = 0;
int change_back = 2;
QSoundEffect* bgm = new QSoundEffect;
int jump[n][4] = {{-1, 1}, {6, 3}, {2, -1}, {-1, 3, 5}, {-1, -1, -1}, {0, -1}, {-1, 5}, {-1, 3}};
bool heroineGoFlag = true;
bool enterGame1Flag = false;
bool enterGame2Flag = false;
bool game1WinFlag = false;
bool game2WinFlag = false;

void MySleep(unsigned int msec) {
    QTime TargetTime = QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime() < TargetTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    return;
}

void InitChoice() {
    choice_content[0][0] = "告诉他你已经研发出预防药物了";
    choice_content[0][1] = "隐瞒";

    choice_content[1][0] = "同意";
    choice_content[1][1] = "不同意";

    choice_content[2][0] = "同意";
    choice_content[2][1] = "不同意";

    choice_content[3][0] = "你去";
    choice_content[3][1] = "他去";
    choice_content[3][2] = "随便找人去";

    choice_content[4][0] = "正常药物";
    choice_content[4][1] = "失活药物";
    choice_content[4][2] = "添加CPD的药物";

    choice_content[5][0] = "是";
    choice_content[5][1] = "不是";

    choice_content[6][0] = "私下将研究数据传送给中心基地";
    choice_content[6][1] = "利用实验室的γ病毒让他感染";

    choice_content[7][0] = "告诉他真相";
    choice_content[7][1] = "隐瞒";
    return;
}

void ReadText1() {
    /*剧情文本读入*/
    int count = 0;
    QFile file1(":/mytxt/text1.txt");
    if(!file1.open(QIODevice::ReadOnly)) {
        text1[1] = "暂且用这种方式报错，文件打开失败";
        warn = 1;   //第一类报错，待弹出警告框
        return;
    }
    QTextStream stream1(&file1);
    while(!stream1.atEnd()) {
        QString temp = stream1.read(1);
        text_flag1[++count] = temp[0];
        text1[count] = stream1.readLine();
    }
    file1.close();
    return;
}

void changeBgm(int n) {
    switch (n) {
    case 1:
        bgm->setSource(QUrl("qrc:/bgm/music_1.wav"));
        bgm->setVolume(0.77);
        bgm->setLoopCount(QSoundEffect::Infinite);
        bgm->play();
        break;
    case 2:
        bgm->setSource(QUrl("qrc:/bgm/music_2.wav"));
        bgm->setVolume(0.77);
        bgm->setLoopCount(QSoundEffect::Infinite);
        bgm->play();
        break;
    case 3:
        bgm->setSource(QUrl("qrc:/bgm/music_3.wav"));
        bgm->setVolume(0.77);
        bgm->setLoopCount(QSoundEffect::Infinite);
        bgm->play();
        break;
    }
}

void MyDialog1::End() {
    ui->diabox_label->setVisible(false);
    ui->label->setVisible(false);
    change_back = 2;
    background = 6;
    setBackground();
    ui->heart_progressBar->setVisible(false);
    ui->regret_progressBar->setVisible(false);
    ui->heart->setVisible(false);
    ui->regret->setVisible(false);
    if(endflag == 1) // 第一版的结局
    {
        ui->label_end1->setText("谢谢你改变了我的命运，让我能够开始新的生活");
        ui->label_end2->setText("这段时光里，感谢你教会了我理智、冷静与勇敢");
        ui->label_end3->setText("希望现实中的你不要遇到像他一样的人");
        ui->label_end4->setText("如果不幸遇到了，也希望你能像帮助我一样帮助自己脱离苦海");
        ui->label_end5->setText("毕竟....");
        MySleep(2000);
        ui->label_end1->setVisible(true);
        MySleep(2000);
        ui->label_end2->setVisible(true);
        MySleep(2000);
        ui->label_end3->setVisible(true);
        MySleep(2000);
        ui->label_end4->setVisible(true);
        MySleep(2000);
        ui->label_end5->setVisible(true);
        MySleep(3000);
        ui->label_end1->setVisible(false);
        ui->label_end2->setVisible(false);
        ui->label_end3->setVisible(false);
        ui->label_end4->setVisible(false);
        ui->label_end5->setVisible(false);
        change_back = 2;
        background = 7;
        setBackground();
        return;
    }
    else if (endflag == 2) // bad end 1 & 2
    {
        ui->label_end2->setText("他对你的好感值清零");
        ui->label_end3->setText("你没能改变我的命运");
        ui->label_end4->setText("游戏失败");
        MySleep(2000);
        ui->label_end2->setVisible(true);
        MySleep(2000);
        ui->label_end3->setVisible(true);
        MySleep(2000);
        ui->label_end4->setVisible(true);
        MySleep(2000);
        ui->label_end2->setVisible(false);
        ui->label_end3->setVisible(false);
        ui->label_end4->setVisible(false);
        // 处理结束的界面之类的
    }
    else if (endflag == 3) // bad end 3
    {
        ui->label_end1->setText("你改变了我的悲惨结局");
        ui->label_end2->setText("但是很遗憾");
        ui->label_end3->setText("由于你没有成功阻止他的阴谋，除你所在基地以外其他基地均已沦陷");
        ui->label_end4->setText("你们成为了唯一的一座孤岛");
        ui->label_end5->setText("不久之后因为物资问题同样被吞噬，人类的历史画上句号");
        MySleep(2000);
        ui->label_end1->setVisible(true);
        MySleep(2000);
        ui->label_end2->setVisible(true);
        MySleep(2000);
        ui->label_end3->setVisible(true);
        MySleep(2000);
        ui->label_end4->setVisible(true);
        MySleep(2000);
        ui->label_end5->setVisible(true);
        MySleep(3000);
        ui->label_end1->setVisible(false);
        ui->label_end2->setVisible(false);
        ui->label_end3->setVisible(false);
        ui->label_end4->setVisible(false);
        ui->label_end5->setVisible(false);
        // 处理结束的界面之类的
    }
    else if (endflag == 4) // normal end
    {
        // to be continued
    }
}

void MyDialog1::UpdateHeartRegret() {
    MySleep(200);
    if(heart < 0) heart = 0;
    if(heart > 100) heart = 100;
    ui->heart_progressBar->setValue(heart);
    ui->heart_progressBar->setFormat(QString::number(ui->heart_progressBar->value(), 10));
    if(regret < 0) regret = 0;
    if(regret > 100) regret = 100;
    ui->regret_progressBar->setValue(regret);
    ui->regret_progressBar->setFormat(QString::number(ui->regret_progressBar->value(), 10));
}

void MyDialog1::Begin() {
    background = 2;
    change_back = 2;
    changeBgm(1);
    setBackground();
    ui->label_begin1->setVisible(true);
    ui->label_begin1->setText("");
    QString text;
    QFile filebegin(":/mytxt/text2.txt");
    ui->label_begin1->setWordWrap(true);
    if(!filebegin.open(QIODevice::ReadOnly)){
        warn = 1;   //第一类报错，待弹出警告框
        return;
    }
    QTextStream streambegin(&filebegin);
    /*while(!streambegin.atEnd()) {
        QString temp = streambegin.readLine();
        text.clear();
        text.append("<p style='line-height:150%'>").append("    ").append(temp);
        ui->label_begin1->setText(text);
        MySleep(50);
    }*/
    filebegin.close();
    ui->hint_label->setVisible(true);
    //MySleep(2000);
    startflag = 1;
    return;
}

void MyDialog1::Begin2() {
    QString text;
    ui->label_begin1->setText("");
    ui->hint_label->setVisible(false);
    QFile filebegin2(":/mytxt/text3.txt");
    if(!filebegin2.open(QIODevice::ReadOnly)) {
        warn = 1;   //第一类报错，待弹出警告框
        return;
    }
    QTextStream streambegin2(&filebegin2);
    /*while(!streambegin2.atEnd()){
        QString temp = streambegin2.readLine();
        text.clear();
        text.append("<p style='line-height:150%'>").append("    ").append(temp);
        ui->label_begin1->setText(text);
        MySleep(50);
    }*/
    filebegin2.close();
    text.append("<br>");
    ui->label_begin1->setText(text);
    MySleep(200);
    text.append("<br>");
    ui->label_begin1->setText(text);
    MySleep(200);
    text.append("任务提示：请代替“我”作出选择，不同选择会使剧情走向以");
    ui->label_begin1->setText(text);
    MySleep(200);
    text.append("<br>及他对“我”的态度发生变化，当他对“我”的好感值或悔意");
    ui->label_begin1->setText(text);
    MySleep(200);
    text.append("<br>值达到100时，任务成功，游戏结束。");
    ui->label_begin1->setText(text);
    MySleep(200);
    text.append("<br>基础好感值：60");
    ui->label_begin1->setText(text);
    MySleep(200);
    text.append("<br>基础悔意值：0");
    ui->label_begin1->setText(text);
    MySleep(200);
    ui->hint_label->setVisible(true);
    return;
}

void MyDialog1::StartGame() {
    background = 1;
    ui->diabox_label->setVisible(false);
    ui->label->setVisible(false);
    ui->label_begin1->setVisible(false);
    ui->hint_label->setVisible(false);
    setBackground();
    ui->heart_progressBar->setVisible(false);
    ui->regret_progressBar->setVisible(false);
    ui->heart->setVisible(false);
    ui->regret->setVisible(false);
    ui->Start->setText("");
    ui->Start->setStyleSheet("border-image: url(:/mypic/Start.png);");
    return;
}

MyDialog1::MyDialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog1)
{
    ui->setupUi(this);
    ui->BtnC1->setVisible(false);
    ui->BtnC2->setVisible(false);
    ui->BtnC3->setVisible(false);
    ui->NexSenBtn->setVisible(false);

    ui->label_end1->setVisible(false);
    ui->label_end1->setAlignment(Qt::AlignCenter);
    ui->label_end2->setVisible(false);
    ui->label_end2->setAlignment(Qt::AlignCenter);
    ui->label_end3->setVisible(false);
    ui->label_end3->setAlignment(Qt::AlignCenter);
    ui->label_end4->setVisible(false);
    ui->label_end4->setAlignment(Qt::AlignCenter);
    ui->label_end5->setVisible(false);
    ui->label_end5->setAlignment(Qt::AlignCenter);

    InitChoice();
    ui->diabox_label->setStyleSheet("border-image: url(:/mypic/DialogBox.png);");
    ui->BtnC1->setStyleSheet("border-image: url(:/mypic/DialogBox.png);");
    ui->BtnC2->setStyleSheet("border-image: url(:/mypic/DialogBox.png);");
    ui->BtnC3->setStyleSheet("border-image: url(:/mypic/DialogBox.png);");
    ui->temp_choice4->move(507, 407);
    ui->temp_choice4->setVisible(false);

    ui->heart_progressBar->setStyleSheet("QProgressBar{background:white;} QProgressBar::chunk{border-radius:5px; background:rgb(252,157,154);}");
    ui->heart_progressBar->setRange(0, 100);
    ui->heart_progressBar->setValue(heart);
    ui->heart_progressBar->setAlignment(Qt::AlignCenter);
    ui->heart_progressBar->setFormat(QString::number(ui->heart_progressBar->value(), 10));
    ui->regret_progressBar->setStyleSheet("QProgressBar{background:white;} QProgressBar::chunk{border-radius:5px; background:rgb(16,109,156);}");
    ui->regret_progressBar->setRange(0, 100);
    ui->regret_progressBar->setValue(regret);
    ui->regret_progressBar->setAlignment(Qt::AlignCenter);
    ui->regret_progressBar->setFormat(QString::number(ui->regret_progressBar->value(), 10));
    ui->heart->setStyleSheet("border-image: url(:/mypic/heart.png);");
    ui->regret->setStyleSheet("border-image: url(:/mypic/brokenheart.png);");
}

MyDialog1::~MyDialog1()
{
    delete ui;
}

void MyDialog1::setPerson(int n){
    if(n == 0) ui->person1->setStyleSheet("border-image: url(:/mypic/empty.png);");
    if(n == 1) ui->person1->setStyleSheet("border-image: url(:/mypic/zhanan.png);");
    if(n == 2) ui->person1->setStyleSheet("border-image: url(:/mypic/zhananhurt.png);");
    return;
}

void MyDialog1::setBackground() {
    if(change_back == 2) // 常规切换背景
    {
        switch(background) {
        case 0: ui->background_label->setStyleSheet("border-image: url(:/mypic/lab.png);"); break;
        case 1: ui->background_label->setStyleSheet("border-image: url(:/mypic/title.jpg);"); break;
        case 2: ui->background_label->setStyleSheet("border-image: url(:/mypic/Front.jpg);"); break;
        case 3: ui->background_label->setStyleSheet("border-image: url(:/mypic/lab_2.png);"); break;
        case 4: ui->background_label->setStyleSheet("border-image: url(:/mypic/ruin.png);"); break;
        case 5: ui->background_label->setStyleSheet("border-image: url(:/mypic/seperate.png);"); break;
        case 6: ui->background_label->setStyleSheet("border-image: url(:/mypic/end.png);"); break;
        case 7: ui->background_label->setStyleSheet("border-image: url(:/mypic/end_2.jpg);"); break;
        case 9: ui->background_label->setStyleSheet("border-image: url(:/mypic/empty.png);"); break;
        }
        return;
    }
    if(change_back) // 切到黑屏再切换背景
    {
        ui->background_label->setStyleSheet("border-image: url(:/mypic/black.png);");
        ui->diabox_label->setVisible(false);
        ui->label->setVisible(false);
        ui->heart_progressBar->setVisible(false);
        ui->regret_progressBar->setVisible(false);
        ui->heart->setVisible(false);
        ui->regret->setVisible(false);
        ui->person1->setVisible(false);
        //bgm->stop();
        MySleep(200);
        switch(background) {
        case 0: ui->background_label->setStyleSheet("border-image: url(:/mypic/lab.png);"); break;
        case 1: ui->background_label->setStyleSheet("border-image: url(:/mypic/title.jpg);"); break;
        case 2: ui->background_label->setStyleSheet("border-image: url(:/mypic/Front.jpg);"); break;
        case 3: ui->background_label->setStyleSheet("border-image: url(:/mypic/lab_2.png);"); break;
        case 4: ui->background_label->setStyleSheet("border-image: url(:/mypic/ruin.png);"); break;
        case 5: ui->background_label->setStyleSheet("border-image: url(:/mypic/seperate.png);"); break;
        case 6: ui->background_label->setStyleSheet("border-image: url(:/mypic/end.png);"); break;
        case 7: ui->background_label->setStyleSheet("border-image: url(:/mypic/end_2.jpg);"); break;
        case 9: ui->background_label->setStyleSheet("border-image: url(:/mypic/empty.png);"); break;
        }
    }
    ui->diabox_label->setVisible(true);
    ui->label->setVisible(true);
    ui->heart_progressBar->setVisible(true);
    ui->regret_progressBar->setVisible(true);
    ui->heart->setVisible(true);
    ui->regret->setVisible(true);
    ui->person1->setVisible(true);
    change_back = 0;
    return;
}

void MyDialog1::MakeChoice() {
    if(choice_num[choice_id] == 2) {
        ui->BtnC1->setText(choice_content[choice_id][0]);
        ui->BtnC2->setText(choice_content[choice_id][1]);
        ui->BtnC1->setVisible(true);
        ui->BtnC2->setVisible(true);
    }
    else if(choice_num[choice_id] == 3) {
        ui->BtnC1->setText(choice_content[choice_id][0]);
        ui->BtnC2->setText(choice_content[choice_id][1]);
        ui->BtnC3->setText(choice_content[choice_id][2]);
        if(choice_id == 4) // todo
        {
            ui->temp_choice4->setVisible(true);
            ui->label->setText("他：好。<br>注：D能够使γ-PD失活，但是至少注射一次以上的γ-PD，CPD才能发挥作用");
        }
        ui->BtnC1->setVisible(true);
        ui->BtnC2->setVisible(true);
        ui->BtnC3->setVisible(true);
    }
    is_making_choice = 1;
    choice_id ++ ;
    return;
}

void MyDialog1::on_NexSenBtn_clicked() {
    if(endflag) return;
    if(startflag == 0) return;
    if(startflag == 3) startflag ++ ;
    if(startflag == 2) {
        ui->diabox_label->setVisible(true);
        ui->label->setVisible(true);
        ui->label_begin1->setVisible(false);
        ui->heart_progressBar->setVisible(true);
        ui->regret_progressBar->setVisible(true);
        ui->heart->setVisible(true);
        ui->regret->setVisible(true);
        background = 0;
        change_back = 1;
        startflag = 3;
        //return;
    }
    if(startflag == 1) {
        Begin2();
        startflag = 2;
        return;
    }
    if(regret == 100) {
        endflag = 1;
        background = 9;
        End();
        return;
    }
    if(startflag == 4) ui->hint_label->setVisible(false);
    if(is_making_choice) return;
    if(input_text_flag == 0) {
        ReadText1();
        input_text_flag = 1;
        ui->label->setAlignment(Qt::AlignHCenter);
        ui->label->setAlignment(Qt::AlignVCenter);
        ui->label->setWordWrap(true);
    }
    count_text1 ++ ;
    if (output_text_flag == 1) {
        output_text_flag = 0;
        MakeChoice();
    }
    else if (enterGame1Flag) {
        enterGame1Flag = false;
        game1 = new MineSweeper;
        game1->show();
        count_text1 -- ;
        // if (win) count_text1 ++ ;
    }
    else if (enterGame2Flag) {
        enterGame2Flag = false;
        game2 = new FiveInARow;
        game2->show();
        if (game2->Winner == Piece::PLAYER1) count_text1 -- ;
        else if (game2->Winner == Piece::PLAYER2) count_text1 += 2 ;
    }
    else {
        setBackground();
        ui->label->setText(text1[count_text1]);
        if (text_flag1[count_text1] == '<') enterGame1Flag = true;
        if (text_flag1[count_text1] == '>') enterGame2Flag = true;
        if((text_flag1[count_text1] == '@' || text_flag1[count_text1] == '#') && output_text_flag == 0)
            output_text_flag = 1;
        if(text_flag1[count_text1] == '~' || text_flag1[count_text1] == '@') {
            if(count_text1 > 72) setPerson(2); // change if-condition
            else setPerson(1);
        }
        else setPerson(0);

        switch(count_text1) {
            //case 4: background = 3; change_back = 1; break;
            case 11: background = 3; change_back = 1; break;
            case 26: background = 0; change_back = 1; count_text1 = 30; break;
            case 28: background = 0; change_back = 1; count_text1 = 30; break;
            case 30: background = 0; change_back = 1; break;
            case 34:
                background = 4;
                change_back = 1;
                if (!heroineGoFlag) count_text1 = 46;
                else count_text1 ++ ;
                break;
            case 35:
                background = 4;
                change_back = 1;
                if (!heroineGoFlag) count_text1 = 46;
                break;
            case 46:
                background = 0;
                change_back = 1;
                if (CPD_flag) count_text1 = 66;
                else count_text1 = 64;
                break;
            //case 35: background = 4; change_back = 1; break;
            //case 24: changeBgm(2); break;
            //case 36: regret += 50; heart = 50; break;
            //case 40: background = 3; change_back = 1; break;
            //case 41: changeBgm(3); break;
            //case 50: background = 5; change_back = 1; break;
            //case 52: regret++; break;
            case 66: background = 0; change_back = 1; break;
            case 72: background = 5; change_back = 1; break;
            //default: background = 3; change_back = 1; break;
            // todo
        }
        UpdateHeartRegret();
    }
    return;
}

void MyDialog1::on_BtnC1_clicked() {
    //count_text1 += 1;
    // 这里通过对count_text1的调整进入分支剧情，具体数值需要文本内容确定后填写
    count_text1 += jump[choice_id - 1][0];
    heart += heart_change[choice_id - 1][0];
    if(choice_id == 9) regret = 90; // todo
    //regret += regret_change[choice_id - 1][0];
    UpdateHeartRegret();
    ui->BtnC1->setVisible(false);
    ui->BtnC2->setVisible(false);
    ui->BtnC3->setVisible(false);
    is_making_choice = 0;
    ui->temp_choice4->setVisible(false);
    on_NexSenBtn_clicked();
    //if (choice_id - 1 == 1) choice_id ++ ;
    if (choice_id - 1 == 5 && heroineGoFlag) choice_id ++ ;
    if (count_text1 == 5) background = 4; change_back = 1;
    return;
}

void MyDialog1::on_BtnC2_clicked() {
    if (choice_id - 1 == 3) heroineGoFlag = false;
    //count_text1 += -1;
    // 这里通过对count_text1的调整进入分支剧情，具体数值需要文本内容确定后填写
    count_text1 += jump[choice_id - 1][1];
    heart += heart_change[choice_id - 1][1];
    //regret += regret_change[choice_id - 1][1];
    UpdateHeartRegret();
    ui->BtnC1->setVisible(false);
    ui->BtnC2->setVisible(false);
    ui->BtnC3->setVisible(false);
    is_making_choice = 0;
    ui->temp_choice4->setVisible(false);
    on_NexSenBtn_clicked();
    if (choice_id - 1 == 0) choice_id ++ ;
    if (choice_id - 1 == 5 && heroineGoFlag) choice_id ++ ;
    return;
}

void MyDialog1::on_BtnC3_clicked() {
    if (choice_id - 1 == 3) heroineGoFlag = false;
    if (choice_id - 1 == 4) {
        CPD_flag = true;
        jump[6][1] = 11;
    }
    //count_text1 += -1;
    // 这里通过对count_text1的调整进入分支剧情，具体数值需要文本内容确定后填写
    count_text1 += jump[choice_id - 1][2];
    heart += heart_change[choice_id - 1][2];
    //regret += regret_change[choice_id - 1][2];
    UpdateHeartRegret();
    ui->BtnC1->setVisible(false);
    ui->BtnC2->setVisible(false);
    ui->BtnC3->setVisible(false);
    is_making_choice = 0;
    ui->temp_choice4->setVisible(false);
    on_NexSenBtn_clicked();
    return;
}

void MyDialog1::mousePressEvent(QMouseEvent *event) {
    if(event->button()) on_NexSenBtn_clicked();
    return;
}

void MyDialog1::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_F) on_NexSenBtn_clicked();
    return;
}

void MyDialog1::on_Start_clicked() {
    ui->Start->setVisible(false);
    Begin();
    return;
}

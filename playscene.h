#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QPixmap>
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "mypushbutton.h"
#include "mycoin.h"
#include "dataconfig.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr);
    // 重写构造函数，获取选择的关卡数
    PlayScene(int level);
    // 重写析构函数，用于测试场景是否正确释放
    ~PlayScene();
    // 重写绘图事件，绘制窗口背景
    void paintEvent(QPaintEvent *);
    // 创建金币背景图
    void createCoinSceneBg();

public slots:
    // 退出按钮点击槽函数
    void closeBtn_Clicked();
    // 处理胜利信号槽函数
    void winSignal_Emited();

signals:
    // 退出按钮点击后触发返回选择关卡场景信号
    void chooseSceneBack();
    // 胜利信号
    void winSignal();

private:
    // 维护关卡数
    int level;
    // 维护退出按钮
    MyPushButton *closeBtn;
    // 维护当前关卡使用的二维数组
    int gameArray[4][4];
    // 维护当前场景金币数组
    MyCoin *coinBtn[4][4];
    // 维护当前关卡是否胜利
    bool isWin = 1;
    // 维护胜利画面
    QLabel *winlabel;
    // 维护播放器
    QAudioOutput *audioOutput;
    // 维护返回按钮音效
    QMediaPlayer *backSound;
    // 维护点击金币音效
    QMediaPlayer *coinSound;
    // 维护胜利音效
    QMediaPlayer *winSound;
};

#endif // PLAYSCENE_H

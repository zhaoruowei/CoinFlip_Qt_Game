#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include <QPixmap>
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "mypushbutton.h"
#include "playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    // 重写绘图事件
    void paintEvent(QPaintEvent *);
    // 创建关卡按钮
    void createLevelBtn();

public slots:
    // 声明退出按钮点击槽函数
    void closeBtn_Clicked();
    // 监听子窗口退出按钮信号
    void chooseScene_Back();

signals:
    void chooseSceneBack();

private:
    // 维护退出按钮
    MyPushButton *closeBtn;
    // 维护游戏场景界面
    PlayScene *pScene;
    // 维护播放器
    QAudioOutput *audioOutput;
    // 维护选择关卡按钮音效
    QMediaPlayer *chooseSound;
    // 维护返回按钮音效
    QMediaPlayer *backSound;
};

#endif // CHOOSELEVELSCENE_H

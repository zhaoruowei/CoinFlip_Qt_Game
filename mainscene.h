#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "mypushbutton.h"
#include "chooselevelscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    // 重写paintEvent事件 画背景图
    void paintEvent(QPaintEvent *);

public slots:
    // 自定义按钮点击槽函数
    void MyPushButton_clicked();
    // 监听子窗口触发的chooseSceneBack信号
    void chooseScene_Back();

private:
    Ui::MainScene *ui;
    // 维护一个自定义开始按钮类
    MyPushButton *startBtn;
    // 维护一个关卡选择窗口类
    ChooseLevelScene *chooseScene;
    // 维护背景音乐
    QMediaPlayer *bgMusic;
    // 维护播放器
    QAudioOutput *audioOutput;
    // 维护开始按钮点击音效
    QMediaPlayer *startSound;
};
#endif // MAINSCENE_H

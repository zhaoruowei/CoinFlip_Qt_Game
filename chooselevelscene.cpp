#include "chooselevelscene.h"

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    // 声明游戏界面
    this->pScene = nullptr;

    // 初始化播放器
    this->audioOutput = new QAudioOutput;
    audioOutput->setVolume(50);

    // 初始化选择关卡按钮音效
    // 加载音效
    // 加载播放音效
    this->chooseSound = new QMediaPlayer;
    this->chooseSound->setSource(QUrl("qrc:/res/TapButtonSound.wav"));

    // 初始化返回按钮音效
    this->backSound = new QMediaPlayer;
    this->backSound->setSource(QUrl("qrc:/res/BackButtonSound.wav"));


    // 设置窗口大小
    this->setFixedSize(320, 588);
    // 设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    // 设置标题
    this->setWindowTitle("Choose Level");

    // 创建菜单栏
    QMenuBar *bar = this->menuBar();
    this->setMenuBar(bar);
    // 创建开始菜单
    QMenu *startMenu = bar->addMenu("Start");
    // 创建按钮菜单项
    QAction *quitAction = startMenu->addAction("Quit");
    // 绑定菜单项槽函数
    connect(quitAction, &QAction::triggered, this, [=](){
        this->close();
    }, Qt::AutoConnection);

    // 创建退出按钮
    this->closeBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    // 绑定父窗口
    this->closeBtn->setParent(this);
    this->closeBtn->move(this->width() - this->closeBtn->width(), this->height() - this->closeBtn->height());
    connect(this->closeBtn, SIGNAL(clicked()), this, SLOT(closeBtn_Clicked()));

    // 创建选择关卡按钮
    this->createLevelBtn();

}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    // 加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    // 加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5, 30, pix.width(), pix.height(), pix);
}
void ChooseLevelScene::closeBtn_Clicked()
{
//    qDebug() << "点击了";

    // 绑定播放器
    this->backSound->setAudioOutput(audioOutput);
    // 播放音效
    this->backSound->play();

    QTimer::singleShot(500, this, [=](){
        this->hide();
        // 触发自定义信号，关闭自身
        emit this->chooseSceneBack();
    });
}
// 创建关卡按钮
void ChooseLevelScene::createLevelBtn()
{
    for (int i = 0; i < 20; i++)
    {
        MyPushButton *menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+(i%4)*70, 130+(i/4)*70);
        // 显示文字
        QLabel *label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->setText(QString::number(i+1));
        // 设置文字居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->move(25+(i%4)*70, 130+(i/4)*70);
        // 鼠标事件穿透, 点击后穿透按钮上层的label标签，传递给下层的按钮
        label->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        // 绑定按钮点击信号槽
        connect(menuBtn, &MyPushButton::clicked, this, [=](){
//            qDebug() << "点击了" << i;
            if (this->pScene == nullptr)
            {
                // 绑定播放器
                this->chooseSound->setAudioOutput(audioOutput);
                // 播放音效
                this->chooseSound->play();

                this->hide();
                this->pScene = new PlayScene(i+1);
                this->pScene->setGeometry(this->geometry());
                this->pScene->show();
                connect(this->pScene, SIGNAL(chooseSceneBack()), this, SLOT(chooseScene_Back()));
            }
        }, Qt::AutoConnection);
    }
}
void ChooseLevelScene::chooseScene_Back()
{
//    qDebug() << "子场景触发了";
    this->setGeometry(this->pScene->geometry());
    this->show();
    // 释放子场景
    delete this->pScene;
    this->pScene = nullptr;
}

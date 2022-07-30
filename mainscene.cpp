#include "mainscene.h"
#include "ui_mainscene.h"

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    // 配置主场景

    // 初始化播放器
    this->audioOutput = new QAudioOutput;
    audioOutput->setVolume(50);
    // 初始化音乐
    // 加载开始按钮音效
    this->startSound = new QMediaPlayer;
    this->startSound->setSource(QUrl("qrc:/res/TapButtonSound.wav"));
    // 加载背景音乐
    this->bgMusic = new QMediaPlayer;
    this->bgMusic->setSource(QUrl("qrc:/res/bgmusic.mp3"));
    this->bgMusic->setAudioOutput(audioOutput);
    this->bgMusic->play();

    // 设置固定大小
    setFixedSize(320, 588);
    // 设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    // 设置标题
    setWindowTitle("CoinFlip");
    // 菜单栏功能
    connect(ui->actionExit, &QAction::triggered, this, [=](){
        this->close();
    }, Qt::AutoConnection);
    connect(ui->actionStop_BGM, &QAction::triggered, this, [=](){
        this->bgMusic->pause();
    }, Qt::AutoConnection);
    connect(ui->actionStart_BGM, &QAction::triggered, this, [=](){
        this->bgMusic->play();
    }, Qt::AutoConnection);

    // 创建开始按钮
    this->startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5, this->height()*0.7);
    // 绑定信号和槽
    connect(startBtn, SIGNAL(clicked()), this, SLOT(MyPushButton_clicked()));

    // 创建选择关卡界面（必须在构造函数中创建对象）
    this->chooseScene = new ChooseLevelScene;
    // 子窗口关闭，触发子窗口自定义信号
    connect(this->chooseScene, SIGNAL(chooseSceneBack()), this, SLOT(chooseScene_Back()));
}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    // 拉伸图片
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    // 画图标
    pix.load(":/res/Title.png");
    // 缩放
    pix = pix.scaled(pix.width()*0.5, pix.height()*0.5);
    // 绘制
    painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);
}
void MainScene::MyPushButton_clicked()
{
    // 播放音乐
    this->startSound->setAudioOutput(audioOutput);
    this->startSound->play();

    startBtn->zoom1();
    startBtn->zoom2();
    // 延迟处理,延迟隐藏当前窗口，显示新窗口
    // 单位毫秒
    QTimer::singleShot(500, this, [=](){
        // 隐藏当前界面
        this->hide();
        this->chooseScene->setGeometry(this->geometry());
        // 显示选择关卡界面
        this->chooseScene->show();
    });
}
void MainScene::chooseScene_Back()
{
//    qDebug() << "子窗口触发了";
    this->setGeometry(this->chooseScene->geometry());
    this->chooseScene->close();
    this->show();
}

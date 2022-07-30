#include "playscene.h"

PlayScene::PlayScene(QWidget *parent)
    : QMainWindow{parent}
{

}
PlayScene::PlayScene(int level)
{
    // 初始化关卡等级
    this->level = level;
    // 初始化关卡二维数组
    dataConfig config;
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            gameArray[i][j] = config.mData[this->level][i][j];
        }
    }

    // 初始化胜利界面
    this->winlabel = new QLabel;
    QPixmap pixmap;
    pixmap.load(":/res/LevelCompletedDialogBg.png");
    winlabel->setGeometry(0, 0, pixmap.width(), pixmap.height());
    winlabel->setPixmap(pixmap);
    winlabel->setParent(this);
    winlabel->move(35, -pixmap.height());

    // 初始化播放器
    this->audioOutput = new QAudioOutput;
    this->audioOutput->setVolume(50);

    // 加载返回按钮音效
    this->backSound = new QMediaPlayer;
    this->backSound->setSource(QUrl("qrc:/res/BackButtonSound.wav"));
    // 加载点击金币音效
    // 加载音效
    this->coinSound = new QMediaPlayer;
    this->coinSound->setSource(QUrl("qrc:/res/ConFlipSound.wav"));
    // 加载胜利音效
    // 加载音效
    this->winSound = new QMediaPlayer;
    this->winSound->setSource(QUrl("qrc:/res/LevelWinSound.wav"));

    // 设置窗口大小
    this->setFixedSize(320, 588);
    // 设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    // 设置标题
    this->setWindowTitle("Level"+QString::number(level));

    // 创建菜单栏
    QMenuBar *bar = this->menuBar();
    this->setMenuBar(bar);
    // 创建开始菜单
    QMenu *startMenu = bar->addMenu("Start");
    // 创建退出菜单项
    QAction *quitAction = startMenu->addAction("Exit");
    // 连接菜单项槽函数
    connect(quitAction, &QAction::triggered, this, [=](){
        this->close();
    }, Qt::AutoConnection);

    // 创建返回按钮
    this->closeBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    this->closeBtn->setParent(this);
    // 调整按钮位置
    this->closeBtn->move(this->width() - this->closeBtn->width(), this->height() - this->closeBtn->height());
    // 绑定按钮点击信号槽
    connect(this->closeBtn, SIGNAL(clicked()), this, SLOT(closeBtn_Clicked()));

    // 显示当前关卡
    QLabel *label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    QString str = QString("Level: %1").arg(this->level);
    label->setText(str);
    // 设置大小和位置
    label->setGeometry(QRect(30, this->height() - 50,120, 50));

    // 创建金币背景图
    this->createCoinSceneBg();

    // 绑定胜利信号和槽函数
    connect(this, SIGNAL(winSignal()), this, SLOT(winSignal_Emited()));


}
PlayScene::~PlayScene()
{
//    qDebug() << this->level << "释放了";
}
// 背景设置
void PlayScene::paintEvent(QPaintEvent *)
{
    // 加载背景图片
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    // 加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5, pix.height()*0.5);
    painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);
}
void PlayScene::closeBtn_Clicked()
{
//    qDebug() << "clicked";
    // 播放音乐
    this->backSound->setAudioOutput(audioOutput);
    this->backSound->play();

    // 延迟0.5s执行当前窗口关闭，触发选择关卡场景显示信号
    QTimer::singleShot(500, this, [=]{
        this->close();
        emit this->chooseSceneBack();
    });
}
void PlayScene::createCoinSceneBg()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // 绘制背景图片
            QLabel *label = new QLabel;
            label->setParent(this);
            label->setGeometry(0, 0, 50, 50);
            label->setPixmap(QPixmap(":/res/BoardNode(1).png"));
            label->move(57 + i*50, 200 + j*50);

            // 创建金币对象
            QString img;
            if (gameArray[i][j] == 1)
            {
                img = ":/res/Coin0001.png";
            }
            else
            {
                img = ":/res/Coin0008.png";
            }

            MyCoin *coin = new MyCoin(img);
            coin->setParent(this);
            coin->move(57 + i*50, 200 + j*50);
            coin->x = i;
            coin->y = j;
            coin->flag = gameArray[i][j];

            this->coinBtn[i][j] = coin;

            // 监听每个金币的点击事件
            connect(coin, &MyCoin::clicked, coin, [=](){
                // 播放音效
                this->coinSound->setAudioOutput(this->audioOutput);
                this->coinSound->play();

                coin->changFlag();
                // 同步金币状态
                gameArray[i][j] = gameArray[i][j]==1?0:1;

                // 延时翻动周围上下左右的4个金币
                QTimer::singleShot(300, this, [=](){
                    // 判断点击的金币位置
                    if (coin->x+1 <=3)
                    {
                        coinBtn[coin->x+1][coin->y]->changFlag();
                        gameArray[coin->x+1][coin->y] = gameArray[coin->x+1][coin->y]==1?0:1;
                    }
                    if (coin->x-1 >=0)
                    {
                        coinBtn[coin->x-1][coin->y]->changFlag();
                        gameArray[coin->x-1][coin->y] = gameArray[coin->x-1][coin->y]==1?0:1;

                    }
                    if (coin->y+1 <= 3)
                    {
                        coinBtn[coin->x][coin->y+1]->changFlag();
                        gameArray[coin->x][coin->y+1] = gameArray[coin->x][coin->y+1]==1?0:1;
                    }
                    if (coin->y-1 >= 0)
                    {
                        coinBtn[coin->x][coin->y-1]->changFlag();
                        gameArray[coin->x][coin->y-1] = gameArray[coin->x][coin->y-1]==1?0:1;
                    }
                    // 重置胜利判断标志
                    this->isWin = 1;
                    // 判断是否胜利
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {

//                            qDebug() << i+1 << "," << j+1 << ": " << coinBtn[i][j]->flag;
                            if (coinBtn[i][j]->flag==0)
                            {
                                this->isWin = 0;
                                break;
                            }
                        }
                    }
                    if (this->isWin)
                    {
//                        qDebug() << "win";
                        emit winSignal();
                        // 胜利后禁止翻转金币
                        for (int i = 0; i < 4; i++)
                        {
                            for (int j = 0; j < 4; j++)
                            {
                                coinBtn[i][j]->isWin=1;
                            }
                        }
                    }
                });
            }, Qt::AutoConnection);
        }
    }
}
void PlayScene::winSignal_Emited()
{
//    qDebug() << "win";
    // 为胜利画面添加动画效果
    QPropertyAnimation *animation = new QPropertyAnimation(winlabel, "geometry");
    // 设置持续时间
    animation->setDuration(1000);
    // 设置起始位置
    animation->setStartValue(QRect(winlabel->x(),winlabel->y(),winlabel->width(),winlabel->height()));
    // 设置结束位置
    animation->setEndValue(QRect(winlabel->x(),winlabel->y()+198,winlabel->width(),winlabel->height()));
    // 设置弹出效果
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();

    // 播放音乐
    this->winSound->setAudioOutput(this->audioOutput);
    this->winSound->play();
//    qDebug() << "执行完了";
}

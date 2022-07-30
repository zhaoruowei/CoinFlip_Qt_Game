#include "mycoin.h"

MyCoin::MyCoin(QWidget *parent)
    : QPushButton{parent}
{

}
// 参数代表点击金币后，不同事件段金币显示的图片路径
MyCoin::MyCoin(QString butImg)
{
    QPixmap pixmap;
    bool ret = pixmap.load(butImg);
    if (!ret)
    {
        qDebug() << butImg << "加载失败";
    }
    // 设置按钮格式
    this->setFixedSize(pixmap.width(), pixmap.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(), pixmap.height()));

    // 初始化定时器
    this->timer1 = new QTimer(this);
    this->timer2 = new QTimer(this);

    // 绑定定时器到时槽函数
    connect(this->timer1, &QTimer::timeout, this, [=](){
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1.png").arg(this->m_min++);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
        if (this->m_min > this->m_max)
        {
            this->m_min = 1;
            this->isAnimation = 0;
            this->timer1->stop();
        }
    }, Qt::AutoConnection);
    connect(this->timer2, &QTimer::timeout, this, [=](){
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1.png").arg(this->m_max--);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
        if (this->m_min > this->m_max)
        {
            this->m_max = 8;
            this->isAnimation = 0;
            this->timer2->stop();
        }
    }, Qt::AutoConnection);
}
void MyCoin::changFlag()
{
    if (this->flag) // 金币正面时
    {
        this->timer1->start(30);
        this->isAnimation = 1;
        this->flag = 0;
    }
    else
    {
        this->timer2->start(30);
        this->isAnimation = 1;
        this->flag = 1;
    }
}
void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if (isAnimation || isWin)
    {
        return;
    }
    else
    {
        // 交给父类执行事件
        return QPushButton::mousePressEvent(e);
    }
}

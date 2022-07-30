#include "mypushbutton.h"

MyPushButton::MyPushButton(QWidget *parent)
    : QPushButton{parent}
{

}

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;
    // 创建QPixmap对象
    QPixmap pixmap;
    // 判断是否能够正常加载图片，不能则提示加载失败
    bool ret = pixmap.load(this->normalImgPath);
    if (!ret)
    {
        qDebug() << normalImg << "图片加载失败！";
    }
    // 设置图片尺寸
    this->setFixedSize(pixmap.width(), pixmap.height());
    // 设置样式表CSS
    this->setStyleSheet("QPushButton{border:0px;}");
    // 设置图标
    this->setIcon(pixmap);
    // 设置图标大小
    this->setIconSize(QSize(pixmap.width(), pixmap.height()));
}
void MyPushButton::zoom1()
{
//    qDebug() << "变化了";
    // 创建动画对象
    QPropertyAnimation *animational = new QPropertyAnimation(this, "geometry");
    // 设置时间间隔, 单位毫秒
    animational->setDuration(200);
    // 创建起始位置
    animational->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    // 创建结束位置
    animational->setEndValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    // 设置缓和曲线,QEasingCurve::OutBounce为弹跳效果
    animational->setEasingCurve(QEasingCurve::OutBounce);
    // 执行动画
    animational->start();
}
void MyPushButton::zoom2()
{
    // 创建动画对象
    QPropertyAnimation *animational = new QPropertyAnimation(this, "geometry");
    animational->setDuration(200);
    animational->setStartValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    animational->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animational->setEasingCurve(QEasingCurve::OutBounce);
    animational->start();
}
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    // 判断传入的按下显示按钮图片是否可用
    if (pressImgPath != "")
    {
        QPixmap pixmap;
        bool ret = pixmap.load(pressImgPath);
        if (!ret)
        {
            qDebug() << pressImgPath << "加载失败";
        }
        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
    }
    // 交给父类执行按下事件
    return QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    QPixmap pixmap;
    bool ret = pixmap.load(normalImgPath);
    if (!ret)
    {
        qDebug() << normalImgPath << "加载失败";
    }
    this->setFixedSize(pixmap.width(), pixmap.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(), pixmap.height()));
    // 交给父类处理释放事件
    return QPushButton::mouseReleaseEvent(e);
}

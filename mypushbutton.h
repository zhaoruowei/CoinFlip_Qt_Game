#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QDebug>
#include <QPropertyAnimation>
#include <QRect>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);
    // 重写构造函数
    MyPushButton(QString normalImg, QString pressImg="");
    // 按钮点击特效
    void zoom1();
    void zoom2();
    // 重写按钮按下，释放事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    // 成员属性
    // 存放正常显示图片路径
    QString normalImgPath;
    // 存放按下显示图片路径
    QString pressImgPath;
};

#endif // MYPUSHBUTTON_H

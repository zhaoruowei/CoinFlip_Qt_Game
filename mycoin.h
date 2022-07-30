#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QDebug>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    explicit MyCoin(QWidget *parent = nullptr);
    // 重写构造函数
    MyCoin(QString butImg);
    // 声明金币状态改变函数
    void changFlag();
    // 重写按钮按下事件，如果动画标志为1时，则不能点击，否则可以点击
    void mousePressEvent(QMouseEvent *e);

public:
    // 维护金币坐标，以及正反
    int x;
    int y;
    bool flag;
    // 维护金币获胜状态
    bool isWin = 0;

private:
    // 维护两个定时器（正面翻反面，反面翻正面）
    QTimer *timer1;
    QTimer *timer2;
    // 维护反转金币时最小图片和最大图片
    int m_min = 1;
    int m_max = 8;
    // 维护金币翻转动画状态
    bool isAnimation = 0;
};

#endif // MYCOIN_H

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent) {
//    set the size of canvas as 600 * 600
    this->resize(600, 600);
}

Widget::~Widget() {
}

void Widget::paintEvent(QPaintEvent *event) {
    painter = new QPainter(this);
//    set the color of the axis
    QPen axisPen(QColor(0, 0, 0));
//    set the color of pixels on the line drawn
    QBrush* pixBrush = new QBrush(QColor(0, 0, 0));
    painter->setPen(axisPen);
    painter->setBrush(*pixBrush);
//    set origin at (300, 300) of widget
    painter->translate(300, 300);
    painter->drawLine(QPoint(-300, 0), QPoint(300, 0));
    painter->drawLine(QPoint(0, -300), QPoint(0, 300));
    painter->rotate(-90);
    points.append(QPoint(0, 0));
    points.append(QPoint(10, 10));
    points.append(QPoint(20, 20));
//    points = getPoints();
    drawPixel(points, painter);
    painter->end();
}

void Widget::drawPixel(QVector<QPoint> pix, QPainter* painter) {
    for(int i = 0; i < pix.length(); i++) {
        painter->drawRect(pix[i].x() - 5, pix[i].y() - 5, 10, 10);
        this->update();
    }
}

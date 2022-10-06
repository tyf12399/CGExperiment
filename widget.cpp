#include "widget.h"
#include "cgalgorithm.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent) {
    //    set the size of widget as 600 * 600
    this->resize(600, 600);
}

Widget::~Widget() {
}

void Widget::paintEvent(QPaintEvent *event) {
    painter = new QPainter(this);
    //    transform the coordinate
    painter->translate(300, 300);
    painter->drawLine(QPoint(-300, 0), QPoint(300, 0));
    painter->drawLine(QPoint(0, -300), QPoint(0, 300));
    painter->scale(1, -1);
    painter->save();

    //    set the color of the axis
    QPen *axisPen = new QPen(QColor(0, 0, 0));
    //    set the color of pixels on the line drawn
    QBrush* pixBrush = new QBrush(QColor(0, 255, 0));
    painter->setPen(*axisPen);
    painter->setBrush(*pixBrush);

    CGAlgorithm *cal = new CGAlgorithm();
    points = cal->getLinePoints(QPoint(0, 0), QPoint(-10, -1), "dda");
    drawPixel(points, painter);
    painter->end();
}

void Widget::drawPixel(QVector<QPoint> pix, QPainter* painter) {
    for(int i = 0; i < pix.length(); i++) {
        painter->drawRect(pix[i].x() * 10 - 5, pix[i].y() * 10 - 5, 10, 10);
    }
}

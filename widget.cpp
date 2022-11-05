#include "widget.h"
#include "cgalgorithm.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent) {
    //    set the size of widget as 600 * 600
    this->resize(600, 600);
    this->setWindowTitle("CGExperiment");

// TODO: add a gui to input parameters

}

Widget::~Widget() {
}

void Widget::paintEvent(QPaintEvent *event) {
    painter = new QPainter(this);

    //    set the color
    QPen *axisPen = new QPen(QColor(0, 0, 0), 2);
    QPen *mapPen = new QPen(QColor(50, 50, 50), 1, Qt::DotLine);
    QPen *linePen = new QPen(QColor(255, 0, 0), 2);
    QBrush *fillBrush = new QBrush(QColor(0, 0, 0, 0));
    //    transform the coordinate and draw background
    painter->translate(300, 300);
    painter->scale(1, -1);
    painter->setPen(*axisPen);
    painter->drawLine(QPoint(-400, 0), QPoint(400, 0));
    painter->drawLine(QPoint(0, -400), QPoint(0, 400));

    painter->setPen(*mapPen);
    for(int i = -405; i < 405; i += 10) {
        painter->drawLine(QPoint(-400, i), QPoint(400, i));
        painter->drawLine(QPoint(i, -400), QPoint(i, 400));
    }
    painter->save();


    //    set the color of pixels on the line drawn
    QBrush* pixBrush = new QBrush(QColor(0, 255, 255));
    painter->setBrush(*pixBrush);



    // choose the shape to draw
    QString shape = "Ellipse";

    CGAlgorithm *cal = new CGAlgorithm();

    if(shape == "Line") {
        QPoint *start = new QPoint(0, 15);
        QPoint *end = new QPoint(10, -1);
        points = cal->getLinePoints(*start, *end, "bresenham");
        drawPixel(points, painter);
        // give a reference
        painter->setPen(*linePen);
        painter->drawLine(*start * 10, *end * 10);
    } else if(shape == "Circle") {
        QPoint *center = new QPoint(5, 0);
        int r = 20;
        points = cal->getCirclePoints(*center, r, "bresenham");
        drawPixel(points, painter);
        // give a reference
        painter->setPen(*linePen);
        painter->setBrush(*fillBrush);
        painter->drawEllipse(*center * 10, r * 10, r * 10);
    } else if(shape == "Ellipse") {
        QPoint *center = new QPoint(5, 0);
        int a = 20;
        int b = 10;
        points = cal->getEllipsePoints(*center, a, b);
        drawPixel(points, painter);
        // give a reference
        painter->setPen(*linePen);
        painter->setBrush(*fillBrush);
        painter->drawEllipse(*center * 10, a * 10, b * 10);
    }
    painter->end();
}

void Widget::drawPixel(QVector<QPoint> pix, QPainter* painter) {
    // paint the pixels on map
    for(int i = 0; i < pix.length(); i++) {
        painter->drawRect(pix[i].x() * 10 - 5, pix[i].y() * 10 - 5, 10, 10);
    }
}

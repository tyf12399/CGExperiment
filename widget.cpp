#include "widget.h"
#include "cgalgorithm.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent) {
    //    set the size of widget as 600 * 600
    this->resize(800, 600);
    this->setWindowTitle("CGExperiment");
// TODO: add a gui to input parameters
    layout = new QHBoxLayout();
    argsLayout = new QVBoxLayout();
    shapeSelect = new QComboBox();
    methodSelect = new QComboBox();
    argsInput = new QTextEdit();
    submmit = new QPushButton("confirm");
    shapeSelect->addItem("Line");
    shapeSelect->addItem("Circle");
    shapeSelect->addItem("Ellipse");
    shapeSelect->addItem("Polygon");
    methodSelect->addItem("dda");
    methodSelect->addItem("bresenham");

    argsLayout->addWidget(shapeSelect);
    argsLayout->addWidget(methodSelect);
    argsLayout->addWidget(argsInput);
    argsLayout->addWidget(submmit);
    layout->addSpacing(600);
    layout->addLayout(argsLayout);
    this->setLayout(layout);


    connect(shapeSelect, QOverload<int>::of(&QComboBox::currentIndexChanged),
    [ = ](int index) {
        if(index == 0) {
            methodSelect->clear();
            methodSelect->addItem("dda");
            methodSelect->addItem("bresenham");
        } else if(index == 1) {
            methodSelect->clear();
            methodSelect->addItem("mid-point");
            methodSelect->addItem("bresenham");
        } else if(index == 2) {
            methodSelect->clear();
            methodSelect->addItem("mid-point");
        } else if(index == 3) {
            methodSelect->clear();
            methodSelect->addItem("flood");
        }
        argsInput->clear();
    });
    connect(submmit, &QPushButton::pressed, [ = ] {
        this->repaint();
        submmit->setText("repaint");
    });
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
    painter->drawLine(QPoint(-300, 0), QPoint(300, 0));
    painter->drawLine(QPoint(0, -300), QPoint(0, 300));

    painter->setPen(*mapPen);
    for(int i = -305; i < 305; i += 10) {
        painter->drawLine(QPoint(-300, i), QPoint(300, i));
        painter->drawLine(QPoint(i, -300), QPoint(i, 300));
    }
    painter->save();


    //    set the color of pixels on the line drawn
    QBrush* pixBrush = new QBrush(QColor(0, 255, 255));
    painter->setBrush(*pixBrush);


    QString shape = shapeSelect->currentText();
    QString method = methodSelect->currentText();
    QString args = argsInput->toPlainText();
    if(!args.isEmpty()) {
        CGAlgorithm *cal = new CGAlgorithm();
        if(shape == "Line") {
            QPoint *start = new QPoint();
            QPoint *end = new QPoint();
            textParser(args, *start, *end);
            points = cal->getLinePoints(*start, *end, method);
            drawPixel(points, painter);
            // give a reference
            painter->setPen(*linePen);
            painter->drawLine(*start * 10, *end * 10);
        } else if(shape == "Circle") {
            QPoint *center = new QPoint();
            int r;
            textParser(args, *center, r);
            points = cal->getCirclePoints(*center, r, method);
            drawPixel(points, painter);
            // give a reference
            painter->setPen(*linePen);
            painter->setBrush(*fillBrush);
            painter->drawEllipse(*center * 10, r * 10, r * 10);
        } else if(shape == "Ellipse") {
            QPoint *center = new QPoint();
            int a;
            int b;
            textParser(args, *center, a, b);
            points = cal->getEllipsePoints(*center, a, b);
            drawPixel(points, painter);
            // give a reference
            painter->setPen(*linePen);
            painter->setBrush(*fillBrush);
            painter->drawEllipse(*center * 10, a * 10, b * 10);
        } else if(shape == "Polygon") {
            QVector<QVector<QPoint>> verticesList = {};
//            for (int i = 1; i <= 2; ++i) {
//                QVector<QPoint> vertices = {};
//                vertices.append(QPoint(9 * i, 10 * i));
//                vertices.append(QPoint(10 * i, -10 * i));
//                vertices.append(QPoint(-5 * i, -5 * i));
//                vertices.append(QPoint(-10 * i, 10 * i));
//                verticesList.append(vertices);
//            }
            textParser(args, verticesList);
            points = cal->getPolygonPoints(verticesList, QPoint(15, 15), method);
            drawPixel(points, painter);
        }

    }
    painter->end();
}


void Widget::drawPixel(QVector<QPoint> pix, QPainter* painter) {
    // paint the pixels on map
    for(int i = 0; i < pix.length(); i++) {
        painter->drawRect(pix[i].x() * 10 - 5, pix[i].y() * 10 - 5, 10, 10);
    }
}

void Widget::textParser(QString rawText, QPoint &start, QPoint&end) {
    rawText.replace("(", "");
    rawText.replace(")", "");
    QStringList list = rawText.split(",");
    start = QPoint(list[0].toInt(), list[1].toInt());
    end = QPoint(list[2].toInt(), list[3].toInt());
}

void Widget::textParser(QString rawText, QPoint &center, int &r) {
    rawText.replace("(", "");
    rawText.replace(")", "");
    QStringList list = rawText.split(",");
    center = QPoint(list[0].toInt(), list[1].toInt());
    r = list[2].toInt();
}

void Widget::textParser(QString rawText, QPoint &center, int &a, int &b) {
    rawText.replace("(", "");
    rawText.replace(")", "");
    QStringList list = rawText.split(",");
    center = QPoint(list[0].toInt(), list[1].toInt());
    a = list[2].toInt();
    b = list[3].toInt();
}
void Widget::textParser(QString rawText, QVector<QVector<QPoint>> &verticesList) {

    for (int i = 1; i <= 2; ++i) {
        QVector<QPoint> vertices = {};
        vertices.append(QPoint(9 * i, 10 * i));
        vertices.append(QPoint(10 * i, -10 * i));
        vertices.append(QPoint(-5 * i, -5 * i));
        vertices.append(QPoint(-10 * i, 10 * i));
        verticesList.append(vertices);
    }
}


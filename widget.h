#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPainter>
#include <QPen>

class Widget : public QWidget {
    Q_OBJECT

  public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *event);
    void drawPixel(QVector<QPoint> pix, QPainter* painter);
  private:
    QVector<QPoint> points;
    QPainter *painter;
};
#endif // WIDGET_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QPainter>
#include <QPen>
#include <QVBoxLayout>
#include <QHBoxLayout>

class Widget : public QWidget {
    Q_OBJECT

  public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *event);
    void drawPixel(QVector<QPoint> pix, QPainter *painter);
    void textParser(QString rawText, QPoint &start, QPoint &end);
    void textParser(QString rawText, QPoint &center, int &r);
    void textParser(QString rawText, QPoint &center, int &a, int &b);
    void textParser(QString rawText, QVector<QVector<QPoint>> &verticesList);
  private:
    QVector<QPoint> points;
    QPainter *painter;
    QHBoxLayout *layout;
    QVBoxLayout *argsLayout;
    QComboBox *shapeSelect;
    QComboBox *methodSelect;
    QTextEdit *argsInput;
    QPushButton *submmit;
};
#endif // WIDGET_H

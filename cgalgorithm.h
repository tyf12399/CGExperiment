#ifndef CGALGORITHM_H
#define CGALGORITHM_H
#include <QPoint>
#include <QVector>
#include <QMessageBox>
class CGAlgorithm {
  public:
    CGAlgorithm();
    QVector<QPoint> getLinePoints(QPoint start, QPoint end, QString method);
  private:
    QVector<QPoint> dda(QPoint start, QPoint end);
    QVector<QPoint> bresenham(QPoint start, QPoint end);
};

#endif // CGALGORITHM_H

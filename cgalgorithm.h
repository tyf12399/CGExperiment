#ifndef CGALGORITHM_H
#define CGALGORITHM_H
#include <QPoint>
#include <QVector>
#include <QMessageBox>
class CGAlgorithm {
  public:
    CGAlgorithm();
    QVector<QPoint> getLinePoints(QPoint start, QPoint end, QString method);
    QVector<QPoint> getCirclePoints(QPoint center, int r, QString method);
    QVector<QPoint> getEllipsePoints(QPoint center, int a, int b);

  private:
    QVector<QPoint> ddaLine(QPoint start, QPoint end);
    QVector<QPoint> bresenhamLine(QPoint start, QPoint end);
    QVector<QPoint> midPointCircle(QPoint center, int r);
    QVector<QPoint> bresenhamCircle(QPoint center, int r);
    QVector<QPoint> midPointEllipse(QPoint center, int a, int b);
    QVector<QPoint> symmetricalOperation(QVector<QPoint> points);
};

#endif // CGALGORITHM_H

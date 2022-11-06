#ifndef CGALGORITHM_H
#define CGALGORITHM_H
#include <QPoint>
#include <QVector>
#include <QStack>

class CGAlgorithm {
  public:
    CGAlgorithm();
    QVector<QPoint> getLinePoints(QPoint start, QPoint end, QString method);
    QVector<QPoint> getCirclePoints(QPoint center, int r, QString method);
    QVector<QPoint> getEllipsePoints(QPoint center, int a, int b);
    QVector<QPoint> getPolygonPoints(QVector<QVector<QPoint>> verticesList, QString method);

  private:
    QVector<QPoint> ddaLine(QPoint start, QPoint end);
    QVector<QPoint> bresenhamLine(QPoint start, QPoint end);
    QVector<QPoint> midPointCircle(QPoint center, int r);
    QVector<QPoint> bresenhamCircle(QPoint center, int r);
    QVector<QPoint> midPointEllipse(QPoint center, int a, int b);
    QVector<QPoint> scanLineFill(QVector<QPoint> edges, QPoint seed);
    void floodFill4(QVector<QPoint> *edges, QPoint seed);
    QVector<QPoint> symmetricalOperation(QVector<QPoint> points);
    QVector<QPoint> edgeCal(QVector<QVector<QPoint>> verticesList);
    QPoint seedInitial(QVector<QPoint> edges);
    bool isInner(QPoint p, QVector<QPoint> edges);
};

#endif // CGALGORITHM_H

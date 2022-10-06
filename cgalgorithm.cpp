#include "cgalgorithm.h"
#include "QDebug"
CGAlgorithm::CGAlgorithm() {
}

QVector<QPoint> CGAlgorithm::getLinePoints(QPoint start, QPoint end, QString method) {
    QVector<QPoint> ans{};
    if (method == "dda") {
        ans = dda(start, end);
    } else if (method == "bresenham") {
        ans =  bresenham(start, end);
    } else {
        ans.append(QPoint(0, 0));
        qDebug() << "wrong input";
    }
    return ans;
}

QVector<QPoint> CGAlgorithm::dda(QPoint start, QPoint end) {
    QVector<QPoint> ans{};
    int x0 = start.x();
    int y0 = start.y();
    int x1 = end.x();
    int y1 = end.y();
    int dx, dy, n, k;
    double xinc, yinc, x, y;
    dx = x1 - x0;
    dy = y1 - y0;
    if (abs(dx) > abs(dy))
        n = abs(dx);
    else
        n = abs(dy);
    xinc = (double)dx / n;
    yinc = (double)dy / n;
    x = (double)x0;
    y = (double)y0;
    for (k = 1; k <= n; k++) {
        ans.append(QPoint(int(x + 0.5), int(y + 0.5)));
        x += xinc;
        y += yinc;
    }
    return ans;
}
QVector<QPoint> CGAlgorithm::bresenham(QPoint start, QPoint end) {

}

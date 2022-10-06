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
    ans.append(QPoint(int(x + 0.5), int(y + 0.5)));
    for (k = 1; k <= n; k++) {
        x += xinc;
        y += yinc;
        ans.append(QPoint(int(x + 0.5), int(y + 0.5)));
    }
    return ans;
}
QVector<QPoint> CGAlgorithm::bresenham(QPoint start, QPoint end) {
    QVector<QPoint> ans{};
    int x0 = start.x();
    int y0 = start.y();
    int x1 = end.x();
    int y1 = end.y();
    int x = x0;
    int y = y0;
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int s0 = x1 > x0 ? 1 : -1;
    int s1 = y1 > y0 ? 1 : -1;
    ans.append(QPoint(x, y));
    bool interchange = false;	// 默认不互换 dx、dy
    if (dy > dx) {			// 当斜率大于 1 时，dx、dy 互换
        int temp = dx;
        dx = dy;
        dy = temp;
        interchange = true;
    }
    int p = 2 * dy - dx;
    for(int i = 0; i < dx; i++) {

        if (p >= 0) {
            if (!interchange)		// 当斜率 < 1 时，选取上下象素点
                y += s1;
            else					// 当斜率 > 1 时，选取左右象素点
                x += s0;
            p -= 2 * dx;
        }
        if (!interchange)
            x += s0;				// 当斜率 < 1 时，选取 x 为步长
        else
            y += s1;				// 当斜率 > 1 时，选取 y 为步长
        p += 2 * dy;
        ans.append(QPoint(x, y));
    }
    return ans;
}

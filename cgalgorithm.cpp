#include "cgalgorithm.h"
#include "QDebug"
CGAlgorithm::CGAlgorithm() {
}

QVector<QPoint> CGAlgorithm::getLinePoints(QPoint start, QPoint end, QString method) {
    QVector<QPoint> ans{};
    if (method == "dda") {
        ans = ddaLine(start, end);
    } else if (method == "bresenham") {
        ans =  bresenhamLine(start, end);
    } else {
        ans.append(QPoint(0, 0));
        qDebug() << "wrong input";
    }
    return ans;
}

QVector<QPoint> CGAlgorithm::ddaLine(QPoint start, QPoint end) {
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
QVector<QPoint> CGAlgorithm::bresenhamLine(QPoint start, QPoint end) {
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
    bool interchange = false;
    if (dy > dx) {
        int temp = dx;
        dx = dy;
        dy = temp;
        interchange = true;
    }
    int p = 2 * dy - dx;
    for(int i = 0; i < dx; i++) {

        if (p >= 0) {
            if (!interchange)
                y += s1;
            else
                x += s0;
            p -= 2 * dx;
        }
        if (!interchange)
            x += s0;
        else
            y += s1;
        p += 2 * dy;
        ans.append(QPoint(x, y));
    }
    return ans;
}

QVector<QPoint> CGAlgorithm::getCirclePoints(QPoint center, int r, QString method) {
    QVector<QPoint> ans{};
    if (method == "mid-point") {
        ans = midPointCircle(center, r);
    } else if (method == "bresenham") {
        ans =  bresenhamCircle(center, r);
    } else {
        ans.append(QPoint(0, 0));
        qDebug() << "wrong input";
    }
    return ans;
}

QVector<QPoint> CGAlgorithm::midPointCircle(QPoint center, int r) {
    QVector<QPoint> ans{};
    int x = r;
    int y = 0;
    int err = 0;
    while (x >= y) {
        ans.append(QPoint(x, y));
        ans.append(QPoint(x, -y));
        ans.append(QPoint(-x, y));
        ans.append(QPoint(-x, -y));
        ans.append(QPoint(y, x));
        ans.append(QPoint(y, -x));
        ans.append(QPoint(-y, x));
        ans.append(QPoint(-y, -x));

        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }

        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }

    for(int i = 0; i < ans.length(); i++) {
        ans[i] += center;
    }
    return ans;
}

QVector<QPoint> CGAlgorithm::bresenhamCircle(QPoint center, int r) {
    QVector<QPoint> ans{};
    return ans;
}

QVector<QPoint> CGAlgorithm::midPointEllipse(QPoint center, int a, int b) {
    QVector<QPoint> ans{};
    return ans;
}

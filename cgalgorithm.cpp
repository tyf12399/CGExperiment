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
    int x = 0;
    int y = r;
    int d = 1.25 - r;
    while (x <= y) {
        ans.append(QPoint(x, y));
        ans.append(QPoint(y, x));

        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y -= 1;
        }
        x += 1;
    }
    ans = symmetricalOperation(ans);
    for(int i = 0; i < ans.length(); i++) {
        ans[i] += center;
    }

    return ans;
}

QVector<QPoint> CGAlgorithm::bresenhamCircle(QPoint center, int r) {
    QVector<QPoint> ans{};
    int x = 0;
    int y = r;
    int delta = 2 * (1 - r);
    int delta1, delta2, direction;
    while(y >= 0) {
        ans.append(QPoint(x, y));
        if(delta < 0) {
            delta1 = 2 * (delta + y) - 1;
            if(delta1 <= 0) {
                direction = 1;
            } else {
                direction = 2;
            }
        } else if (delta > 0) {
            delta2 = 2 * (delta - x) - 1;
            if(delta2 < 0) {
                direction = 2;
            } else {
                direction = 3;
            }
        } else {
            direction = 2;
        }

        if(direction == 1) {
            x++;
            delta += 2 * x + 1;
        } else if(direction == 2) {
            x++;
            y--;
            delta += 2 * (x - y + 1);
        } else if(direction == 3) {
            y--;
            delta += (-2 * y + 1);
        }
    }

    ans = symmetricalOperation(ans);
    for(int i = 0; i < ans.length(); i++) {
        ans[i] += center;
    }
    return ans;
}

QVector<QPoint> CGAlgorithm::getEllipsePoints(QPoint center, int a, int b) {
    QVector<QPoint> ans{};
    ans = midPointEllipse(center, a, b);
    return ans;
}

QVector<QPoint> CGAlgorithm::midPointEllipse(QPoint center, int a, int b) {
    QVector<QPoint> ans{};
    int  x, y;
    float  p1, p2;
    x = 0;
    y = b;
    p1 = b * b - a * a * b + 0.25 * a * a;
    ans.append(QPoint(x, y));
    while (a * a * y > b * b * x) {                //第一象限内靠近y轴内点的绘制
        if (p1 < 0) {
            p1 = p1 + 2 * b * b * (x + 1) + b * b;
            x = x + 1;
            y = y;
        } else {
            p1 = p1 + 2 * b * b * (x + 1) + b * b - 2 * a * a * (y - 1);
            x = x + 1;
            y = y - 1;
        }
        ans.append(QPoint(x, y));
    }
    p2 = 1.0 * b * b * (x + 0.5) * (x + 0.5) + 1.0 * a * a * (y - 1) * (y - 1) - 1.0 * a * a * b * b;
    while (y > 0) {                                                //第一象限另外一区域
        if (p2 > 0) {
            p2 = p2 - 2 * a * a * (y - 1) + a * a;
            y = y - 1;
            x = x;
        } else {
            p2 = p2 - 2 * a * a * (y - 1) + a * a + 2 * b * b * (x + 1);
            y = y - 1;
            x = x + 1;
        }
        ans.append(QPoint(x, y));
    }

    ans = symmetricalOperation(ans);
    for(int i = 0; i < ans.length(); i++) {
        ans[i] += center;
    }
    return ans;
}

QVector<QPoint> CGAlgorithm::symmetricalOperation(QVector<QPoint> points) {
    QVector<QPoint> full{};
    for(int i = 0; i < points.length(); i++) {
        int x = points[i].rx();
        int y = points[i].ry();
        full.append(QPoint(x, y));
        full.append(QPoint(x, -y));
        full.append(QPoint(-x, y));
        full.append(QPoint(-x, -y));
    }
    return full;
}

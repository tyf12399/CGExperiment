#include "cgalgorithm.h"
#include "QDebug"
CGAlgorithm::CGAlgorithm() {
}

QVector<QPoint> CGAlgorithm::getLinePoints(QPoint start, QPoint end, QString method) {
    // choose the algorithm to calculate the pixels position
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
    // use dda to draw a line
    QVector<QPoint> ans{};
    int x0 = start.x();
    int y0 = start.y();
    int x1 = end.x();
    int y1 = end.y();
    int dx, dy, n, k;
    double xstep, ystep, x, y;
    dx = x1 - x0;
    dy = y1 - y0;
    //use slope to decide direction
    if (abs(dx) > abs(dy))
        n = abs(dx);
    else
        n = abs(dy);
    // calculate the step length
    ystep = (double)dy / n;
    xstep = (double)dx / n;
    x = (double)x0;
    y = (double)y0;

    for (k = 0; k <= n; k++) {
        ans.append(QPoint(qRound(x), qRound(y)));
        x += xstep;
        y += ystep;
    }
    return ans;
}

QVector<QPoint> CGAlgorithm::bresenhamLine(QPoint start, QPoint end) {
    // use bresenham to draw a line
    QVector<QPoint> ans{};
    int x0 = start.x();
    int y0 = start.y();
    int x1 = end.x();
    int y1 = end.y();
    int x = x0;
    int y = y0;
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int stepx = x1 > x0 ? 1 : -1;
    int stepy = y1 > y0 ? 1 : -1;
    bool exchanged = false;
    // choose the direction by slope
    if (dy > dx) {
        int temp = dx;
        dx = dy;
        dy = temp;
        exchanged = true;
    }
    int d = 2 * dy - dx;
    for(int i = 0; i <= dx; i++) {
        ans.append(QPoint(x, y));
        if (d >= 0) {
            if (!exchanged)
                y += stepy;
            else
                x += stepx;
            d -= 2 * dx;
        }
        if (!exchanged) {
            x += stepx;
        } else {
            y += stepy;
        }
        d += 2 * dy;
    }
    return ans;
}

QVector<QPoint> CGAlgorithm::getCirclePoints(QPoint center, int r, QString method) {
    // choose the algorithm to calculate the pixels position
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
    // use mid-point to draw a circle
    QVector<QPoint> ans{};
    int x = 0;
    int y = r;
    int d = 1.25 - r;

    while (x <= y) {
        ans.append(QPoint(x, y));
        ans.append(QPoint(y, x));

        if (d < 0) {
            // update d
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y -= 1;
        }
        x += 1;
    }

    ans = symmetricalOperation(ans);
    // translation
    for(int i = 0; i < ans.length(); i++) {
        ans[i] += center;
    }

    return ans;
}

QVector<QPoint> CGAlgorithm::bresenhamCircle(QPoint center, int r) {
    // use bresenham to draw a circle
    QVector<QPoint> ans{};
    int x = 0;
    int y = r;
    // delta Di
    int delta = 2 * (1 - r);
    int delta1, delta2, direction;
    while(y >= 0) {
        ans.append(QPoint(x, y));
        if(delta < 0) {
            // delta HD
            delta1 = 2 * (delta + y) - 1;
            if(delta1 < 0) {
                // choose H
                direction = 1;
            } else {
                // choose D
                direction = 2;
            }
        } else if (delta > 0) {
            // delta DV
            delta2 = 2 * (delta - x) - 1;
            if(delta2 < 0) {
                // choose D
                direction = 2;
            } else {
                // choose V
                direction = 3;
            }
        } else {
            // choose D
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
    // translation
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
    // use mid-point to draw a line
    QVector<QPoint> ans{};
    int  x, y;
    float  d1, d2;
    x = 0;
    y = b;
    ans.append(QPoint(x, y));

    // region 2
    d1 = b * b - a * a * b + 0.25 * a * a;
    while (a * a * y > b * b * x) {
        if (d1 < 0) {
            d1 = d1 + 2 * b * b * (x + 1) + b * b;
            x = x + 1;
        } else {
            d1 = d1 + 2 * b * b * (x + 1) + b * b - 2 * a * a * (y - 1);
            x = x + 1;
            y = y - 1;
        }
        ans.append(QPoint(x, y));
    }

    // region 1
    d2 = 1.0 * b * b * (x + 0.5) * (x + 0.5) + 1.0 * a * a * (y - 1) * (y - 1) - 1.0 * a * a * b * b;
    while (y > 0) {
        if (d2 > 0) {
            d2 = d2 - 2 * a * a * (y - 1) + a * a;
            y = y - 1;
            x = x;
        } else {
            d2 = d2 - 2 * a * a * (y - 1) + a * a + 2 * b * b * (x + 1);
            y = y - 1;
            x = x + 1;
        }
        ans.append(QPoint(x, y));
    }

    ans = symmetricalOperation(ans);
    // translation
    for(int i = 0; i < ans.length(); i++) {
        ans[i] += center;
    }
    return ans;
}

QVector<QPoint> CGAlgorithm::getPolygonPoints(QVector<QVector<QPoint>> verticesList, QPoint seed, QString method) {
    QVector<QPoint> innerPoints = {};
    QVector<QPoint> edges = edgeCal(verticesList);
    if(method == "scanline") {
        innerPoints = scanLineFill(edges, seed);
    } else if(method == "flood") {
        floodFill4(&edges, seed);
        return edges;
    }
    return innerPoints;
}

QVector<QPoint> CGAlgorithm::edgeCal(QVector<QVector<QPoint>> verticesList) {
    QVector<QPoint> edge = {};
    for(int i = 0; i < verticesList.length(); i++) {
        QVector<QPoint> vertices = verticesList[i];
        int len = vertices.length();
        for (int j = 1; j < len; j++) {
            edge.append(bresenhamLine(vertices[j - 1], vertices[j]));
        }
        edge.append(bresenhamLine(vertices[len - 1], vertices[0]));
    }
    return edge;
}

QVector<QPoint> CGAlgorithm::scanLineFill(QVector<QPoint> edges, QPoint seed) {
    QVector<QPoint> innerPoints = {};
    return innerPoints;
}

void CGAlgorithm::floodFill4(QVector<QPoint> *edges, QPoint seed) {
    if(!edges->contains(seed)) {
        edges->append(seed);
        floodFill4(edges, QPoint(seed.rx() + 1, seed.ry()));
        floodFill4(edges, QPoint(seed.rx() - 1, seed.ry()));
        floodFill4(edges, QPoint(seed.rx(), seed.ry() + 1));
        floodFill4(edges, QPoint(seed.rx(), seed.ry() - 1));
    }
}

QVector<QPoint> CGAlgorithm::symmetricalOperation(QVector<QPoint> points) {
    // four-way symmtrical operation
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

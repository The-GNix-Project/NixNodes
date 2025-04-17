#include "ConnectionItem.hpp"

ConnectionItem::ConnectionItem(NodeItem* src, NodeItem* dst) {
    setZValue(-1);
    setPen(QPen(Qt::black, 2));
    updatePath(src, dst);
}

void ConnectionItem::updatePath(NodeItem* src, NodeItem* dst) {
    QPointF p1 = src->outputPort();
    QPointF p2 = dst->inputPort();

    QPainterPath path(p1);
    QPointF ctrl1 = p1 + QPointF(50, 0);
    QPointF ctrl2 = p2 - QPointF(50, 0);
    path.cubicTo(ctrl1, ctrl2, p2);
    setPath(path);
}
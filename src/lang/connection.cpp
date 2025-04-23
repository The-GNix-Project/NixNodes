#include "lang/connection.hpp"
#include <QPainter>
#include <QDebug>

Connection::Connection(Output* source, Input* target, QGraphicsItem* parent)
    :  QGraphicsPathItem(parent),
        m_source(source), m_target(target),
        m_tempEnd(source->scenePos() + QPointF(10,5)) {
    qDebug() << "Connection constructed" << scenePos();
    if (m_source) {
        qDebug() << "Source:" << m_source->scenePos();
    }
    if (m_target) {
        qDebug() << "Target:" << m_target->scenePos();
    } 
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setZValue(1);
    updatePath();
}

void Connection::updatePath() {
    QPainterPath path;
    if (m_source && m_target) {
        // Draw curved path between source and target
        QPointF start = m_source->scenePos() + QPointF(10, 5);
        QPointF end = m_target->scenePos() + QPointF(0, 5);
        QPointF ctrl1 = start + QPointF(50, 0);
        QPointF ctrl2 = end - QPointF(50, 0);
        path.cubicTo(ctrl1, ctrl2, end);
    } else if (m_source) {
        // Draw straight line during drag
        QPointF start = m_source->scenePos() + QPointF(10, 5);
        path.moveTo(start);
        path.lineTo(m_tempEnd);
    }
    setPath(path);
}

void Connection::updateTempEnd(const QPointF& tempEnd) {
    m_tempEnd = tempEnd;
    updatePath();
}
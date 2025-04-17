#include "NodeItem.hpp"

NodeItem::NodeItem(const QString& title, QGraphicsItem* parent)
    : QGraphicsObject(parent)
    , m_title(title)
{
    setFlags(ItemIsMovable | ItemIsSelectable);
}

QRectF NodeItem::boundingRect() const {
    return { 0, 0, 120, 60 };
}

void NodeItem::paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget*) {
    // body
    p->setBrush(isSelected() ? Qt::lightGray : Qt::white);
    p->setPen(Qt::black);
    p->drawRect(boundingRect());

    // title bar
    QRectF titleRect(0, 0, 120, 20);
    p->setBrush(Qt::darkGray);
    p->drawRect(titleRect);

    p->setPen(Qt::white);
    p->drawText(titleRect, Qt::AlignCenter, m_title);
}

QPointF NodeItem::outputPort() const {
    return mapToScene(boundingRect().topRight()  + QPointF(0, boundingRect().height()/2));
}

QPointF NodeItem::inputPort() const {
    return mapToScene(boundingRect().topLeft()   + QPointF(0, boundingRect().height()/2));
}
#include "Port.hpp"

Port::Port(QGraphicsItem* parent, PortType type) : QGraphicsEllipseItem(-6, -6, 12, 12, parent), m_type(type)
{
    setBrush(Qt::white);
    setPen(Qt::NoPen);
    setFlag(ItemSendsScenePositionChanges);
    setAcceptHoverEvents(true);
}

void Port::add_connection(QGraphicsPathItem* connection) {
    m_connections.append(connection);
    update_connections();
}

QVariant Port::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemScenePositionHasChanged) update_connections();
    return QGraphicsEllipseItem::itemChange(change, value);
}

void Port::update_connections() {
    for (auto* connection : m_connections) {
        auto* start = connection->data(0).value<Port*>();
        auto* end   = connection->data(1).value<Port*>();
        QPainterPath path;
        path.moveTo(start->scenePos());
        path.cubicTo(start->scenePos()+QPointF(50,0),
                        end->scenePos()+QPointF(-50,0),
                        end->scenePos());
        connection->setPath(path);
    }
}
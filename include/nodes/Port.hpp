#pragma once

#include <QGraphicsView>
#include <QGraphicsPathItem>
#include <QPainterPath>


class Port : public QGraphicsEllipseItem {
public:
    enum PortType { Input, Output };
    Port(QGraphicsItem* parent, PortType type);
    PortType port_type() const { return m_type; }
    void add_connection(QGraphicsPathItem* connection);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void update_connections();

private:
    PortType m_type;
    QList<QGraphicsPathItem*> m_connections;
};
 
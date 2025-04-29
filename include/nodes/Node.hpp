#pragma once

#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>

#include "Port.hpp"

class Node : public QGraphicsRectItem {
public:
    Node(const QString& title);
    Port* add_port(Port::PortType type);
    void set_body_enabled(bool on);
    void set_body_text(const QString& txt);

protected:
    void paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget*) override;

private:
    QString m_title;
    QList<Port*> m_inputs, m_outputs;
    QGraphicsTextItem* m_bodyItem;
    bool m_bodyEnabled = false;
    const qreal m_titleH = 30;
    const qreal m_margin = 12;
    const qreal m_portSpacing = 24;
    const qreal m_portYOffset = 10; // move ports down slightly
    const qreal m_defaultWidth = 100;
    const qreal m_bodyWidthExtra = 100; // extra width when body enabled

    void update_layout();
};
 
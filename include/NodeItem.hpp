#ifndef NODEITEM_H
#define NODEITEM_H

#pragma once

#include <QtWidgets>

// A simple movable/selectable node with a title bar
class NodeItem : public QGraphicsObject {
    Q_OBJECT
public:
    explicit NodeItem(const QString& title, QGraphicsItem* parent = nullptr);

    // QGraphicsItem interface
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    // Port positions in scene coords
    QPointF outputPort() const;
    QPointF inputPort()  const;

private:
    QString m_title;  // store title text
};

#endif
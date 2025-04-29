#pragma once

#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>

#include "Node.hpp"
#include "Port.hpp"

class Canvas : public QGraphicsScene {
public:
    Canvas(QObject* parent = nullptr) : QGraphicsScene(parent) {}

protected:
    void drawBackground(QPainter* painter, const QRectF& rect) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QGraphicsPathItem* m_currentConnection=nullptr;
    void update_bezier_path(const QPointF& endPos);
};

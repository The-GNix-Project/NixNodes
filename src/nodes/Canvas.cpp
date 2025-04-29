#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>

#include "Canvas.hpp"
#include "Node.hpp"
#include "Port.hpp"

void Canvas::drawBackground(QPainter* painter, const QRectF& rect) {
    const qreal gridSize = 50;
    QRectF b = rect;
    qreal left   = std::floor(b.left()/gridSize)*gridSize;
    qreal right  = std::ceil(b.right()/gridSize)*gridSize;
    qreal top    = std::floor(b.top()/gridSize)*gridSize;
    qreal bottom = std::ceil(b.bottom()/gridSize)*gridSize;

    QColor lightLine(70,70,70, 60);
    QColor heavyLine(100,100,100,100);
    for (qreal x = left; x <= right; x += gridSize) {
        bool heavy = (std::fmod(x, gridSize*5)==0);
        painter->setPen(heavy?heavyLine:lightLine);
        painter->drawLine(QPointF(x, top), QPointF(x, bottom));
    }
    for (qreal y = top; y <= bottom; y += gridSize) {
        bool heavy = (std::fmod(y, gridSize*5)==0);
        painter->setPen(heavy?heavyLine:lightLine);
        painter->drawLine(QPointF(left, y), QPointF(right, y));
    }
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QList<QGraphicsItem*> items = this->items(event->scenePos());
    Port* port = nullptr;
    for (auto* it : items) if ((port = dynamic_cast<Port*>(it))) break;
    if (port && port->port_type()==Port::Output) {
        m_currentConnection=new QGraphicsPathItem();
        m_currentConnection->setPen(QPen(QColor(200,200,200),2));
        m_currentConnection->setData(0,QVariant::fromValue(port));
        addItem(m_currentConnection);
        update_bezier_path(event->scenePos()); event->accept(); return;
    }
    QGraphicsScene::mousePressEvent(event);
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (m_currentConnection) { update_bezier_path(event->scenePos()); event->accept(); return; }
    QGraphicsScene::mouseMoveEvent(event);
}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if (m_currentConnection) {
        auto* startPort=m_currentConnection->data(0).value<Port*>();
        QList<QGraphicsItem*> items=this->items(event->scenePos());
        Port* endPort=nullptr;
        for(auto* it:items)
            if((endPort=dynamic_cast<Port*>(it))) {
                if(endPort!=startPort && endPort->port_type()==Port::Input) break;
                endPort=nullptr;
            }
        if(endPort) {
            m_currentConnection->setData(1,QVariant::fromValue(endPort));
            QPainterPath path;
            path.moveTo(startPort->scenePos());
            path.cubicTo(startPort->scenePos()+QPointF(50,0),endPort->scenePos()+QPointF(-50,0),endPort->scenePos());
            m_currentConnection->setPath(path);
            startPort->add_connection(m_currentConnection);
            endPort->add_connection(m_currentConnection);
        } else { removeItem(m_currentConnection); delete m_currentConnection; }
        m_currentConnection=nullptr; event->accept(); return;
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

void Canvas::update_bezier_path(const QPointF& endPos) {
    if(!m_currentConnection) return;
    auto* startPort=m_currentConnection->data(0).value<Port*>();
    QPainterPath path;
    path.moveTo(startPort->scenePos());
    path.cubicTo(startPort->scenePos()+QPointF(50,0),endPos+QPointF(-50,0),endPos);
    m_currentConnection->setPath(path);
}
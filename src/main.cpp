// SPDX-License-Identifier: GPL-3.0-or-later
//
// This file is part of GNix: NixNodes
// GNix - The Graphical Nix Project
// -----------------------------------------------------------------------------------------|
// GNix is free software: you can redistribute it and/or modify                             |
// it under the terms of the GNU General Public License as published by                     |
// the Free Software Foundation, either version 3 of the License, or any later version.     |
//                                                                                          |
// GNix is distributed in the hope that it will be useful,                                  |
// but WITHOUT ANY WARRANTY; without even the implied warranty of                           |
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                            |
// GNU General Public License for more details.                                             |
//                                                                                          |
// You should have received a copy of the GNU General Public License                        |
// along with GNix.  If not, see <https://www.gnu.org/licenses/>.                           |
// -----------------------------------------------------------------------------------------|
#include <string>
#include <cmath>

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>

namespace nixnodes {

class Port : public QGraphicsEllipseItem {
public:
    enum PortType { Input, Output };
    Port(QGraphicsItem* parent, PortType type)
      : QGraphicsEllipseItem(-6, -6, 12, 12, parent), m_type(type)
    {
        setBrush(Qt::white);
        setPen(Qt::NoPen);
        setFlag(ItemSendsScenePositionChanges);
        setAcceptHoverEvents(true);
    }
    PortType portType() const { return m_type; }
    void addConnection(QGraphicsPathItem* connection) {
        m_connections.append(connection);
        updateConnections();
    }
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override {
        if (change == ItemScenePositionHasChanged) updateConnections();
        return QGraphicsEllipseItem::itemChange(change, value);
    }
    void updateConnections() {
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
private:
    PortType m_type;
    QList<QGraphicsPathItem*> m_connections;
};

class Node : public QGraphicsRectItem {
public:
    Node(const QString& title)
      : m_title(title)
    {
        setFlag(ItemIsMovable);
        setPen(Qt::NoPen);
        m_bodyItem = new QGraphicsTextItem(this);
        m_bodyItem->setDefaultTextColor(Qt::black);
        m_bodyItem->setTextInteractionFlags(Qt::TextEditorInteraction);
        updateLayout();
    }

    Port* addPort(Port::PortType type) {
        Port* p = new Port(this, type);
        if (type == Port::Input)  m_inputs.append(p);
        else                       m_outputs.append(p);
        updateLayout();
        return p;
    }
    void setBodyEnabled(bool on) {
        m_bodyEnabled = on;
        m_bodyItem->setVisible(on);
        updateLayout();
    }
    void setBodyText(const QString& txt) {
        m_bodyItem->setPlainText(txt);
        updateLayout();
    }
protected:
    void paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget*) override {
        QRectF r = rect();
        p->setRenderHint(QPainter::Antialiasing);
        // background
        p->setPen(Qt::NoPen);
        p->setBrush(QColor(60,60,60));
        p->drawRoundedRect(r,8,8);

        // title
        qreal th = m_titleH;
        QRectF tr(r.left(), r.top(), r.width(), th);
        QLinearGradient grad(tr.topLeft(), tr.bottomLeft());
        grad.setColorAt(0, QColor(80,80,80));
        grad.setColorAt(1, QColor(60,60,60));
        p->setBrush(grad);
        p->drawRoundedRect(tr,8,8);
        p->setPen(Qt::white);
        QFont f = p->font(); f.setBold(true); f.setPointSizeF(11);
        p->setFont(f);
        QRectF textRect = p->fontMetrics().boundingRect(m_title);
        p->drawText(r.left() + (r.width()-textRect.width())/2,
                    r.top() + (th+textRect.height())/2,
                    m_title);

        // draw body background
        if (m_bodyEnabled) {
            QRectF bodyBg(m_bodyItem->pos(), QSizeF(m_bodyItem->textWidth(), m_bodyItem->boundingRect().height()));
            bodyBg.adjust(-2, -2, 2, 2); // slight padding
            p->setBrush(Qt::white);
            p->setPen(Qt::NoPen);
            p->drawRoundedRect(bodyBg, 4, 4);
        }
    }
    
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

    void updateLayout() {
        // determine width
        qreal w = m_defaultWidth + (m_bodyEnabled ? m_bodyWidthExtra : 0);
        // body text size
        qreal textH = 0;
        if (m_bodyEnabled) {
            m_bodyItem->setTextWidth(w - 2*m_margin);
            textH = m_bodyItem->boundingRect().height();
        }
        // ports count
        int nmax = qMax(m_inputs.size(), m_outputs.size());
        qreal portsH = (nmax>0 ? (nmax-1)*m_portSpacing : 0);
        // total height
        qreal h = m_titleH + m_margin + m_portYOffset + portsH + m_margin + textH + m_margin;
        setRect(-w/2, -m_titleH, w, h);
        QRectF r = rect();
        // position body at same Y-level as first port
        if (m_bodyEnabled) {
            qreal bodyY = r.top() + m_titleH + m_margin + m_portYOffset;    
            m_bodyItem->setPos(r.left()+m_margin, bodyY);
        }
        // layout ports
        auto layout = [&](const QList<Port*>& ports, qreal x) {
            int n = ports.size();
            qreal span = (n>0 ? (n-1)*m_portSpacing : 0);
            qreal baseY = r.top() + m_titleH + m_margin + m_portYOffset + span/2;
            for (int i=0;i<n;++i)
                ports[i]->setPos(x, baseY - i*m_portSpacing);
        };
        layout(m_inputs,  r.left());
        layout(m_outputs, r.right());
    }
};

class GraphicsScene : public QGraphicsScene {
public:
    GraphicsScene(QObject* parent = nullptr) : QGraphicsScene(parent) {}

protected:
    void drawBackground(QPainter* painter, const QRectF& rect) override {
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

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        QList<QGraphicsItem*> items = this->items(event->scenePos());
        Port* port = nullptr;
        for (auto* it : items) if ((port = dynamic_cast<Port*>(it))) break;
        if (port && port->portType()==Port::Output) {
            m_currentConnection=new QGraphicsPathItem();
            m_currentConnection->setPen(QPen(QColor(200,200,200),2));
            m_currentConnection->setData(0,QVariant::fromValue(port));
            addItem(m_currentConnection);
            updateBezierPath(event->scenePos()); event->accept(); return;
        }
        QGraphicsScene::mousePressEvent(event);
    }
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override {
        if (m_currentConnection) { updateBezierPath(event->scenePos()); event->accept(); return; }
        QGraphicsScene::mouseMoveEvent(event);
    }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override {
        if (m_currentConnection) {
            auto* startPort=m_currentConnection->data(0).value<Port*>();
            QList<QGraphicsItem*> items=this->items(event->scenePos());
            Port* endPort=nullptr;
            for(auto* it:items)
                if((endPort=dynamic_cast<Port*>(it))) {
                    if(endPort!=startPort && endPort->portType()==Port::Input) break;
                    endPort=nullptr;
                }
            if(endPort) {
                m_currentConnection->setData(1,QVariant::fromValue(endPort));
                QPainterPath path;
                path.moveTo(startPort->scenePos());
                path.cubicTo(startPort->scenePos()+QPointF(50,0),endPort->scenePos()+QPointF(-50,0),endPort->scenePos());
                m_currentConnection->setPath(path);
                startPort->addConnection(m_currentConnection);
                endPort->addConnection(m_currentConnection);
            } else { removeItem(m_currentConnection); delete m_currentConnection; }
            m_currentConnection=nullptr; event->accept(); return;
        }
        QGraphicsScene::mouseReleaseEvent(event);
    }
private:
    QGraphicsPathItem* m_currentConnection=nullptr;
    void updateBezierPath(const QPointF& endPos) {
        if(!m_currentConnection) return;
        auto* startPort=m_currentConnection->data(0).value<Port*>();
        QPainterPath path;
        path.moveTo(startPort->scenePos());
        path.cubicTo(startPort->scenePos()+QPointF(50,0),endPos+QPointF(-50,0),endPos);
        m_currentConnection->setPath(path);
    }
};

} // namespace nixnodes

int main(int argc, char *argv[]) {
    using namespace nixnodes;
    QApplication a(argc, argv);

    GraphicsScene scene;
    scene.setSceneRect(-400, -300, 800, 600);
    scene.setBackgroundBrush(Qt::black);

    Node* node1 = new Node("Integer");
    node1->setPos(-200, 0);
    node1->setBodyEnabled(true);
    node1->setBodyText("7");
    scene.addItem(node1);
    node1->addPort(Port::Output);

    Node* node2 = new Node("Integer");
    node2->setPos(-200, 100);
    node2->setBodyEnabled(true);
    node2->setBodyText("5");
    scene.addItem(node2);
    node2->addPort(Port::Output);

    Node* node3 = new Node("Sum");
    node3->setPos(200, 0);
    scene.addItem(node3);
    node3->addPort(Port::Input);
    node3->addPort(Port::Input);
    node3->addPort(Port::Input);
    node3->addPort(Port::Output);

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setRenderHint(QPainter::SmoothPixmapTransform);
    view.resize(800, 600);
    view.show();

    return a.exec();
}

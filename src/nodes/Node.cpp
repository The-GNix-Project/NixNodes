#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>

#include "Port.hpp"
#include "Node.hpp"

Node::Node(const QString& title)
    : m_title(title)
{
    setFlag(ItemIsMovable);
    setPen(Qt::NoPen);
    m_bodyItem = new QGraphicsTextItem(this);
    m_bodyItem->setDefaultTextColor(Qt::black);
    m_bodyItem->setTextInteractionFlags(Qt::TextEditorInteraction);
    update_layout();
}

Port* Node::add_port(Port::PortType type) 
{
    Port* p = new Port(this, type);
    if (type == Port::Input)  m_inputs.append(p);
    else                       m_outputs.append(p);
    update_layout();
    return p;
}

void Node::set_body_enabled(bool on) {
    m_bodyEnabled = on;
    m_bodyItem->setVisible(on);
    update_layout();
}

void Node::set_body_text(const QString& txt) {
    m_bodyItem->setPlainText(txt);
    update_layout();
}

void Node::paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget*) {
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

void Node::update_layout() {
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
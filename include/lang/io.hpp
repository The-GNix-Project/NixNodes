#ifndef IO_HPP
#define IO_HPP

#include <string>

#include <QString>
#include <QRegularExpression>
#include <QtWidgets>

#include "lang/node.hpp"

class Node;

class IO: public QGraphicsObject {
    Q_OBJECT
public:
    template<typename T>
    IO(T init_name): QGraphicsObject() {
        setFlags(ItemIsSelectable | ItemIsFocusable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        setAcceptHoverEvents(true);
        change_name(init_name);
        setZValue(1); 
    }

    Node* parentNode() const { 
        return qgraphicsitem_cast<Node*>(parentItem()); 
    }

    bool change_name(const QString& new_name);
    bool change_name(const std::string& new_name);
    bool change_name(const char* new_name);

    QString get_name();
    std::string format_name();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    QPainterPath shape() const override;

signals:
    void dragStarted(QPointF pos);
    void dragUpdated(QPointF pos);
    void dragEnded(QPointF pos);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    QString name;
};

class Input: public IO {    
    Q_OBJECT
public:
    template<typename T>
    Input(T init_name): IO(init_name) {
        setFlags(ItemIsSelectable | ItemIsFocusable);
        setAcceptHoverEvents(true);
        change_name(init_name);
    }
};

class Output: public IO {    
    Q_OBJECT
public:
    template<typename T>
    Output(T init_name): IO(init_name) {
        setFlags(ItemIsSelectable | ItemIsFocusable);
        setAcceptHoverEvents(true);
        change_name(init_name);
    }
};

#endif
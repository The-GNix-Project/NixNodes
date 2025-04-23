#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <QGraphicsView>
#include "lang/node.hpp"
#include "lang/connection.hpp"

class Connection;

class Graph: public QGraphicsScene {
    Q_OBJECT
public:
    Graph(QObject *parent = (QObject *)nullptr): QGraphicsScene(parent) {setBackgroundBrush(QColor("#2e3440"));}; 
    void addNode(Node* node);
    void onOutputDragUpdate(QPointF pos);
    void onOutputDragEnd(QPointF pos);
public slots:
    void onOutputDragStart(QPointF pos);
private:
    Output* pendingSource = nullptr;
    Connection* tempConnection = nullptr; 
};

#endif
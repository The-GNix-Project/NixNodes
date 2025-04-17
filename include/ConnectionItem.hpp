#ifndef CONNECTIONITEM_H
#define CONNECTIONITEM_H

#pragma once

#include <QtWidgets>
#include "NodeItem.hpp"

// A bezier curve connecting two NodeItems
class ConnectionItem : public QGraphicsPathItem {
public:
    ConnectionItem(NodeItem* src, NodeItem* dst);
    void updatePath(NodeItem* src, NodeItem* dst);
};

#endif
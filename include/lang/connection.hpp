#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <QGraphicsPathItem>
#include "lang/io.hpp"

class Connection : public QGraphicsPathItem {
public:
    enum { Type = UserType + 1 };
    Connection(Output* source, Input* target, QGraphicsItem* parent = nullptr);
    
    int type() const override { return Type; }
    Output* source() const { return m_source; }
    Input* target() const { return m_target; }
    void updatePath();
    void updateTempEnd(const QPointF& tempEnd);

private:
    Output* m_source;
    Input* m_target;
    QPointF m_tempEnd;
    bool m_isDragging = false;
};

#endif
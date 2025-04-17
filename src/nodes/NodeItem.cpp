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

#include "NodeItem.hpp"

NodeItem::NodeItem(const QString& title, QGraphicsItem* parent)
    : QGraphicsObject(parent)
    , m_title(title)
{
    setFlags(ItemIsMovable | ItemIsSelectable);
}

QRectF NodeItem::boundingRect() const {
    return { 0, 0, 120, 60 };
}

void NodeItem::paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget*) {
    // body
    p->setBrush(isSelected() ? Qt::lightGray : Qt::white);
    p->setPen(Qt::black);
    p->drawRect(boundingRect());

    // title bar
    QRectF titleRect(0, 0, 120, 20);
    p->setBrush(Qt::darkGray);
    p->drawRect(titleRect);

    p->setPen(Qt::white);
    p->drawText(titleRect, Qt::AlignCenter, m_title);
}

QPointF NodeItem::outputPort() const {
    return mapToScene(boundingRect().topRight()  + QPointF(0, boundingRect().height()/2));
}

QPointF NodeItem::inputPort() const {
    return mapToScene(boundingRect().topLeft()   + QPointF(0, boundingRect().height()/2));
}
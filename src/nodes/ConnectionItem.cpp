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

#include "ConnectionItem.hpp"

ConnectionItem::ConnectionItem(NodeItem* src, NodeItem* dst) {
    setZValue(-1);
    setPen(QPen(Qt::black, 2));
    updatePath(src, dst);
}

void ConnectionItem::updatePath(NodeItem* src, NodeItem* dst) {
    QPointF p1 = src->outputPort();
    QPointF p2 = dst->inputPort();

    QPainterPath path(p1);
    QPointF ctrl1 = p1 + QPointF(50, 0);
    QPointF ctrl2 = p2 - QPointF(50, 0);
    path.cubicTo(ctrl1, ctrl2, p2);
    setPath(path);
}
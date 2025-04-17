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

#include <QApplication>
#include <QGraphicsView>
#include "NodeItem.hpp"
#include "ConnectionItem.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QGraphicsScene scene;
    scene.setBackgroundBrush(QColor("#2e3440"));

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setDragMode(QGraphicsView::ScrollHandDrag);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setWindowTitle("Qt6 Node Editor MVP");

    // TODO: Make a constructor for these nodes and connections
    // Create & add nodes
    auto *n1 = new NodeItem("Node A");
    auto *n2 = new NodeItem("Node B");
    n1->setPos(50, 50);
    n2->setPos(300, 200);
    scene.addItem(n1);
    scene.addItem(n2);

    // Connect them
    auto *conn = new ConnectionItem(n1, n2);
    scene.addItem(conn);

    // Update path when nodes move (QGraphicsObject provides xChanged/yChanged signals)
    QObject::connect(n1, &NodeItem::xChanged, [=]{ conn->updatePath(n1, n2); });
    QObject::connect(n1, &NodeItem::yChanged, [=]{ conn->updatePath(n1, n2); });
    QObject::connect(n2, &NodeItem::xChanged, [=]{ conn->updatePath(n1, n2); });
    QObject::connect(n2, &NodeItem::yChanged, [=]{ conn->updatePath(n1, n2); });

    view.resize(600, 400);
    view.show();

    return app.exec();
}
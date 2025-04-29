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

#include "Port.hpp"
#include "Node.hpp"
#include "Canvas.hpp"

namespace nixnodes {
 
} // namespace nixnodes

int main(int argc, char *argv[]) {
    using namespace nixnodes;
    QApplication a(argc, argv);

    Canvas node_canvas;
    node_canvas.setSceneRect(-400, -300, 800, 600);
    node_canvas.setBackgroundBrush(Qt::black);

    Node* node1 = new Node("Integer");
    node1->setPos(-200, 0);
    node1->set_body_enabled(true);
    node1->set_body_text("7");
    node_canvas.addItem(node1);
    node1->add_port(Port::Output);

    Node* node2 = new Node("Integer");
    node2->setPos(-200, 100);
    node2->set_body_enabled(true);
    node2->set_body_text("5");
    node_canvas.addItem(node2);
    node2->add_port(Port::Output);

    Node* node3 = new Node("Sum");
    node3->setPos(200, 0);
    node_canvas.addItem(node3);
    node3->add_port(Port::Input);
    node3->add_port(Port::Input);
    node3->add_port(Port::Input);
    node3->add_port(Port::Output);

    QGraphicsView view(&node_canvas);
    view.setRenderHint(QPainter::Antialiasing);
    view.setRenderHint(QPainter::SmoothPixmapTransform);
    view.resize(800, 600);
    view.show();

    return a.exec();
}

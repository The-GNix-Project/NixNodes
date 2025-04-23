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
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include <QString>
#include <QDebug>
#include <QRegularExpression>
#include <QApplication>

#include "lang/io.hpp"
#include "lang/node.hpp"
#include "lang/graph.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    qDebug() << "App Started\n";

    Graph scene;

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setDragMode(QGraphicsView::ScrollHandDrag);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setWindowTitle("NixNodes Prototype");

    auto* node = new Node("node");
    node->add_input(std::make_unique<Input>("myInput1"));
    node->add_input(std::make_unique<Input>("myInput2"));
    node->add_output(std::make_unique<Output>("myOutput1"));
    node->add_output(std::make_unique<Output>("myOutput2"));
    node->add_output(std::make_unique<Output>("myOutput3"));
    node->setPos(50, 50);
    scene.addNode(node);

    auto* node2 = new Node("node2");
    node2->add_input(std::make_unique<Input>("myInput3"));
    node2->add_input(std::make_unique<Input>("myInput4"));
    node2->add_output(std::make_unique<Output>("myOutput4"));
    node2->add_output(std::make_unique<Output>("myOutput5"));
    node2->add_output(std::make_unique<Output>("myOutput6"));
    node2->setPos(100, 100);
    scene.addNode(node2);

    view.resize(600, 400);
    view.show();

    return app.exec();
}
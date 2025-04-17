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

#include "WelcomeWidget.hpp"
#include <QLabel>
#include <QVBoxLayout>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel("NixNodes! The Graphical Programming interface for the Nix Language", this);
    layout->addWidget(label);

    setLayout(layout);
}

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
#include <QRegularExpression>

#include "nodes/io.hpp"
#include "nodes/node.hpp"

auto key_selector = [](auto pair){return pair.first;};

int main(int argc, char *argv[]) {
    using namespace std;
    auto mynode = Node("myNode");
    mynode.add_input(std::make_unique<Input>("i1"));
    mynode.add_input(std::make_unique<Input>("i2"));
    mynode.add_output(std::make_unique<Output>("o1"));

    auto inputs = mynode.get_inputs();
    vector<string> input_keys(inputs.size());
    transform(inputs.begin(), inputs.end(), input_keys.begin(), key_selector);
    cout << "Inputs:\n";
    for (string key : input_keys) cout << " " << key << "\n";

    auto outputs = mynode.get_outputs();
    vector<string> output_keys(outputs.size());
    transform(outputs.begin(), outputs.end(), output_keys.begin(), key_selector);
    cout << "Outputs:\n";
    for (string key : output_keys) cout << " " << key << "\n";
    return 0;
}
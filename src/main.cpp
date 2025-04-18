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
#include <regex>
#include <QString>
#include <QRegularExpression>

#define REGEX_MATCH(var, rx) std::regex_match(var, std::regex(rx))

class IO {
public:
    template<typename T>
    IO(T init_name) {
        change_name(init_name);
    }

    bool change_name(const QString& new_name) {
        if (new_name.length() > 52) {
            return false;
        }

        // Regex: starts with letter/_ and followed by letters, numbers, _, or space
        QRegularExpression rx(R"(^[a-zA-Z_][a-zA-Z0-9_ ]*$)");
        if (rx.match(new_name).hasMatch()) {
            name = new_name;
            return true;
        }

        return false;
    }
    
    bool change_name(const std::string& new_name) {
        return change_name(QString::fromStdString(new_name));
    }

    bool change_name(const char* new_name) {
        return change_name(QString::fromUtf8(new_name));
    }

    std::string format_name() {
        QString clean = name.trimmed().toLower();

        clean.replace(QRegularExpression("[^a-zA-Z0-9_]"), "_");

        clean.replace(QRegularExpression("_+"), "_");

        clean = clean.trimmed();
        if (clean.startsWith('_') || clean.endsWith('_'))
            clean = clean.mid(clean.startsWith('_') ? 1 : 0,
                            clean.length() - (clean.endsWith('_') ? 1 : 0));

        if (!clean.isEmpty() && !QRegularExpression("^[a-zA-Z_]").match(clean).hasMatch()) {
            clean = "_" + clean;
        }
        return clean.toStdString();
    }

    QString get_name() {return name;}

protected:
    QString name;
};

class Input: public IO {    
public:
    template<typename T>
    Input(T init_name) {
        change_name(init_name);
    }
};

class Output: public IO {    
public:
    template<typename T>
    Output(T init_name) {
        change_name(init_name);
    }
};

int main(int argc, char *argv[]) {
    auto input = Input("my Input");
    std::cout << input.format_name();
    return 0;
}
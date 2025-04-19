#include "nodes/io.hpp"

bool IO::change_name(const QString& new_name) {
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

bool IO::change_name(const std::string& new_name) {
    return change_name(QString::fromStdString(new_name));
}

bool IO::change_name(const char* new_name) {
    return change_name(QString::fromUtf8(new_name));
}

std::string IO::format_name() {
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

QString IO::get_name() {return name;}
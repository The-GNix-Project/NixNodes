#ifndef IO_HPP
#define IO_HPP

#include <string>
#include <QString>
#include <QRegularExpression>

class IO {
public:
    template<typename T>
    IO(T init_name) {
        change_name(init_name);
    }

    bool change_name(const QString& new_name);
    bool change_name(const std::string& new_name);
    bool change_name(const char* new_name);

    QString get_name();
    std::string format_name();
protected:
    QString name;
};

class Input: public IO {    
public:
    template<typename T>
    Input(T init_name): IO(init_name) {
        change_name(init_name);
    }
};

class Output: public IO {    
public:
    template<typename T>
    Output(T init_name): IO(init_name) {
        change_name(init_name);
    }
};

#endif
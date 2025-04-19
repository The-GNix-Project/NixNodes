#ifndef NODE_HPP
#define NODE_HPP

#include <QString>
#include <vector>
#include <unordered_map>
#include <memory>
#include "nodes/io.hpp"

class Node {
public:
    template<typename T>
    Node(T init_name) : name(init_name) {}

    bool change_name(const QString& new_name);
    bool change_name(const std::string& new_name);
    bool change_name(const char* new_name);

    void add_input(std::unique_ptr<Input> input);
    void delete_input(const std::string& name);
    std::unordered_map<std::string, Input*> get_inputs();

    void add_output(std::unique_ptr<Output> output);
    void delete_output(const std::string& name);
    std::unordered_map<std::string, Output*> get_outputs();

private:
    QString name;
    
    std::vector<std::unique_ptr<Input>> ordered_inputs;
    std::unordered_map<std::string, Input*> named_inputs;
    
    std::vector<std::unique_ptr<Output>> ordered_outputs;
    std::unordered_map<std::string, Output*> named_outputs;
};

#endif
#include "nodes/node.hpp"
#include <QRegularExpression>

// Name management implementations
bool Node::change_name(const QString& new_name) {
    if (new_name.length() > 52) return false;
    
    static QRegularExpression rx(R"(^[a-zA-Z_][a-zA-Z0-9_ ]*$)");
    if (rx.match(new_name).hasMatch()) {
        name = new_name;
        return true;
    }
    return false;
}

bool Node::change_name(const std::string& new_name) {
    return change_name(QString::fromStdString(new_name));
}

bool Node::change_name(const char* new_name) {
    return change_name(QString::fromUtf8(new_name));
}

// Input implementations
void Node::add_input(std::unique_ptr<Input> input) {
    ordered_inputs.push_back(std::move(input));
    named_inputs[ordered_inputs.back()->get_name().toStdString()] = ordered_inputs.back().get();
}

void Node::delete_input(const std::string& name) {
    if (auto it = named_inputs.find(name); it != named_inputs.end()) {
        auto pos = std::find_if(ordered_inputs.begin(), ordered_inputs.end(),
            [&](auto& ptr) { return ptr.get() == it->second; });
        if (pos != ordered_inputs.end()) {
            std::swap(*pos, ordered_inputs.back());
            ordered_inputs.pop_back();
        }
        named_inputs.erase(it);
    }
}

std::unordered_map<std::string, Input*> Node::get_inputs() {
    return named_inputs;
}

// Output implementations
void Node::add_output(std::unique_ptr<Output> output) {
    ordered_outputs.push_back(std::move(output));
    named_outputs[ordered_outputs.back()->get_name().toStdString()] = ordered_outputs.back().get();
}

void Node::delete_output(const std::string& name) {
    if (auto it = named_outputs.find(name); it != named_outputs.end()) {
        auto pos = std::find_if(ordered_outputs.begin(), ordered_outputs.end(),
            [&](auto& ptr) { return ptr.get() == it->second; });
        if (pos != ordered_outputs.end()) {
            std::swap(*pos, ordered_outputs.back());
            ordered_outputs.pop_back();
        }
        named_outputs.erase(it);
    }
}

std::unordered_map<std::string, Output*> Node::get_outputs() {
    return named_outputs;
}
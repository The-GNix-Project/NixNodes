#include "lang/node.hpp"
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

std::unordered_map<std::string, Input*> Node::get_inputs() {
    return named_inputs;
}

std::unordered_map<std::string, Output*> Node::get_outputs() {
    return named_outputs;
}

void Node::add_input(std::unique_ptr<Input> input) {
    input->setParentItem(this);
    ordered_inputs.push_back(std::move(input));
    named_inputs[ordered_inputs.back()->get_name().toStdString()] = ordered_inputs.back().get();
    updateSizeAndPositions(); 
}

void Node::add_output(std::unique_ptr<Output> output) {
    output->setParentItem(this);
    ordered_outputs.push_back(std::move(output));
    named_outputs[ordered_outputs.back()->get_name().toStdString()] = ordered_outputs.back().get();
    updateSizeAndPositions(); 
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
        updateSizeAndPositions();
    }
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
        updateSizeAndPositions();
    }
}

// Calculate the minimum required height based on I/O count
int Node::calculateRequiredHeight() const {
    const int title_height = 20;
    const int padding_below_title = 10;
    const int spacing_per_port = 20; // Minimum vertical space between ports
    const int min_height = 60; // title (20) + padding (10) + 30 (min space for 1 port)

    const size_t max_io = std::max(ordered_inputs.size(), ordered_outputs.size());
    const int required_height = title_height + padding_below_title + (max_io * spacing_per_port);
    
    return std::max(required_height, min_height);
}

void Node::updateSizeAndPositions() {
    const int new_height = calculateRequiredHeight();
    prepareGeometryChange();

    // left / inputs
    for (size_t i = 0; i < ordered_inputs.size(); ++i) {
        qreal spacing = new_height / (ordered_inputs.size() + 1.0);
        qreal y = (i + 1) * spacing;
        ordered_inputs[i]->setPos(-5, y - 5);
    }

    // right / outputs
    for (size_t i = 0; i < ordered_outputs.size(); ++i) {
        qreal spacing = new_height / (ordered_outputs.size() + 1.0);
        qreal y = (i + 1) * spacing;
        ordered_outputs[i]->setPos(115, y - 5);
    }
}

QRectF Node::boundingRect() const {
    const qreal width = 120.0;
    const qreal height = static_cast<qreal>(calculateRequiredHeight());
    return { 0.0, 0.0, width, height };
}

void Node::paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget*) {
    const int height = calculateRequiredHeight();

    // Body (dynamic height)
    p->setBrush(isSelected() ? Qt::lightGray : Qt::white);
    QPainterPath bottom_path;
    bottom_path.addRoundedRect(QRectF(0, 0, 120, height), 7, 7);
    p->setPen(Qt::black);
    p->fillPath(bottom_path, Qt::black);
    p->drawPath(bottom_path);
    
    // Title bar (fixed height)
    p->setBrush(Qt::gray);
    QRectF title_rect(0, 0, 120, 20);
    QPainterPath top_path;
    top_path.addRoundedRect(title_rect, 7, 7);
    p->setPen(Qt::black);
    p->fillPath(top_path, Qt::gray);
    p->drawPath(top_path);

    // Draw centered text
    p->setPen(Qt::white);
    QTextOption text_option(Qt::AlignCenter);
    p->drawText(title_rect, name, text_option);
}

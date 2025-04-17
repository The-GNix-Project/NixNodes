#include "welcome_widget.hpp"
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

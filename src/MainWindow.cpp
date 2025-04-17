#include "MainWindow.hpp"
#include "WelcomeWidget.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set a window title
    setWindowTitle("NixNodes");

    // Create an instance of MyWidget and set it as the central widget.
    MyWidget *widget = new MyWidget(this);
    setCentralWidget(widget);
}

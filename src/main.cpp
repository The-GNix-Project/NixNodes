// #include <QApplication>
// #include "MainWindow.hpp"

// int main(int argc, char *argv[])
// {   
//     QApplication app(argc, argv);

//     MainWindow window;
//     window.show();

//     return app.exec();
// }
#include <QApplication>
#include <QGraphicsView>
#include "NodeItem.hpp"
#include "ConnectionItem.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QGraphicsScene scene;
    scene.setBackgroundBrush(QColor("#2e3440"));

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setDragMode(QGraphicsView::ScrollHandDrag);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setWindowTitle("Qt6 Node Editor MVP");

    // Create & add nodes
    auto *n1 = new NodeItem("Node A");
    auto *n2 = new NodeItem("Node B");
    n1->setPos(50, 50);
    n2->setPos(300, 200);
    scene.addItem(n1);
    scene.addItem(n2);

    // Connect them
    auto *conn = new ConnectionItem(n1, n2);
    scene.addItem(conn);

    // Update path when nodes move (QGraphicsObject provides xChanged/yChanged signals)
    QObject::connect(n1, &NodeItem::xChanged, [=]{ conn->updatePath(n1, n2); });
    QObject::connect(n1, &NodeItem::yChanged, [=]{ conn->updatePath(n1, n2); });
    QObject::connect(n2, &NodeItem::xChanged, [=]{ conn->updatePath(n1, n2); });
    QObject::connect(n2, &NodeItem::yChanged, [=]{ conn->updatePath(n1, n2); });

    view.resize(600, 400);
    view.show();

    return app.exec();
}
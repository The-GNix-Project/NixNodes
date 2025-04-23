#include "lang/graph.hpp"
#include "lang/connection.hpp"
#include <QPoint>

// In your scene/view class (e.g., GraphScene.cpp)
void Graph::addNode(Node* node) {
    addItem(node);
    
    // Connect signals for all outputs in the node
    for (auto& [name, output] : node->get_outputs()) {
        bool ok = connect(output, &Output::dragStarted,
                          this,   &Graph::onOutputDragStart);
        Q_ASSERT(ok); 
        connect(output, &Output::dragStarted, this, &Graph::onOutputDragStart);
        connect(output, &Output::dragUpdated, this, &Graph::onOutputDragUpdate);
        connect(output, &Output::dragEnded, this, &Graph::onOutputDragEnd);
    }
}

void Graph::onOutputDragStart(QPointF pos) {
    auto* view = views().first();
    view->setDragMode(QGraphicsView::NoDrag);

    // just store the source; don’t add to scene yet
    pendingSource = qobject_cast<Output*>(sender());
    qDebug() << "Drag START (waiting for move) from" << pendingSource->get_name();
}

void Graph::onOutputDragUpdate(QPointF pos) {
    if (!tempConnection) {
        // first move after press: create + add
        tempConnection = new Connection(pendingSource, nullptr);
        addItem(tempConnection);
        qDebug() << "…now adding tempConnection";
    }
    tempConnection->updateTempEnd(pos);
}

void Graph::onOutputDragEnd(QPointF scenePos) {
    qDebug() << "Drag Ended";

    if (!tempConnection) {
        // restore drag mode and bail
        views().first()->setDragMode(QGraphicsView::ScrollHandDrag);
        return;
    }

    // Get all items under the cursor, in stacking order:
    auto hits = items(scenePos, Qt::IntersectsItemShape);

    Input* target = nullptr;
    for (auto* gi : hits) {
        // Skip your own Connection item if it’s still there
        if (gi == tempConnection)  continue;

        // Try to cast directly to Input
        if (auto* io = dynamic_cast<Input*>(gi)) {
            target = io;
            break;  // first (topmost) Input is our target
        }
    }

    qDebug() << "Resolved target:" << target;

    // Only connect if we got a valid Input on a different node
    if (target && target->parentNode() != tempConnection->source()->parentNode()) {
        qDebug() << "Valid Target — creating final connection";
        auto* finalConn = new Connection(tempConnection->source(), target);
        addItem(finalConn);
    }

    // Clean up the temporary rubber-band
    removeItem(tempConnection);
    delete tempConnection;
    tempConnection = nullptr;

    // Restore panning
    views().first()->setDragMode(QGraphicsView::ScrollHandDrag);
}

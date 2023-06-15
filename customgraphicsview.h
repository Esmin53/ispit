#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

class CustomGraphicsView : public QGraphicsView
{
public:
    explicit CustomGraphicsView(QWidget* parent = NULL)
        : QGraphicsView(parent)
    {}

protected:
    void mouseMoveEvent(QMouseEvent* event) override
    {

        QGraphicsView::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent* event) override
    {



        QGraphicsView::mouseReleaseEvent(event);
    }
};

#endif // CUSTOMGRAPHICSVIEW_H

/*
 * Copyright (c) 2011 Cesar L. B. Silveira
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <QApplication>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "SizeGripItem.h"

namespace
{
    class RectResizer : public SizeGripItem::Resizer
    {
        public:
	    void operator()(QGraphicsItem* item, const QRectF& rect) override
            {
	            auto rectItem =
                    dynamic_cast<QGraphicsRectItem*>(item);

                if (rectItem)
                {
                    rectItem->setRect(rect);
                }
            }
    };

    class EllipseResizer : public SizeGripItem::Resizer
    {
        public:
	    void operator()(QGraphicsItem* item, const QRectF& rect) override
            {
	            auto ellipseItem =
                    dynamic_cast<QGraphicsEllipseItem*>(item);

                if (ellipseItem)
                {
                    ellipseItem->setRect(rect);
                }
            }
    };
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene scene;

    QGraphicsRectItem rectItem(QRectF(0, 0, 320, 240));
    rectItem.setBrush(Qt::NoBrush);
    rectItem.setPen(QPen(Qt::red));
    rectItem.setFlag(QGraphicsItem::ItemIsMovable);
    scene.addItem(&rectItem);

    QGraphicsEllipseItem ellipseItem(QRectF(0, 0, 200, 200));
    ellipseItem.setBrush(Qt::NoBrush);
    ellipseItem.setPen(QPen(Qt::blue));
    ellipseItem.setFlag(QGraphicsItem::ItemIsMovable);
    scene.addItem(&ellipseItem);

	QPolygonF points;
	points << QPointF(-300.0, 100.0);
	points << QPointF(0.0, 300.0);
	points << QPointF(300.0, 100.0);
	points << QPointF(200.0, -200.0);
	points << QPointF(-200.0, -200.0);
	QGraphicsPolygonItem polygon(points);
	polygon.setBrush(Qt::NoBrush);
	polygon.setPen(QPen(Qt::green));
	polygon.setFlag(QGraphicsItem::ItemIsMovable);
	scene.addItem(&polygon);

    SizeGripItem rectSizeGrip(new RectResizer, &rectItem);
    SizeGripItem ellpiseSizeGrip(new EllipseResizer, &ellipseItem);

    QGraphicsView graphicsView;
    graphicsView.setScene(&scene);
    graphicsView.resize(400, 300);
    graphicsView.show();

    return a.exec();
}

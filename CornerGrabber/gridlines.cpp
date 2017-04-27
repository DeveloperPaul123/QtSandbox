#include "gridlines.h"
#include <QColor>

GridLines::GridLines( int w, int h ) : QGraphicsItem(),
            _width(w), _height(h), _space(10)
{

}

void GridLines::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // re-draw the grid lines from 0,0 to _width, _height

    // do horizontal first

    QColor c (200,200,255,125);

    painter->setPen( c);

    for (int y= 0; y < _height; y+=_space)
    {
        painter->drawLine(0,y, _width, y);
    }

    for (int x= 0; x < _width; x+=_space)
    {
        painter->drawLine(x,0, x, _height);
    }

}

QRectF GridLines::boundingRect() const
{
    return QRectF ( static_cast<qreal>(0), static_cast<qreal>(0), static_cast<qreal>(_width), static_cast<qreal>( _height));
}

void GridLines::handleWindowSizeChanged(int w, int h)
{
    _width = w;
    _height = h;
}

void GridLines::mouseMoveEvent(QGraphicsSceneDragDropEvent *)
{

}

void GridLines::mousePressEvent(QGraphicsSceneDragDropEvent *)
{

}

void GridLines::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
}

void GridLines::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
}

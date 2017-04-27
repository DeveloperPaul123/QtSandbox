/*
  * Copyright 2010, David W. Drell
  *
  * This is free sample code. Use as you wish, no warranties.
  */

#ifndef STATEBOX_H
#define STATEBOX_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QPainter>
#include <QPen>
#include <QPointF>
#include "cornergrabber.h"




/**
  * \class StateBox
  * This is short example/demonstration of creating a custom Qt QGraphicsItem.
  *  Example usage of a custom QGraphicsItem in a QGraphicsScene with examples of mouse hover events.
  *
  *  My goal was to create a simpe box, in the shape of a UML State/Class box, with a title
  *  area seprated from a main arear below by line.
  *
  *  This sample class inherits from QGraphicsItem, and must reimplement boundingRect() and paint()
  *  from the base class.
  *
  *  To learn about handling mouse events in a QGraphicsScene, I wanted my box to turn red when the mouse moves inside, and black
  *  when the mouse moves out.
  */

class StateBox : public QGraphicsItem
{
public:
    StateBox();
    QGraphicsTextItem _text;    ///< sample text to go in the title area.

    void setGridSpace(int space);

    private:


	QRectF boundingRect() const override; ///< must be re-implemented in this class to provide the diminsions of the box to the QGraphicsView
	void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; ///< must be re-implemented here to pain the box on the paint-event
	void hoverEnterEvent ( QGraphicsSceneHoverEvent * event ) override; ///< must be re-implemented to handle mouse hover enter events
	void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event ) override; ///< must be re-implemented to handle mouse hover leave events

	void mouseMoveEvent ( QGraphicsSceneMouseEvent * event ) override;///< allows the main object to be moved in the scene by capturing the mouse move events
	void mousePressEvent (QGraphicsSceneMouseEvent * event ) override;
	void mouseReleaseEvent (QGraphicsSceneMouseEvent * event ) override;

    virtual void mouseMoveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void mousePressEvent(QGraphicsSceneDragDropEvent *event);
	bool sceneEventFilter ( QGraphicsItem * watched, QEvent * event ) override;

    void setCornerPositions();
    void adjustSize(int x, int y);


    QColor _outterborderColor; ///< the hover event handlers will toggle this between red and black
    QPen _outterborderPen; ///< the pen is used to paint the red/black border
    QPointF _location;
    QPointF _dragStart;
    int     _gridSpace;
    qreal   _width;
    qreal   _height;

    QPointF _cornerDragStart;

    int _XcornerGrabBuffer;
    int _YcornerGrabBuffer;
    qreal   _drawingWidth;
    qreal   _drawingHeight;
    qreal   _drawingOrigenX;
    qreal   _drawingOrigenY;

    CornerGrabber*  _corners[4];// 0,1,2,3  - starting at x=0,y=0 and moving clockwise around the box


};

#endif // STATEBOX_H

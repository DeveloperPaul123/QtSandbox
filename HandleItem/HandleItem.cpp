#include "HandleItem.h"
 
#include <QPainter>
#include <QPointF>
 
#include <cmath>
#include <iostream>
 
HandleItem::HandleItem( QGraphicsRectItem *item, QGraphicsScene *scene, QColor color, HandleItem::HandleRole role, QList<HandleItem*> handles ) 
: QGraphicsItem(item)
{
  m_role = role;
  m_color = color;
 
  m_item = item;
  m_handles = handles;
 
  m_pressed = false;
  setZValue( 100 );
 
  setFlag( ItemIsMovable );
  setFlag(ItemSendsGeometryChanges);
}
 
void HandleItem::paint( QPainter *paint, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
  paint->setPen( m_color );
  paint->setBrush( m_color );
 
  QRectF rect = boundingRect();
  QVector<QPointF> points;
 
  switch( m_role )
  {
  case RightHandle:
    points << rect.center()+QPointF(3,0) << rect.center()+QPointF(-3,-5) << rect.center()+QPointF(-3,5);
    paint->drawConvexPolygon( QPolygonF(points) );
    break;
  case LeftHandle:
    points << rect.center()+QPointF(-3,0) << rect.center()+QPointF(3,-5) << rect.center()+QPointF(3,5);
    paint->drawConvexPolygon( QPolygonF(points) );
    break;
  case TopHandle:
    points << rect.center()+QPointF(0,-3) << rect.center()+QPointF(-5,3) << rect.center()+QPointF(5,3);
    paint->drawConvexPolygon( QPolygonF(points) );
    break;
  case BottomHandle:
    points << rect.center()+QPointF(0,3) << rect.center()+QPointF(-5,-3) << rect.center()+QPointF(5,-3);
    paint->drawConvexPolygon( QPolygonF(points) );
    break;
  }
}
 
 
QRectF HandleItem::boundingRect() const
{
  switch( m_role )
  {
  case LeftHandle:
    {
    QPointF point(m_item->boundingRect().left() - pos().x(), m_item->boundingRect().top() + m_item->boundingRect().height()/2);
    return QRectF( point-QPointF(3, 5), QSize( 6, 10 ) );
    }
  case RightHandle:
    {
    QPointF point(m_item->boundingRect().right() - pos().x(), m_item->boundingRect().top() + m_item->boundingRect().height()/2);
    return QRectF( point-QPointF(3, 5), QSize( 6, 10 ) );
    }
  case TopHandle:
    {
    QPointF point(m_item->boundingRect().left() + m_item->boundingRect().width()/2, m_item->boundingRect().top() - pos().y());
    return QRectF( point-QPointF(5, 3), QSize( 10, 6 ) );
    }
  case BottomHandle:
    {
    QPointF point(m_item->boundingRect().left() + m_item->boundingRect().width()/2, m_item->boundingRect().bottom() - pos().y());
    return QRectF( point-QPointF(5, 3), QSize( 10, 6 ) );
    }
  }
 
  return QRectF();
}
 
QVariant HandleItem::itemChange( GraphicsItemChange change, const QVariant &data )
{
  if( change == ItemPositionChange && m_pressed )
  {
 
    QPointF movement;
    QPointF newData = data.toPointF();
    QRectF newRect = m_item->rect();
 
    switch( m_role )
    {
    case LeftHandle:
      {
      // Prevent the rectangle from collapsing.
      //if( fabs(movement.x()) <= 5 )
      if(m_item->rect().width() < 5)
        {
        std::cout << "too small! " << std::endl;
        return QGraphicsItem::itemChange( change, newData );
        }
 
      // Snap the movement to the X direction
      newData.setY(0);
 
      movement = newData - pos();
      // Resize the rectangle
      newRect.setLeft(m_item->rect().left() + movement.x());
 
      m_item->setRect(newRect);
 
      break;
      }
    case RightHandle:
      {
      // Prevent the rectangle from collapsing.
      //if( fabs(movement.x()) <= 5 )
      //if(m_item->rect().width() < 5)
      if(m_item->rect().width() + movement.x() <= 5)
	{
	std::cout << "too small! " << std::endl;
	return QGraphicsItem::itemChange( change, newData );
	}
 
      // Snap the movement to the X direction
      newData.setY(0);
 
      movement = newData - pos();
      // Resize the rectangle
      newRect.setRight(m_item->rect().right() + movement.x());
 
      m_item->setRect(newRect);
 
      break;
      }
    case TopHandle:
      {
      // Prevent the rectangle from collapsing.
      //if( fabs(movement.x()) <= 5 )
      if(m_item->rect().height() < 5)
        {
        std::cout << "too small! " << std::endl;
        return QGraphicsItem::itemChange( change, newData );
        }
 
      // Snap the movement to the Y direction
      newData.setX(0);
 
      movement = newData - pos();
      // Resize the rectangle
      newRect.setTop(m_item->rect().top() + movement.y());
 
      m_item->setRect(newRect);
 
      break;
      }
    case BottomHandle:
      {
      // Prevent the rectangle from collapsing.
      //if( fabs(movement.x()) <= 5 )
      if(m_item->rect().height() < 5)
        {
        std::cout << "too small! " << std::endl;
        return QGraphicsItem::itemChange( change, newData );
        }
 
      // Snap the movement to the Y direction
      newData.setX(0);
 
      movement = newData - pos();
      // Resize the rectangle
      newRect.setBottom(m_item->rect().bottom() + movement.y());
 
      m_item->setRect(newRect);
 
      break;
      }
    } // end switch
 
    return QGraphicsItem::itemChange( change, newData);
  } // end if pressed
 
  return QGraphicsItem::itemChange( change, data );
}
 
void HandleItem::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
  m_pressed = true;  
  QGraphicsItem::mousePressEvent( event );
}
 
void HandleItem::mouseReleaseEvent( QGraphicsSceneMouseEvent *event )
{
  m_pressed = false;
  QGraphicsItem::mouseReleaseEvent( event );
}
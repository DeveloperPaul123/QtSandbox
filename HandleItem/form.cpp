#include <QtGui>
 
#include "form.h"
#include "HandleItem.h"
 
#include <iostream>
 
Form::Form(QWidget *parent) : QWidget(parent)
{
	setupUi(this);

	auto scene = new QGraphicsScene(0, 0, 200, 200, this);
	auto *rectItem = new QGraphicsRectItem(QRectF(10, 10, 50, 100));
	rectItem->setFlag(QGraphicsItem::ItemIsMovable);

	// The center handle must know about all of the other handles so it can translate them with the object
	auto *topHandle = new HandleItem(rectItem, scene, Qt::red, HandleItem::TopHandle);
	auto *rightHandle = new HandleItem(rectItem, scene, Qt::red, HandleItem::RightHandle);
	auto *leftHandle = new HandleItem(rectItem, scene, Qt::red, HandleItem::LeftHandle);
	auto *bottomHandle = new HandleItem(rectItem, scene, Qt::red, HandleItem::BottomHandle);
	auto *centerHandle = new HandleItem(rectItem, scene, Qt::red, HandleItem::CenterHandle,
		QList<HandleItem*>() << topHandle << rightHandle << leftHandle << bottomHandle);
	scene->addItem(rectItem);
	this->graphicsView->setScene(scene);
}
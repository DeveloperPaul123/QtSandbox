/*
  * Copyright 2010, David W. Drell
  *
  * This is free sample code. Use as you wish, no warranties.
  */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QScrollBar>
#include <QResizeEvent>
#include "statebox.h"
#include "gridlines.h"

/*! \mainpage Example Qt QGraphicsItem implemenation
 *
 * Example usage of a custom QGraphicsItem in a QGraphicsScene with examples of mouse hover events.
 *
 * My goal was to create a simpe box, in the shape of a UML State/Class box, with a title
 * area seprated from a main arear below by line.
 *
 * This sample class inherits from QGraphicsItem, and must reimplement boundingRect() and paint()
 * from the base class.
 *
 * To learn about handling mouse events in a QGraphicsScene, I wanted my box to turn red when the mouse moves inside, and black
 * when the mouse moves out.
 *
 *
 *\image html  mainwindowscreenshot.png
 *
 */

/*!
 * \class MainWindow
 *
 * Example usage of a custom QGraphicsItem in a QGraphicsScene with examples of mouse hover events.
 *
 * My goal was to create a simpe box, in the shape of a UML State/Class box, with a title
 * area seprated from a main arear below by line. To learn about handling mouse events in a QGraphicsScene, I wanted my box to turn red when the mouse moves inside, and black
 * when the mouse moves out.
 *
 *  I created the project with QtCreator. I started a new C++ UI project. But I did not use
 *  creator to add widgets to the main window, but rather created instances of the widgets myself.
 *  QtCreator started a mainwindow.h and mainwindow.cpp files - from there I added my widgets.
 *
 */

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui; ///< QtCreator made this instance.

    QGraphicsScene * scene ; ///< the scene will contain the graphics item 'StateBox'

    QGraphicsView * gview; ///< the graphics view will contain and display the scene.

    StateBox * stateBox; ///< this is my custom QGraphicsItem
    GridLines * gridLines; ///< this is my custom QGraphicsItem


    virtual void resizeEvent(QResizeEvent *);///< re-implementing this event handler of the QMainWindow class allows my to capture re-size window values - not used in this project
};

#endif // MAINWINDOW_H

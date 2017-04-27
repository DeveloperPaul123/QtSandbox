/*
  * Copyright 2010, David W. Drell
  *
  * This is free sample code. Use as you wish, no warranties.
  */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSizePolicy>
#include <QGraphicsLineItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow()),
    scene( new QGraphicsScene()),
    gview( new QGraphicsView ()),
    stateBox( new StateBox()),
    gridLines( NULL )
{
    QColor c (242,251,235);

    QBrush brush (c, Qt::SolidPattern);
    scene->setBackgroundBrush(brush);
    /*!
      \verbatim
        ui->setupUi(this);
      \endverbatim

    QtCreator generates ui_mainwindow.h, which defines a new class Ui_MainWindow,
    then makes MainWindow inherit Ui_MainWindow. Ui_MainWindow defines the setupUi() method which creates instances of all
    QtCreator objects.
    */
    ui->setupUi(this);

    /*!
      \verbatim
      ui->horizontalLayout->addWidget( gview);
      \endverbatim
     I used QtCreator's design surface (right-click on main window area) to add a layout
     to hold the graphics view. This also allows the graphicsview to change size  and expand/contract
     to fill the window area as the user changes the size of the main window frame.
     */
    ui->horizontalLayout->addWidget( gview);

    gridLines = new GridLines (this->width(), this->height());
    scene->addItem(gridLines);

    /*!
      \verbatim
      scene->addItem( stateBox);
      \endverbatim
      scene holds the custom QGraphicsItem stateBox
    */
    stateBox->setPos(200,200);
    scene->addItem( stateBox);



    /*!
      \verbatim
      gview->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
      \endverbatim
     setSizePolicy, when used with the horizontalLayout widget, allows the grapicsview to expand/contract
     as the user re-sizes the main window.
    */
    gview->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    /*!
      \verbatim
       gview->setScene(  scene);
      \endverbatim
        add the scene to the QGraphicsView
    */
    gview->setScene(  scene);


    gview->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    gview->show();
}

void MainWindow::resizeEvent(QResizeEvent * )
{
    QSize wsize = ui->centralWidget->frameSize();

    if ( gridLines) gridLines->handleWindowSizeChanged(wsize.width(), wsize.height());

    qDebug() << "cw frame height" << wsize.height() << " width: " << wsize.width();
}


MainWindow::~MainWindow()
{
    delete gview;
    delete stateBox;
    delete scene;
    delete ui;
}


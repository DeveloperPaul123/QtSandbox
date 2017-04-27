#ifndef FORM_H
#define FORM_H
 
#include "ui_form.h"
 
class Form : public QWidget, Ui::Form
{
    Q_OBJECT
 
public:
	explicit Form(QWidget *parent = nullptr);
};
 
#endif
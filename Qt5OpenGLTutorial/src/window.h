#pragma once 
#include <QOpenGLWidget>
#include <qopenglfunctions.h>
#include <qopenglvertexarrayobject.h>
#include <qopenglbuffer.h>
#include <qopenglshaderprogram.h>
#include "transform3d.h"

class Window : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT
public:
	explicit Window(QWidget* parent = nullptr);
	~Window();

	void initializeGL() override;
	void resizeGL(int width, int height) override;
	void paintGL() override;
	void teardownGL();

protected slots:
	void update();

private:
	void printContextInformation();

	QOpenGLBuffer mVertex;
	QOpenGLVertexArrayObject mObject;
	QOpenGLShaderProgram *mProgram;

	int u_modelToWorld;
	int u_worldToView;
	QMatrix4x4 m_projection;
	Transform3D m_transform;
};

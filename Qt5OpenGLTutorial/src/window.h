#pragma once 
#include <QOpenGLWidget>
#include <qopenglfunctions.h>
#include <qopenglvertexarrayobject.h>
#include <qopenglbuffer.h>
#include <qopenglshaderprogram.h>
#include "transform3d.h"
#include "camera3d.h"

class Window : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT
public:
	explicit Window(QWidget* parent = nullptr);
	virtual ~Window();

	void initializeGL() override;
	void resizeGL(int width, int height) override;
	void paintGL() override;
	void teardownGL();

protected:
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void wheelEvent(QWheelEvent* event) override;

protected slots:
	void update();

private:
	void printContextInformation();

	QOpenGLBuffer mVertex;
	QOpenGLVertexArrayObject mObject;
	QOpenGLShaderProgram *mProgram;

	int u_modelToWorld;
	int u_worldToCamera;
	int u_cameraToView;
	QMatrix4x4 m_projection;
	Camera3D m_camera;
	Transform3D m_transform;
};

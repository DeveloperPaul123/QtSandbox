#include "window.h"
#include <QDebug>
#include "vertex.h"
#include <qopenglwindow.h>
#include "input.h"
#include <QResizeEvent>

#include <GL/GL.h>

// Front Verticies
#define VERTEX_FTR Vertex( QVector3D( 0.5f,  0.5f,  0.5f), QVector3D( 1.0f, 0.0f, 0.0f ) )
#define VERTEX_FTL Vertex( QVector3D(-0.5f,  0.5f,  0.5f), QVector3D( 0.0f, 1.0f, 0.0f ) )
#define VERTEX_FBL Vertex( QVector3D(-0.5f, -0.5f,  0.5f), QVector3D( 0.0f, 0.0f, 1.0f ) )
#define VERTEX_FBR Vertex( QVector3D( 0.5f, -0.5f,  0.5f), QVector3D( 0.0f, 0.0f, 0.0f ) )

// Back Verticies
#define VERTEX_BTR Vertex( QVector3D( 0.5f,  0.5f, -0.5f), QVector3D( 1.0f, 1.0f, 0.0f ) )
#define VERTEX_BTL Vertex( QVector3D(-0.5f,  0.5f, -0.5f), QVector3D( 0.0f, 1.0f, 1.0f ) )
#define VERTEX_BBL Vertex( QVector3D(-0.5f, -0.5f, -0.5f), QVector3D( 1.0f, 0.0f, 1.0f ) )
#define VERTEX_BBR Vertex( QVector3D( 0.5f, -0.5f, -0.5f), QVector3D( 1.0f, 1.0f, 1.0f ) )

// Create a colored cube
static const Vertex sg_vertexes[] = {
	// Face 1 (Front)
	VERTEX_FTR, VERTEX_FTL, VERTEX_FBL,
	VERTEX_FBL, VERTEX_FBR, VERTEX_FTR,
	// Face 2 (Back)
	VERTEX_BBR, VERTEX_BTL, VERTEX_BTR,
	VERTEX_BTL, VERTEX_BBR, VERTEX_BBL,
	// Face 3 (Top)
	VERTEX_FTR, VERTEX_BTR, VERTEX_BTL,
	VERTEX_BTL, VERTEX_FTL, VERTEX_FTR,
	// Face 4 (Bottom)
	VERTEX_FBR, VERTEX_FBL, VERTEX_BBL,
	VERTEX_BBL, VERTEX_BBR, VERTEX_FBR,
	// Face 5 (Left)
	VERTEX_FBL, VERTEX_FTL, VERTEX_BTL,
	VERTEX_FBL, VERTEX_BTL, VERTEX_BBL,
	// Face 6 (Right)
	VERTEX_FTR, VERTEX_FBR, VERTEX_BBR,
	VERTEX_BBR, VERTEX_BTR, VERTEX_FTR
};

#undef VERTEX_BBR
#undef VERTEX_BBL
#undef VERTEX_BTL
#undef VERTEX_BTR

#undef VERTEX_FBR
#undef VERTEX_FBL
#undef VERTEX_FTL
#undef VERTEX_FTR

Window::Window(QWidget* parent)
	:QOpenGLWidget(parent)
{
	// move back 5 units
	m_transform.translate(0.0, 0.0, -5.0f);
	setFocusPolicy(Qt::FocusPolicy::StrongFocus);
}

Window::~Window()
{
	makeCurrent();
	teardownGL();
}

void Window::initializeGL()
{
	initializeOpenGLFunctions();
	connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
	printContextInformation();

	// Set global information
	// Will only draw faces that wind counter clockwise.
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Application-specific initialization
	{
		// Create Shader (Do not release until VAO is created)
		mProgram = new QOpenGLShaderProgram();
		mProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
		mProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
		mProgram->link();
		mProgram->bind();

		// Cache Uniform Locations
		u_modelToWorld = mProgram->uniformLocation("modelToWorld");
		u_worldToCamera = mProgram->uniformLocation("worldToCamera");
		u_cameraToView = mProgram->uniformLocation("cameraToView");

		// Create Buffer (Do not release until VAO is created)
		mVertex.create();
		mVertex.bind();
		mVertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
		mVertex.allocate(sg_vertexes, sizeof(sg_vertexes));

		// Create Vertex Array Object
		mObject.create();
		mObject.bind();
		mProgram->enableAttributeArray(0);
		mProgram->enableAttributeArray(1);
		mProgram->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
		mProgram->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());

		// Release (unbind) all
		mObject.release();
		mVertex.release();
		mProgram->release();
	}
}

void Window::resizeGL(int width, int height)
{
	m_projection.setToIdentity();
	m_projection.perspective(45.0f, width / float(height), 0.0f, 1000.0f);
}

void Window::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);

	mProgram->bind();
	mProgram->setUniformValue(u_worldToCamera, m_camera.toMatrix());
	mProgram->setUniformValue(u_cameraToView, m_projection);
	{
		mObject.bind();
		mProgram->setUniformValue(u_modelToWorld, m_transform.toMatrix());
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mObject.release();
	}
	mProgram->release();
}

void Window::teardownGL()
{
	mObject.destroy();
	mVertex.destroy();
	delete mProgram;
}

void Window::keyPressEvent(QKeyEvent* event)
{
	if (event->isAutoRepeat())
	{
		event->ignore();
	}
	else
	{
		Input::registerKeyPress(event->key());
	}
}

void Window::keyReleaseEvent(QKeyEvent* event)
{
	if (event->isAutoRepeat())
	{
		event->ignore();
	}
	else
	{
		Input::registerKeyRelease(event->key());
	}
}

void Window::mousePressEvent(QMouseEvent* event)
{
	Input::registerMousePress(event->button());
}

void Window::mouseReleaseEvent(QMouseEvent* event)
{
	Input::registerMouseRelease(event->button());
}

void Window::wheelEvent(QWheelEvent* event)
{
	QPoint num_degrees = event->angleDelta() / 8;

	if (!num_degrees.isNull())
	{
		auto steps = num_degrees / 15;
		m_camera.translate(0.5f * static_cast<float>(steps.y()) * m_camera.forward());
		update();
	}
}


void Window::update()
{
	// Update input
	Input::update();

	// Camera Transformation
	if (Input::buttonPressed(Qt::LeftButton))
	{
		static const auto transSpeed = 0.5f;
		static const auto rotSpeed = 0.5f;

		// Handle rotations
		// This version of interaction rotates the model (and world) about the camera axes, 
		// resulting in a CAD style interaction, not a fly through camera. 
		// for a fly through camera you would do the following:
		// m_camera.rotate(-rotSpeed * Input::mouseDelta().x(), Camera3D::LocalUp);
		// m_camera.rotate(-rotSpeed * Input::mouseDelta().y(), m_camera.right());
		// What would be interesting is to see if I can create the same effect of a CAD camera by properly 
		// moving the camera instead of the model.
		m_transform.rotate(rotSpeed * Input::mouseDelta().x(), Camera3D::LocalUp);
		m_transform.rotate(rotSpeed * Input::mouseDelta().y(), m_camera.right());

		// Handle translations
		QVector3D translation;
		if (Input::keyPressed(Qt::Key_W))
		{
			translation += m_camera.forward();
		}
		if (Input::keyPressed(Qt::Key_S))
		{
			translation -= m_camera.forward();
		}
		if (Input::keyPressed(Qt::Key_A))
		{
			translation -= m_camera.right();
		}
		if (Input::keyPressed(Qt::Key_D))
		{
			translation += m_camera.right();
		}
		if (Input::keyPressed(Qt::Key_Q))
		{
			translation -= m_camera.up();
		}
		if (Input::keyPressed(Qt::Key_E))
		{
			translation += m_camera.up();
		}
		m_camera.translate(transSpeed * translation);
	}
	else if (Input::buttonPressed(Qt::RightButton))
	{
		//TODO: Add translation using right mouse button (or wheel button)
//		auto current_trans = m_camera.translation();
//		m_camera.translate(current_trans.x() - Input::mouseDelta().x()*0.01f, current_trans.y() - Input::mouseDelta().y()*0.01f, current_trans.z());
	}

	// Schedule a redraw
	QOpenGLWidget::update();
}

void Window::printContextInformation()
{
	QString glType;
	QString glVersion;
	QString glProfile;

	// Get Version Information
	glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
	glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

	// Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
	switch (format().profile())
	{
		CASE(NoProfile);
		CASE(CoreProfile);
		CASE(CompatibilityProfile);
	}
#undef CASE

	// qPrintable() will print our QString w/o quotes around it.
	qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}


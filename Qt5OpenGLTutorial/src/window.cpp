#include "window.h"
#include <QDebug>
#include "vertex.h"
#include <qopenglwindow.h>

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
	m_transform.translate(0.0, 0.0, -5.0f);
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
		u_worldToView = mProgram->uniformLocation("worldToView");

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
	mProgram->setUniformValue(u_worldToView, m_projection);
	mObject.bind();
	mProgram->setUniformValue(u_modelToWorld, m_transform.toMatrix());
	glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
	mObject.release();
	mProgram->release();
}

void Window::teardownGL()
{
	mObject.destroy();
	mVertex.destroy();
	delete mProgram;
}

void Window::update()
{
	// Update instance information
	m_transform.rotate(1.0f, QVector3D(0.4f, 0.3f, 0.3f));

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


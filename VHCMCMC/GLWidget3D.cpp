#include "GLWidget3D.h"
#include "MainWindow.h"
#include <gl/GLU.h>

GLWidget3D::GLWidget3D(MainWindow* mainWin) : QGLWidget(QGLFormat(QGL::SampleBuffers), (QWidget*)mainWin) {
	this->mainWin = mainWin;
}

GLWidget3D::~GLWidget3D() {
}

QSize GLWidget3D::minimumSizeHint() const {
	return QSize(200, 200);
}

QSize GLWidget3D::sizeHint() const {
	return QSize(400, 400);
}

void GLWidget3D::mousePressEvent(QMouseEvent *e) {
	camera.mouseDown(e->x(), e->y());
}

void GLWidget3D::mouseReleaseEvent(QMouseEvent *e) {
	camera.mouseUp();

	updateGL();
}

void GLWidget3D::mouseMoveEvent(QMouseEvent *e) {
	if (e->buttons() & Qt::LeftButton) {
		camera.rotate(e->x(), e->y());
	} else if (e->buttons() & Qt::RightButton) {
		camera.zoom(e->x(), e->y());
	}

	updateGL();
}

void GLWidget3D::initializeGL() {
	//qglClearColor(QColor(113, 112, 117));
	glClearColor(0, 0, 0, 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	static GLfloat lightPosition[4] = {100.0f, 100.0f, 100.0f, 0.0f};
	static GLfloat lightPosition2[4] = {-30.0f, -30.0f, 10.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);	
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

void GLWidget3D::resizeGL(int width, int height) {
	height = height?height:1;

	camera.setWindowSize(width, height);

	glViewport( 0, 0, (GLint)width, (GLint)height );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)width/(GLfloat)height, 0.1f, 10000);
	glMatrixMode(GL_MODELVIEW);
}

void GLWidget3D::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDisable(GL_TEXTURE_2D);*/
	
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -camera.z);
	glMultMatrixd(camera.rt);

	layout.draw();
}



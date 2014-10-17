#include "GLWidget3D.h"
#include "Util.h"
#include "MainWindow.h"
#include <gl/GLU.h>

GLWidget3D::GLWidget3D(QWidget* mainWin) : QGLWidget(QGLFormat(QGL::SampleBuffers), (QWidget*)mainWin) {
	this->mainWin = mainWin;

	camera.resetCamera();

	rotationSensitivity = 0.4f;
	zoomSensitivity = 0.1f;
}

GLWidget3D::~GLWidget3D() {
}

QSize GLWidget3D::minimumSizeHint() const {
	return QSize(200, 200);
}

QSize GLWidget3D::sizeHint() const {
	return QSize(400, 400);
}

void GLWidget3D::mousePressEvent(QMouseEvent *event) {
	QVector2D pos;

	this->setFocus();

	lastPos = event->pos();
	mouseTo2D(event->x(), event->y(), pos);
}

void GLWidget3D::mouseReleaseEvent(QMouseEvent *event) {
	updateGL();
}

void GLWidget3D::mouseMoveEvent(QMouseEvent *event) {
	QVector2D pos;
	mouseTo2D(event->x(), event->y(), pos);

	float dx = (float)(event->x() - lastPos.x());
	float dy = (float)(event->y() - lastPos.y());
	float camElevation = camera.getCamElevation();

	vboRenderManager.mousePos3D=pos.toVector3D();

	if (event->buttons() & Qt::LeftButton) {	// Rotate
		camera.changeXRotation(rotationSensitivity * dy);
		camera.changeZRotation(-rotationSensitivity * dx);    
		updateCamera();
		lastPos = event->pos();
	} else if (event->buttons() & Qt::MidButton) {
		camera.changeXYZTranslation(-dx, dy, 0);
		updateCamera();
		lastPos = event->pos();
	} else if (event->buttons() & Qt::RightButton) {	// Zoom
		camera.changeXYZTranslation(0, 0, -zoomSensitivity * dy);
		updateCamera();
		lastPos = event->pos();
	}

	updateGL();
}

void GLWidget3D::initializeGL() {

	//qglClearColor(QColor(113, 112, 117));
	qglClearColor(QColor(0, 0, 0));

	////////////////////////////////////////
	//---- GLEW extensions ----
	GLenum err = glewInit();
	if (GLEW_OK != err){// Problem: glewInit failed, something is seriously wrong.
		qDebug() << "Error: " << glewGetErrorString(err);
	}
	qDebug() << "Status: Using GLEW " << glewGetString(GLEW_VERSION);
	if (glewIsSupported("GL_VERSION_4_2"))
		printf("Ready for OpenGL 4.2\n");
	else {
		printf("OpenGL 4.2 not supported\n");
		//exit(1);
	}
	const GLubyte* text = glGetString(GL_VERSION);
	printf("VERSION: %s\n",text);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	///
	vboRenderManager.init();
	updateCamera();
	shadow.initShadow(vboRenderManager.program,this);
	glUniform1i(glGetUniformLocation(vboRenderManager.program,"shadowState"), 1);
}

void GLWidget3D::resizeGL(int width, int height) {
	updateCamera();
}

void GLWidget3D::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDisable(GL_TEXTURE_2D);
	
	// NOTE: camera transformation is not necessary here since the updateCamera updates the uniforms each time they are changed

	drawScene(0);		
}

void GLWidget3D::drawScene(int drawMode) {
	if (drawMode == 0) {
		shadow.makeShadowMap(this);

		glUniform1i(glGetUniformLocation(vboRenderManager.program,"shadowState"), 1);

		layout.draw(vboRenderManager);

		glEnable(GL_CULL_FACE);
		vboRenderManager.renderStaticGeometry("layout");
		glDisable(GL_CULL_FACE);
		vboRenderManager.renderModels("furniture");
	} else if (drawMode == 1) { // compute shadow map
		glUniform1i(glGetUniformLocation(vboRenderManager.program,"shadowState"), 2);

		glEnable(GL_CULL_FACE);
		vboRenderManager.renderStaticGeometry(QString("layout"));
		glDisable(GL_CULL_FACE);
		vboRenderManager.renderModels("furniture");
	}
}

/**
 * Convert the screen space coordinate (x, y) to the model space coordinate.
 */
void GLWidget3D::mouseTo2D(int x,int y, QVector2D &result) {
	updateCamera();
	updateGL();
	GLint viewport[4];

	// retrieve the matrices
	glGetIntegerv(GL_VIEWPORT, viewport);

	// retrieve the projected z-buffer of the origin
	GLfloat winX,winY,winZ;
	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	/*glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
	GLdouble posX, posY, posZ;
	gluUnProject( winX, winY, winZ, camera->mvMatrix.data(), camera->pMatrix.data(), viewport, &posX, &posY, &posZ);
	// unproject the image plane coordinate to the model space
	
	
		float znear=10.0f,zFar= 10.0f*2000.0f;
		
			GLdouble posXFar, posYFar, posZFar;
			gluUnProject( winX, winY, zFar, camera->mvMatrix.data(), camera->pMatrix.data(), viewport, &posXFar, &posYFar, &posZFar);
			QVector3D rayStar(posX,posY,posZ);
			QVector3D rayEnd(posXFar,posYFar,posZFar);
			double t;
			QVector3D q1(0,0,1.0f);
			QVector3D q2(0,0,0);
			QVector3D result3D;
			printf("mouse %d %d win %f %f z1 %f z2 %f Pos %f %f %f PosF %f %f %f\n",x,y,winX,winY,winZ,zFar,posX,posY,posZ,posXFar,posYFar,posZFar);
			if(Util::planeIntersectWithLine(rayStar,rayEnd,q1,q2,t,result3D)!=0){
				result->setX(result3D.x());
				result->setY(result3D.y());
			}else{
				printf("fail hit\n");
			}
			//return;
	
	result->setX(posX);
	result->setY(posY);*/
	GLdouble wx, wy, wz;  /*  returned world x, y, z coords  */
	GLdouble wx2, wy2, wz2;  /*  returned world x, y, z coords  */
	gluUnProject( winX, winY, 0.0f, camera.mvMatrix.data(), camera.pMatrix.data(), viewport, &wx, &wy, &wz);
	gluUnProject( winX, winY, 1.0f, camera.mvMatrix.data(), camera.pMatrix.data(), viewport, &wx2, &wy2, &wz2);
	double f = wz / ( wz2 - wz );
	double x2d = wx - f * (wx2 - wx );
	double y2d = wy - f * (wy2 - wy );	
	result.setX(x2d);
	result.setY(y2d);
	//printf("Mouse %d %d\n",x,y);
}

// this method should be called after any camera transformation (perspective or modelview)
// it will update viewport, perspective, view matrix, and update the uniforms
void GLWidget3D::updateCamera(){
	// update matrices
	int height = this->height() ? this->height() : 1;
	glViewport(0, 0, (GLint)this->width(), (GLint)this->height());
	camera.updatePerspective(this->width(),height);
	camera.updateCamMatrix();

	// update uniforms
	float mvpMatrixArray[16];
	float mvMatrixArray[16];

	for(int i=0;i<16;i++){
		mvpMatrixArray[i]=camera.mvpMatrix.data()[i];
		mvMatrixArray[i]=camera.mvMatrix.data()[i];	
	}
	float normMatrixArray[9];
	for(int i=0;i<9;i++){
		normMatrixArray[i]=camera.normalMatrix.data()[i];
	}

	//glUniformMatrix4fv(mvpMatrixLoc,  1, false, mvpMatrixArray);
	glUniformMatrix4fv(glGetUniformLocation(vboRenderManager.program, "mvpMatrix"),  1, false, mvpMatrixArray);
	glUniformMatrix4fv(glGetUniformLocation(vboRenderManager.program, "mvMatrix"),  1, false, mvMatrixArray);
	glUniformMatrix3fv(glGetUniformLocation(vboRenderManager.program, "normalMatrix"),  1, false, normMatrixArray);

	// light poss
	QVector3D light_dir(-0.40f,0.81f,-0.51f);
	glUniform3f(glGetUniformLocation(vboRenderManager.program, "lightDir"),light_dir.x(),light_dir.y(),light_dir.z());
}//

void GLWidget3D::setLayout(Layout layout)
{
	this->layout = layout;
}

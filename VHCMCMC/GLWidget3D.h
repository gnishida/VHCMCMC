#pragma once

#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include "Camera.h"
#include "Layout.h"

class MainWindow;

class GLWidget3D : public QGLWidget {
public:
	MainWindow* mainWin;
	Camera camera;
	Layout layout;

public:
	GLWidget3D(MainWindow *parent);
	~GLWidget3D();

	QSize minimumSizeHint() const;
	QSize sizeHint() const;

	void mouseTo2D(int x, int y, QVector2D &result);

	void drawScene();


protected:
	void initializeGL();

	void resizeGL(int width, int height);
	void paintGL();    

	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);



};


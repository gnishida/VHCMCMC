#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "ui_MainWindow.h"
#include "GLWidget3D.h"
#include "MCMC.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();

protected:
	void keyPressEvent(QKeyEvent* e);
	void keyReleaseEvent(QKeyEvent* e);
	
public slots:

private:
	Ui::MainWindowClass ui;
	GLWidget3D* glWidget1;
	GLWidget3D* glWidget2;
	MCMC mcmc;
};

#endif // MAINWINDOW_H

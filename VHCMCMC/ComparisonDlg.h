#pragma once

#include <QDockWidget>
#include "ui_ComparisonDlg.h"
#include "GLWidget3D.h"

class MainWindow;

class ComparisonDlg : public QDockWidget {
Q_OBJECT

public:
	Ui::ComparisonDlg ui;
	ComparisonDlg(MainWindow* mainWin);

public slots:

private:
	MainWindow* mainWin;
	GLWidget3D* glWidget;
};


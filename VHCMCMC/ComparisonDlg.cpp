#include "ComparisonDlg.h"
#include "MainWindow.h"

ComparisonDlg::ComparisonDlg(MainWindow* mainWin) : QDockWidget("Comparison", (QWidget*)mainWin) {
	this->mainWin = mainWin;

	// set up the UI
	ui.setupUi(this);

	// setup the GL widget
	glWidget = new GLWidget3D(this);
	setCentralWidget(glWidget);
}

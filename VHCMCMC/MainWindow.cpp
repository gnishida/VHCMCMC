#include "MainWindow.h"
#include "Layout.h"
#include "HumanComputationEmulator.h"
#include "GLWidget3D.h"
#include <random>
#include <QHBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	// setup the dialog
	//comparisonDlg = new ComparisonDlg(this);

	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui.actionStart, SIGNAL(triggered()), this, SLOT(onStart()));

	//QVBoxLayout* layout = new QVBoxLayout(this);

	// setup the GL widget
	//glWidget = new GLWidget3D(layout);
	//glWidget->setGeometry(50,50,300,300);
	//setCentralWidget(glWidget);

	//comparisonDlg->show();



	QWidget *central = new QWidget(this); // a central widget
	glWidget1 = new GLWidget3D((QWidget*)this);
	//glWidget->setFrameStyle(QFrame::Box | QFrame::Plain);
	glWidget2 = new GLWidget3D((QWidget*)this);
	//QLabel *widget2 = new QLabel("two widget", this);
	//widget2->setFrameStyle(QFrame::Box | QFrame::Plain);

	QHBoxLayout *layout = new QHBoxLayout(central);
	layout->addWidget(glWidget1);
	layout->addWidget(glWidget2);

	central->setLayout(layout);
	setCentralWidget(central); // you were missing this
}

MainWindow::~MainWindow()
{
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
	switch( e->key() ){
	case Qt::Key_Left:
		printf("Left\n");
		break;
	case Qt::Key_Right:
		printf("Right\n");
		break;
	}
}

void MainWindow::keyReleaseEvent(QKeyEvent* e)
{
}

void MainWindow::onStart()
{
	/*
	std::mt19937 mtengine;
	std::uniform_real_distribution<double> distribution(0.0,1.0);

	HumanComputationEmulator HC(20);
	//GradientDescent gd;

	// initialize the layout
	Layout layout;

	// start MCMC steps
	for (int iter = 0; iter < 10000; ++iter) {
		// make a proposal
		Layout layout2 = layout.proposeChange(layout.width * 0.1, layout.depth * 0.1, 0.314);

		cv::Mat feature1 = layout.feature();
		cv::Mat feature2 = layout2.feature();

		// do HC
		std::vector<bool> votes = HC.run(feature1, feature2);

		// estimate feature vectors
		//gd.solve(feature1, feature2, votes);

		// accept or reject
		layout = layout2;
	}
	*/
}


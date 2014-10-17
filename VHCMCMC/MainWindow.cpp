#include "MainWindow.h"
#include "Layout.h"
#include "HumanComputationEmulator.h"
#include "GLWidget3D.h"
#include <random>
#include <QHBoxLayout>
#include <QLabel>
#include <QDir>

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));

	// setup the GL widget	
	QWidget *central = new QWidget(this); // a central widget
	glWidget1 = new GLWidget3D((QWidget*)this);
	glWidget1->setLayout(mcmc.layout);
	glWidget2 = new GLWidget3D((QWidget*)this);
	glWidget2->setLayout(mcmc.proposedLayout);

	// set up the layout
	QHBoxLayout *layout = new QHBoxLayout(central);
	layout->addWidget(glWidget1);
	layout->addWidget(glWidget2);
	central->setLayout(layout);
	setCentralWidget(central);
}

MainWindow::~MainWindow()
{
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
	if (!QDir("samples").exists()) QDir().mkdir("samples");
	QString fileName = "samples/" + QString::number(mcmc.step) + ".png";

	switch (e->key()) {
	case Qt::Key_Left:
		printf("Left\n");

		glWidget1->grabFrameBuffer().save(fileName);

		mcmc.reject();
		mcmc.generateProposal();
		glWidget2->setLayout(mcmc.proposedLayout);
		glWidget2->updateGL();

		break;
	case Qt::Key_Right:
		printf("Right\n");

		glWidget2->grabFrameBuffer().save(fileName);

		mcmc.accept();
		mcmc.generateProposal();
		glWidget1->setLayout(mcmc.layout);
		glWidget1->updateGL();
		glWidget2->setLayout(mcmc.proposedLayout);
		glWidget2->updateGL();

		break;
	}
}

void MainWindow::keyReleaseEvent(QKeyEvent* e)
{
}



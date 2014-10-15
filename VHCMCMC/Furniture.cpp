#include "Furniture.h"
#include <QGLWidget>

void Furniture::draw()
{
	glTranslatef(x, y, 0.0);
	glRotatef(theta / 3.14159265 * 360, 0, 0, 1);

	if (type == 0) {
		drawDiningTableChair();
	} else if (type == 1) {
		drawBookShelf();
	} else if (type == 2) {
		drawLamp();
	}
}

void Furniture::drawDiningTableChair()
{
	drawDiningTable();

	glPushMatrix();
	glTranslatef(- width * 0.25, - depth * 0.25, 0.0);
	glRotatef(90, 0, 0, 1);
	drawDiningChair();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(width * 0.25, - depth * 0.25, 0.0);
	glRotatef(90, 0, 0, 1);
	drawDiningChair();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-width * 0.25, depth * 0.25, 0.0);
	glRotatef(-90, 0, 0, 1);
	drawDiningChair();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(width * 0.25, depth * 0.25, 0.0);
	glRotatef(-90, 0, 0, 1);
	drawDiningChair();
	glPopMatrix();
}

void Furniture::drawDiningTable()
{
	float d = depth * 0.5;
	float h = height * 0.65;

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.9f, 0.7f);

	glNormal3f(0, -1, 0);
	glVertex3f(- width * 0.5, - d * 0.5, 0.0);
	glVertex3f(- width * 0.5 + 0.1, - d * 0.5, 0.0f);
	glVertex3f(- width * 0.5 + 0.1, - d * 0.5, h);
	glVertex3f(- width * 0.5, - d * 0.5, h);

	glNormal3f(0, -1, 0);
	glVertex3f(width * 0.5 - 0.1, - d * 0.5, 0.0);
	glVertex3f(width * 0.5, - d * 0.5, 0.0f);
	glVertex3f(width * 0.5, - d * 0.5, h);
	glVertex3f(width * 0.5 - 0.1, - d * 0.5, h);


	glNormal3f(0, 1, 0);
	glVertex3f(- width * 0.5 + 0.1, d * 0.5, 0);
	glVertex3f(- width * 0.5, d * 0.5, 0);
	glVertex3f(- width * 0.5, d * 0.5, h);
	glVertex3f(- width * 0.5 + 0.1, d * 0.5, h);

	glNormal3f(0, 1, 0);
	glVertex3f(width * 0.5, d * 0.5, 0);
	glVertex3f(width * 0.5 - 0.1, d * 0.5, 0);
	glVertex3f(width * 0.5 - 0.1, d * 0.5, h);
	glVertex3f(width * 0.5, d * 0.5, h);


	glNormal3f(0, 0, 1);
	glVertex3f(- width * 0.5, - d * 0.5, h);
	glVertex3f(width * 0.5, - d * 0.5, h);
	glVertex3f(width * 0.5, d * 0.5, h);
	glVertex3f(- width * 0.5, d * 0.5, h);

	glEnd();
}

void Furniture::drawDiningChair()
{
	float w = width * 0.25;
	float d = depth * 0.25;

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.5f, 1.0f);

	glNormal3f(1, 0, 0);
	glVertex3f(w * 0.5, - d * 0.5, 0.0);
	glVertex3f(w * 0.5, d * 0.5, 0.0f);
	glVertex3f(w * 0.5, d * 0.5, height * 0.5);
	glVertex3f(w * 0.5, - d * 0.5, height * 0.5);

	glNormal3f(0, 0, 1);
	glVertex3f(- w * 0.5, -d * 0.5, height * 0.5);
	glVertex3f(w * 0.5, -d * 0.5, height * 0.5);
	glVertex3f(w * 0.5, d * 0.5, height * 0.5);
	glVertex3f(- w * 0.5, d * 0.5, height * 0.5);

	glNormal3f(1, 0, 0);
	glVertex3f(- w * 0.5, -d * 0.5, 0);
	glVertex3f(- w * 0.5, d * 0.5, 0);
	glVertex3f(- w * 0.5, d * 0.5, height);
	glVertex3f(- w * 0.5, -d * 0.5, height);

	glEnd();
}

void Furniture::drawBookShelf()
{
	int num = height / 0.3;

	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.8f, 0.2f);

	glNormal3f(0, -1, 0);
	glVertex3f(-width * 0.5, -depth * 0.5, 0.0);
	glVertex3f(width * 0.5, -depth * 0.5, 0.0f);
	glVertex3f(width * 0.5, -depth * 0.5, height);
	glVertex3f(-width * 0.5, -depth * 0.5, height);

	glNormal3f(0, 1, 0);
	glVertex3f(width * 0.5, depth * 0.5, 0.0);
	glVertex3f(-width * 0.5, depth * 0.5, 0.0f);
	glVertex3f(-width * 0.5, depth * 0.5, height);
	glVertex3f(width * 0.5, depth * 0.5, height);

	glNormal3f(-1, 0, 0);
	glVertex3f(-width * 0.5, depth * 0.5, 0.0);
	glVertex3f(-width * 0.5, -depth * 0.5, 0.0f);
	glVertex3f(-width * 0.5, -depth * 0.5, height);
	glVertex3f(-width * 0.5, depth * 0.5, height);

	for (int i = 1; i < num; ++i) {
		glNormal3f(0, 0, 1);
		glVertex3f(-width * 0.5, -depth * 0.5, i * 0.3);
		glVertex3f(width * 0.5, -depth * 0.5, i * 0.3);
		glVertex3f(width * 0.5, depth * 0.5, i * 0.3);
		glVertex3f(-width * 0.5, depth * 0.5, i * 0.3);
	}

	glNormal3f(0, 0, 1);
	glVertex3f(-width * 0.5, -depth * 0.5, height);
	glVertex3f(width * 0.5, -depth * 0.5, height);
	glVertex3f(width * 0.5, depth * 0.5, height);
	glVertex3f(-width * 0.5, depth * 0.5, height);

	glEnd();
}

void Furniture::drawLamp()
{
	float w = 0.05;
	float d = 0.05;

	glBegin(GL_QUADS);
	glColor3f(0.8f, 0.9f, 1.0f);

	// lamp pole
	glNormal3f(0, -1, 0);
	glVertex3f(-w * 0.5, -d * 0.5, 0.0);
	glVertex3f(w * 0.5, -d * 0.5, 0.0f);
	glVertex3f(w * 0.5, -d * 0.5, height);
	glVertex3f(-w * 0.5, -d * 0.5, height);

	glNormal3f(1, 0, 0);
	glVertex3f(w * 0.5, -d * 0.5, 0.0);
	glVertex3f(w * 0.5, d * 0.5, 0.0f);
	glVertex3f(w * 0.5, d * 0.5, height);
	glVertex3f(w * 0.5, -d * 0.5, height);

	glNormal3f(0, 1, 0);
	glVertex3f(w * 0.5, d * 0.5, 0.0);
	glVertex3f(-w * 0.5, d * 0.5, 0.0f);
	glVertex3f(-w * 0.5, d * 0.5, height);
	glVertex3f(w * 0.5, d * 0.5, height);

	glNormal3f(-1, 0, 0);
	glVertex3f(-w * 0.5, d * 0.5, 0.0);
	glVertex3f(-w * 0.5, -d * 0.5, 0.0f);
	glVertex3f(-w * 0.5, -d * 0.5, height);
	glVertex3f(-w * 0.5, d * 0.5, height);


	// lamp shade
	glColor3f(1.0f, 1.0f, 0.6f);
	glNormal3f(0, -1, 0);
	glVertex3f(-width * 0.5, -depth * 0.5, height * 0.8);
	glVertex3f(width * 0.5, -depth * 0.5, height * 0.8);
	glVertex3f(width * 0.5, -depth * 0.5, height);
	glVertex3f(-width * 0.5, -depth * 0.5, height);

	glNormal3f(1, 0, 0);
	glVertex3f(width * 0.5, -depth * 0.5, height * 0.8);
	glVertex3f(width * 0.5, depth * 0.5, height * 0.8);
	glVertex3f(width * 0.5, depth * 0.5, height);
	glVertex3f(width * 0.5, -depth * 0.5, height);

	glNormal3f(0, 1, 0);
	glVertex3f(width * 0.5, depth * 0.5, height * 0.8);
	glVertex3f(-width * 0.5, depth * 0.5, height * 0.8);
	glVertex3f(-width * 0.5, depth * 0.5, height);
	glVertex3f(width * 0.5, depth * 0.5, height);

	glNormal3f(-1, 0, 0);
	glVertex3f(-width * 0.5, depth * 0.5, height * 0.8);
	glVertex3f(-width * 0.5, -depth * 0.5, height * 0.8);
	glVertex3f(-width * 0.5, -depth * 0.5, height);
	glVertex3f(-width * 0.5, depth * 0.5, height);

	glNormal3f(0, 0, 1);
	glVertex3f(-width * 0.5, -depth * 0.5, height);
	glVertex3f(width * 0.5, -depth * 0.5, height);
	glVertex3f(width * 0.5, depth * 0.5, height);
	glVertex3f(-width * 0.5, depth * 0.5, height);

	glEnd();
}

Polygon2D Furniture::footprint()
{
	Polygon2D line;
	line.push_back(QVector2D(x-width * 0.5, y-depth * 0.5));
	line.push_back(QVector2D(x+width * 0.5, y-depth * 0.5));
	line.push_back(QVector2D(x+width * 0.5, y+depth * 0.5));
	line.push_back(QVector2D(x-width * 0.5, y+depth * 0.5));
	line.push_back(QVector2D(x-width * 0.5, y-depth * 0.5));

	line.rotate(theta / 3.14159265 * 360, QVector2D(x, y));

	return line;
}


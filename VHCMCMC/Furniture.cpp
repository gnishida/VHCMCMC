#include "Furniture.h"
#include <QGLWidget>
#include "VBOModel.h"
#include "Util.h"

Furniture::Furniture(int type, float x, float y, float z, float theta) : type(type), x(x), y(y), z(z), theta(theta)
{
	if (type == TYPE_DININGTABLE) { // table
		width = 2.0;
		depth = 2.0;
		height = 2.0;
		_footprint.push_back(QVector2D(x-width * 0.5, y-depth * 0.5));
		_footprint.push_back(QVector2D(x+width * 0.5, y-depth * 0.5));
		_footprint.push_back(QVector2D(x+width * 0.5, y+depth * 0.5));
		_footprint.push_back(QVector2D(x-width * 0.5, y+depth * 0.5));
		_footprint.push_back(QVector2D(x-width * 0.5, y-depth * 0.5));
	} else if (type == TYPE_BOOKSHELF) { // book shelf
		width = 1.0;
		depth = 0.4;
		height = 1.6;
		_footprint.push_back(QVector2D(x-width * 0.5, y-depth * 0.5));
		_footprint.push_back(QVector2D(x+width * 0.5, y-depth * 0.5));
		_footprint.push_back(QVector2D(x+width * 0.5, y+depth * 0.5));
		_footprint.push_back(QVector2D(x-width * 0.5, y+depth * 0.5));
		_footprint.push_back(QVector2D(x-width * 0.5, y-depth * 0.5));
	} else if (type == TYPE_SOFATABLE) { // sofa
		width = 3.0;
		depth = 3.0;
		height = 0.75;
		_footprint.push_back(QVector2D(x-width * 0.5, y-depth * 0.5));
		_footprint.push_back(QVector2D(x+width * 0.5, y-depth * 0.5));
		_footprint.push_back(QVector2D(x+width * 0.5, y+depth * 0.5));
		_footprint.push_back(QVector2D(x-width * 0.5, y+depth * 0.5));
		_footprint.push_back(QVector2D(x-width * 0.5, y-depth * 0.5));
	} else if (type == TYPE_LAMP) { // lamp
		width = 0.5;
		depth = 0.5;
		height = 1.6;
		_footprint.push_back(QVector2D(x-width * 0.5, y-depth * 0.5));
		_footprint.push_back(QVector2D(x+width * 0.5, y-depth * 0.5));
		_footprint.push_back(QVector2D(x+width * 0.5, y+depth * 0.5));
		_footprint.push_back(QVector2D(x-width * 0.5, y+depth * 0.5));
		_footprint.push_back(QVector2D(x-width * 0.5, y-depth * 0.5));
	}
}

void Furniture::draw(VBORenderManager& rendManager)
{
	if (type == TYPE_DININGTABLE) {
		drawDiningTableChair(rendManager);
	} else if (type == TYPE_BOOKSHELF) {
		drawBookShelf(rendManager);
	} else if (type == TYPE_SOFATABLE) {
		drawSofa(rendManager);
	} else if (type == TYPE_LAMP) {
		drawLamp(rendManager);
	}
}

void Furniture::drawDiningTableChair(VBORenderManager& rendManager)
{
	ModelSpec spec;

	spec.transMatrix.setToIdentity();
	spec.transMatrix.translate(QVector3D(x, y, 0));
	spec.transMatrix.rotate(Util::rad2deg(theta), 0.0f, 0.0f, 1.0f);
	spec.transMatrix.rotate(180, 0, 0, 1);
	spec.transMatrix.rotate(90, 1, 0, 0);
	spec.colors.resize(1);

	spec.colors[0]=QVector3D(0.1f, 0.33f, 0.2f);
	spec.type = TYPE_DININGTABLE;

	rendManager.addModel("furniture", spec);
}

void Furniture::drawBookShelf(VBORenderManager& rendManager)
{
	ModelSpec spec;

	spec.transMatrix.setToIdentity();
	spec.transMatrix.translate(QVector3D(x, y, 0));
	spec.transMatrix.rotate(Util::rad2deg(theta), 0.0f, 0.0f, 1.0f);
	spec.transMatrix.rotate(180, 0, 0, 1);
	spec.transMatrix.rotate(90, 1, 0, 0);
	spec.colors.resize(1);

	spec.colors[0] = QVector3D(0.4f, 0.53f, 0.2f);
	spec.type = TYPE_BOOKSHELF;

	rendManager.addModel("furniture", spec);
}

void Furniture::drawSofa(VBORenderManager& rendManager)
{
	ModelSpec spec;

	spec.transMatrix.setToIdentity();
	spec.transMatrix.translate(QVector3D(x, y, 0));
	spec.transMatrix.rotate(Util::rad2deg(theta), 0.0f, 0.0f, 1.0f);
	spec.colors.resize(1);

	spec.colors[0] = QVector3D(0.3f, 0.3f, 0.3f);
	spec.type = TYPE_SOFATABLE;

	rendManager.addModel("furniture", spec);
}

void Furniture::drawLamp(VBORenderManager& rendManager)
{
	ModelSpec spec;

	spec.transMatrix.setToIdentity();
	spec.transMatrix.translate(QVector3D(x, y, 0));
	spec.transMatrix.rotate(Util::rad2deg(theta), 0.0f, 0.0f, 1.0f);
	spec.colors.resize(1);

	spec.colors[0] = QVector3D(1.0f, 1.0f, 0.3f);
	spec.type = TYPE_LAMP;

	rendManager.addModel("furniture", spec);
}

void Furniture::drawPicture(VBORenderManager& rendManager)
{
	std::vector<Vertex> verts;
	verts.push_back(Vertex(x-width*0.5, y+depth, z-height*0.5, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f));
	verts.push_back(Vertex(x+width*0.5, y+depth, z-height*0.5, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f));
	verts.push_back(Vertex(x+width*0.5, y+depth, z+height*0.5, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f));
	verts.push_back(Vertex(x-width*0.5, y+depth, z+height*0.5, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f));	
	rendManager.addStaticGeometry("layout", verts, "../data/textures/picture.jpg", GL_QUADS, 2);// texture && lighting
}

Polygon2D Furniture::footprint()
{
	Polygon2D line = _footprint;
	//_footprint.translate(-x, -y, line);
	line.rotate(Util::rad2deg(theta), QVector2D(x, y));
	//line.translate(x, y);

	return line;
}


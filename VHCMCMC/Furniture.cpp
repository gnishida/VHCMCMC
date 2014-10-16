#include "Furniture.h"
#include <QGLWidget>
#include "VBOModel.h"

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
	} else if (type == TYPE_SOFA) { // sofa
		width = 2.4;
		depth = 0.7;
		height = 0.75;
		_footprint.push_back(QVector2D(x-width * 0.5, y-depth * 0.5));
		_footprint.push_back(QVector2D(x+width * 0.5, y-depth * 0.5));
		_footprint.push_back(QVector2D(x+width * 0.5, y+depth * 0.5));
		_footprint.push_back(QVector2D(x-width * 0.5, y+depth * 0.5));
		_footprint.push_back(QVector2D(x-width * 0.5, y-depth * 0.5));
	} else if (type == TYPE_SMALLSOFA) { // small sofa
		width = 1.0;
		depth = 0.7;
		height = 0.75;
		_footprint.push_back(QVector2D(x-width * 0.5, y-depth * 0.5));
		_footprint.push_back(QVector2D(x+width * 0.5, y-depth * 0.5));
		_footprint.push_back(QVector2D(x+width * 0.5, y+depth * 0.5));
		_footprint.push_back(QVector2D(x-width * 0.5, y+depth * 0.5));
		_footprint.push_back(QVector2D(x-width * 0.5, y-depth * 0.5));
	} else if (type == TYPE_TABLE) { // table
		width = 1.8;
		depth = 1.0;
		height = 0.3;
		_footprint.push_back(QVector2D(x-width * 0.5, y-depth * 0.5));
		_footprint.push_back(QVector2D(x+width * 0.5, y-depth * 0.5));
		_footprint.push_back(QVector2D(x+width * 0.5, y+depth * 0.5));
		_footprint.push_back(QVector2D(x-width * 0.5, y+depth * 0.5));
		_footprint.push_back(QVector2D(x-width * 0.5, y-depth * 0.5));
	} else if (type == TYPE_TREE) { // tree
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
	} else if (type == TYPE_SOFA) {
		drawSofa(rendManager);
	} else if (type == TYPE_SMALLSOFA) {
		drawSmallSofa(rendManager);
	} else if (type == TYPE_TABLE) {
		drawTable(rendManager);
	} else if (type == TYPE_TREE) {
		drawTree(rendManager);
	}
}

void Furniture::drawDiningTableChair(VBORenderManager& rendManager)
{
	ModelSpec spec;

	spec.transMatrix.setToIdentity();
	spec.transMatrix.translate(QVector3D(x, y, 0));
	spec.transMatrix.rotate(theta * 360.0f / 3.1415926535, 0.0f, 0.0f, 1.0f);
	spec.transMatrix.rotate(180, 0, 0, 1);
	spec.transMatrix.rotate(90, 1, 0, 0);
	spec.colors.resize(1);

	spec.colors[0]=QVector3D(0.1f, 0.33f, 0.2f);
	spec.type = TYPE_DININGTABLE;

	rendManager.addStreetElementModel("furniture", spec);
}

void Furniture::drawBookShelf(VBORenderManager& rendManager)
{
	ModelSpec spec;

	spec.transMatrix.setToIdentity();
	spec.transMatrix.translate(QVector3D(x, y, 0));
	spec.transMatrix.rotate(theta * 360.0f / 3.1415926535, 0.0f, 0.0f, 1.0f);
	spec.transMatrix.rotate(180, 0, 0, 1);
	spec.transMatrix.rotate(90, 1, 0, 0);
	spec.colors.resize(1);

	spec.colors[0] = QVector3D(0.4f, 0.53f, 0.2f);
	spec.type = TYPE_BOOKSHELF;

	rendManager.addStreetElementModel("furniture", spec);
}

void Furniture::drawSofa(VBORenderManager& rendManager)
{
	ModelSpec spec;

	spec.transMatrix.setToIdentity();
	spec.transMatrix.translate(QVector3D(x, y, 0));
	spec.transMatrix.rotate(theta * 360.0f / 3.1415926535, 0.0f, 0.0f, 1.0f);
	spec.transMatrix.rotate(180, 0, 0, 1);
	spec.transMatrix.rotate(90, 1, 0, 0);
	spec.colors.resize(1);

	spec.colors[0] = QVector3D(0.92f, 1.0f, 1.0f);
	spec.type = TYPE_SOFA;

	rendManager.addStreetElementModel("furniture", spec);
}

void Furniture::drawSmallSofa(VBORenderManager& rendManager)
{
	ModelSpec spec;

	spec.transMatrix.setToIdentity();
	spec.transMatrix.translate(QVector3D(x, y, 0));
	spec.transMatrix.rotate(theta * 360.0f / 3.1415926535, 0.0f, 0.0f, 1.0f);
	spec.transMatrix.rotate(180, 0, 0, 1);
	spec.transMatrix.rotate(90, 1, 0, 0);
	spec.colors.resize(1);

	spec.colors[0] = QVector3D(0.92f, 1.0f, 1.0f);
	spec.type = TYPE_SMALLSOFA;

	rendManager.addStreetElementModel("furniture", spec);
}

void Furniture::drawTable(VBORenderManager& rendManager)
{
	ModelSpec spec;

	spec.transMatrix.setToIdentity();
	spec.transMatrix.translate(QVector3D(x, y, 0));
	spec.transMatrix.rotate(theta * 360.0f / 3.1415926535, 0.0f, 0.0f, 1.0f);
	spec.transMatrix.rotate(180, 0, 0, 1);
	spec.transMatrix.rotate(90, 1, 0, 0);
	spec.colors.resize(1);

	spec.colors[0] = QVector3D(0.35f, 0.3f, 0.1f);
	spec.type = TYPE_TABLE;

	rendManager.addStreetElementModel("furniture", spec);
}

void Furniture::drawTree(VBORenderManager& rendManager)
{
	ModelSpec spec;

	spec.transMatrix.setToIdentity();
	spec.transMatrix.translate(QVector3D(x, y, 0));
	spec.transMatrix.rotate(theta * 360.0f / 3.1415926535, 0.0f, 0.0f, 1.0f);
	spec.colors.resize(2);

	//trunk
	spec.colors[1]=QVector3D(0.27f,0.22f,0.22f);
	spec.colors[1]=spec.colors[1]+QVector3D(1.0,1.0,1.0f)*((0.2f*qrand())/RAND_MAX-0.1f);
	//leaves
	int treeColor=qrand()%100;
	int desvLeaf=qrand()%40;

	if(treeColor>=0&&treeColor<=46)
		spec.colors[0]=QVector3D(115-desvLeaf,169-desvLeaf,102-desvLeaf);//green to dark 
	if(treeColor>=47&&treeColor<=92)
		spec.colors[0]=QVector3D(69-desvLeaf/2.0f,109-desvLeaf/2.0f,72-desvLeaf/2.0f);//green to dark 
	if(treeColor>=93&&treeColor<=94)
		spec.colors[0]=QVector3D(155-desvLeaf/3.0f,124-desvLeaf/3.0f,24-desvLeaf/3.0f);//yellow to dark 

	if(treeColor>=95&&treeColor<=96)
		spec.colors[0]=QVector3D(96-desvLeaf/4.0f,25-desvLeaf/4.0f,33-desvLeaf/4.0f);//red to dark 

	if(treeColor>=97&&treeColor<=100)
		spec.colors[0]=QVector3D(97-desvLeaf/2.0f,69-desvLeaf/2.0f,58-desvLeaf/2.0f);//grey to dark 
	spec.colors[0] /= 255.0f;
	spec.type = TYPE_TREE;

	rendManager.addStreetElementModel("furniture", spec);
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
	line.rotate(theta / 3.14159265 * 180, QVector2D(x, y));
	//line.translate(x, y);

	return line;
}


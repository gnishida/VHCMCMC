#include "VBOModelManager.h"
#include "VBORenderManager.h"

void VBOModelManager::clearModels(){
	//destroy models
	for (int mN = 0; mN < models.size(); mN++) {
		models[mN].clearModel();
	}
	models.clear();
}

void VBOModelManager::initModels(){
	printf("initStreetElements...\n");

	// init models
	VBOModel m;
	std::vector<QString> fileNames;
	int ind;
		
	// table chair
	ind=models.size();
	models.push_back(m);
	fileNames.clear();
	fileNames.push_back("../data/models/tablechair.obj");
	models[ind].initModel(fileNames);
	models[ind].initScale(1.0f);
	models[ind].loadModel();

	// bookshelf
	ind=models.size();
	models.push_back(m);
	fileNames.clear();
	fileNames.push_back("../data/models/bookshelf.obj");
	models[ind].initModel(fileNames);
	models[ind].initScale(1.0f);
	models[ind].loadModel();

	// sofa
	ind=models.size();
	models.push_back(m);
	fileNames.clear();
	fileNames.push_back("../data/models/sofa.obj");
	models[ind].initModel(fileNames);
	models[ind].initScale(1.0f);
	models[ind].loadModel();

	// small sofa
	ind=models.size();
	models.push_back(m);
	fileNames.clear();
	fileNames.push_back("../data/models/small_sofa.obj");
	models[ind].initModel(fileNames);
	models[ind].initScale(1.0f);
	models[ind].loadModel();

	// table
	ind=models.size();
	models.push_back(m);
	fileNames.clear();
	fileNames.push_back("../data/models/table.obj");
	models[ind].initModel(fileNames);
	models[ind].initScale(1.0f);
	models[ind].loadModel();

	// tree
	ind=models.size();
	models.push_back(m);
	fileNames.clear();
	fileNames.push_back("../data/models/nacho_leaves2.obj");
	fileNames.push_back("../data/models/nacho_trunk2.obj");
	models[ind].initModel(fileNames);
	models[ind].initScale(0.0056f);
	models[ind].loadModel();

	initialized = true;
}

void VBOModelManager::renderOneModel(int programId, ModelSpec& treeStr) {
	if (!initialized) {
		initModels();
	}
	glCullFace(GL_FRONT);
	glUniform1i (glGetUniformLocation (programId, "mode"), 5|mode_Lighting);//model obj: one color

	models[treeStr.type].renderModel(programId, treeStr);
		
	glCullFace(GL_BACK);
	VBOUtil::check_gl_error("RenderOneModel");
}

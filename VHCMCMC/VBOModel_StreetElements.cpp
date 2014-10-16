#include "VBOModel_StreetElements.h"
#include "VBORenderManager.h"


	std::vector<VBOModel> VBOModel_StreetElements::streetElementsModels;
	bool VBOModel_StreetElements::streetElements_wasInitialized=false;


	void VBOModel_StreetElements::clearVBOModel_StreetElements(){
		//destroy models
		for(int mN=0;mN<streetElementsModels.size();mN++){
			streetElementsModels[mN].clearModel();
		}
		streetElementsModels.clear();
	}//

	void VBOModel_StreetElements::initStreetElements(){
		printf("initStreetElements...\n");

		// init models
		VBOModel m;
		std::vector<QString> fileNames;
		int ind;
		
		// table chair
		ind=streetElementsModels.size();
		streetElementsModels.push_back(m);
		fileNames.clear();
		fileNames.push_back("../data/models/tablechair.obj");
		streetElementsModels[ind].initModel(fileNames);
		streetElementsModels[ind].initScale(1.0f);
		streetElementsModels[ind].loadModel();

		// bookshelf
		ind=streetElementsModels.size();
		streetElementsModels.push_back(m);
		fileNames.clear();
		fileNames.push_back("../data/models/bookshelf.obj");
		streetElementsModels[ind].initModel(fileNames);
		streetElementsModels[ind].initScale(1.0f);
		streetElementsModels[ind].loadModel();

		// sofa
		ind=streetElementsModels.size();
		streetElementsModels.push_back(m);
		fileNames.clear();
		fileNames.push_back("../data/models/sofa.obj");
		streetElementsModels[ind].initModel(fileNames);
		streetElementsModels[ind].initScale(1.0f);
		streetElementsModels[ind].loadModel();

		// small sofa
		ind=streetElementsModels.size();
		streetElementsModels.push_back(m);
		fileNames.clear();
		fileNames.push_back("../data/models/small_sofa.obj");
		streetElementsModels[ind].initModel(fileNames);
		streetElementsModels[ind].initScale(1.0f);
		streetElementsModels[ind].loadModel();

		// table
		ind=streetElementsModels.size();
		streetElementsModels.push_back(m);
		fileNames.clear();
		fileNames.push_back("../data/models/table.obj");
		streetElementsModels[ind].initModel(fileNames);
		streetElementsModels[ind].initScale(1.0f);
		streetElementsModels[ind].loadModel();

		// tree
		ind=streetElementsModels.size();
		streetElementsModels.push_back(m);
		fileNames.clear();
		fileNames.push_back("../data/models/nacho_leaves2.obj");
		fileNames.push_back("../data/models/nacho_trunk2.obj");
		streetElementsModels[ind].initModel(fileNames);
		streetElementsModels[ind].initScale(0.0056f);
		streetElementsModels[ind].loadModel();

		streetElements_wasInitialized=true;
	}


	void VBOModel_StreetElements::renderOneStreetElement(int programId,ModelSpec& treeStr){
		if(streetElements_wasInitialized==false){
			initStreetElements();
		}
		glCullFace(GL_FRONT);
		glUniform1i (glGetUniformLocation (programId, "mode"), 5|mode_Lighting);//model obj: one color

		streetElementsModels[treeStr.type].renderModel(programId, treeStr);
		
		glCullFace(GL_BACK);
		VBOUtil::check_gl_error("RenderOneStreetElement");
	}//

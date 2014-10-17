#pragma once

#include <vector>

#include "VBOModel.h"

class VBOModelManager {

public:
	VBOModelManager() : initialized(false) {}

	void clearModels();
	void initModels();

	void renderOneModel(int programId,ModelSpec& strEleStr);

	std::vector<VBOModel> models;
	bool initialized;
};
		

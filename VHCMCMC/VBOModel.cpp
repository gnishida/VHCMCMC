/************************************************************************************************
*
*		@desc Class containing the model loading and render
*		@author igarciad
*
************************************************************************************************/

#include "VBOModel.h"




	VBOModel::VBOModel(){
		modelInitialized=0;
	}//

	VBOModel::~VBOModel(){

	}//

	void VBOModel::initModel(std::vector<QString>& names){
		fileNames=names;
		modelInitialized=1;
		scale=QVector3D(1.0f,1.0f,1.0f);
		//positions.push_back(QVector3D());
	}//


	void VBOModel::initScale(float _scale){
		scale=QVector3D(_scale,_scale,_scale);
	}//

	void VBOModel::initScale(float scaleX,float scaleY,float scaleZ){
		scale=QVector3D(scaleX,scaleY,scaleZ);
	}//

	/*void VBOModel::setPositions(std::vector<QVector3D>& _positions){
		positions=_positions;
	}*/

	void VBOModel::clearModel(){

	}//

	void VBOModel::loadModel(){
		if(modelInitialized==0){
			printf("ERROR: Init model before call load Model\n");
			return;
		}
		//printf("loadModel %d\n",fileNames.size());
		vertexVBO.resize(fileNames.size());
		indexVBO.resize(fileNames.size());
		vaoVBO.resize(fileNames.size());
		stride.resize(fileNames.size());
		normalOffset.resize(fileNames.size());
		numIndexCount.resize(fileNames.size());

		glGenVertexArrays(vaoVBO.size(),&vaoVBO[0]);
		glGenBuffers(vertexVBO.size(), &vertexVBO[0]);
		glGenBuffers(indexVBO.size(), &indexVBO[0]);

		for(int fN=0;fN<fileNames.size();fN++){

			//printf("fN %d\n",fN);
			QString modelFile=fileNames[fN];
			printf("loading OBJ tree mode... %s\n",modelFile.toAscii().constData());
			nv::Model	*modelT;
			modelT = new nv::Model;
			if (!modelT->loadModelFromFile(modelFile.toAscii().constData())) {
				printf("Error loading OBJ tree model %s\n",modelFile.toAscii().constData());
				return;
			}
			//printf("2\n");

			if(scale!=QVector3D(1.0f,1.0f,1.0f)){
				modelT->scalePerNumber(scale.x(),scale.y(),scale.z());	
			}
			modelT->compileModel();
			//printf("3\n");
			int totalVertexSize = modelT->getCompiledVertexCount() * modelT->getCompiledVertexSize() * sizeof(GLfloat);
			int totalIndexSize = modelT->getCompiledIndexCount() * sizeof(GLuint);

			stride[fN] = modelT->getCompiledVertexSize() * sizeof(GLfloat);
			normalOffset[fN] = modelT->getCompiledNormalOffset() * sizeof(GLfloat);
			numIndexCount[fN]=modelT->getCompiledIndexCount();

			modelT->computeBoundingBox(minVal, maxVal);

			//printf("4 %d %d\n",modelT->getCompiledVertexCount(),modelT->getCompiledIndexCount());

			/////////////////////////////////////
			// create VAO and copy
			glBindVertexArray(vaoVBO[fN]);
			glBindBuffer(GL_ARRAY_BUFFER, vertexVBO[fN]);
			glBufferData(GL_ARRAY_BUFFER, totalVertexSize, modelT->getCompiledVertices(), GL_STATIC_DRAW);
			//glBindBuffer(GL_ARRAY_BUFFER, 0);
			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO[fN]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, totalIndexSize, modelT->getCompiledIndices(), GL_STATIC_DRAW);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			// Configure the attributes in the VAO.

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,stride[fN],0);

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,stride[fN],(void*)(normalOffset[fN]));

			// Bind back to the default state.
			glBindVertexArray(0); 
			glBindBuffer(GL_ARRAY_BUFFER,0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			

			delete modelT;
		}
		modelInitialized=2;
	}//


	void VBOModel::renderModel(int programId,ModelSpec& modelSpec){
		if(modelInitialized==0){
			printf("ERROR: Model should be initialized\n");
			return;
		}
		if(modelInitialized==1){//load in case it is neccesary
			loadModel();
		}

		int justOneColor=glGetUniformLocation (programId, "justOneColor");
		int modelTransf=glGetUniformLocation (programId, "modelTransf");

		float transfArray[16];

		for(int fN=0;fN<fileNames.size();fN++){

			glBindVertexArray(vaoVBO[fN]);

			// set color
			if(modelSpec.colors.size()>fN)
				glUniform3f(justOneColor, modelSpec.colors[fN].x(),modelSpec.colors[fN].y(),modelSpec.colors[fN].z());

			// set transfor
			for(int i=0;i<16;i++)transfArray[i]=modelSpec.transMatrix.data()[i];
			glUniformMatrix4fv(modelTransf,1,false,transfArray);//color

			//glBindBuffer(GL_ARRAY_BUFFER, vertexVBO[fN]);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO[fN]);

			glDrawElements(GL_TRIANGLES,(int) numIndexCount[fN] , GL_UNSIGNED_INT, NULL);
	
			glBindVertexArray(0);
		}
	}//

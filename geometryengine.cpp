#include<glad\glad.h>

#include "geometryengine.h"

#include<iostream>
#include<fstream>

#include <QVector2D>
#include <QVector3D>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm\glm\gtx\string_cast.hpp>

GeometryEngine::GeometryEngine() : vboIds(new GLuint[2]), vaoIds(new GLuint[2])
{    
}

GeometryEngine::~GeometryEngine()
{
    glDeleteBuffers(2, vboIds);
    delete[] vboIds;
	glDeleteBuffers(2, vaoIds);
    delete[] vaoIds;
}

void GeometryEngine::init()
{
    initializeGLFunctions();
	if (!gladLoadGL())
    {
        qDebug() << "Failed to initialize GLAD" ;
        exit (-1);
    }  
//! [0]
	glGenVertexArrays(2, vaoIds);
    // Generate 2 VBOs
    glGenBuffers(2, vboIds);

//! [0]

    // Initializes cube geometry and transfers it to VBOs
    initCubeGeometry();
}

void GeometryEngine::loadobj(std::string objfile){
	std::fstream fs;
	char line[128];
	char c;
	bool faceFirst = 1;
	int infoNum = 0;//1: .obj contains 'v', 2: .obj contatins 'v' and 'vn', 3: .obj contains 'v', 'vn' and 'vt'
	std::vector<glm::vec3> vertex;
	std::vector<glm::vec2> textcor;
	std::vector<glm::vec3> normal;
	std::vector<unsigned int> vertexInd, textcorInd, normalInd;
	std::string type;
	fs.open(objfile, std::fstream::in);
	if(fs.is_open()){
		while(fs>>type){
			//std::cout<<type<<std::endl;
			if(type=="#"){
				fs.getline(line, 128);
			}
			if(type=="v"){
				glm::vec3 temp;
				for(int i = 0; i<3; i++){
					fs>>temp[i];
				}
				//std::cout<<glm::to_string(temp)<<std::endl;
				vertex.push_back(temp);
			}
			else if(type=="vt"){
				glm::vec2 temp;
				for(int i = 0; i<2; i++){
					fs>>temp[i];
				}
				//std::cout<<glm::to_string(temp)<<std::endl;
				textcor.push_back(temp);
			}
			else if(type=="vn"){
				glm::vec3 temp;
				for(int i = 0; i<3; i++){
					fs>>temp[i];
				}
				//std::cout<<glm::to_string(temp)<<std::endl;
				normal.push_back(temp);
			}
			else if(type=="f"){
				if(faceFirst){
					faceFirst = 0;
					if(vertex.size()>0) infoNum = 1;
					if(normal.size()>0) infoNum ++;
					if(textcor.size()>0) infoNum ++;
				}
				unsigned int vertexTmp[3], textcorTmp[3], normalTmp[3];
				if(infoNum == 1){
					if (fs>>vertexTmp[0] && fs>>vertexTmp[1] && fs>>vertexTmp[2] ){
						for(int i = 0; i < 3; i++){
							vertexInd.push_back(vertexTmp[i]);
						}
					}
					else{
						std::cout<<"'f' read error: infoNum = 1."<<std::endl;
					}
				}
				else if(infoNum == 2){
					if (fs>>vertexTmp[0] && fs>>c && c == '/' && fs>>c && c == '/' && fs>>normalTmp[0] &&
						fs>>vertexTmp[1] && fs>>c && c == '/' && fs>>c && c == '/' && fs>>normalTmp[1] &&
						fs>>vertexTmp[2] && fs>>c && c == '/' && fs>>c && c == '/' && fs>>normalTmp[2]){
						for(int i = 0; i < 3; i++){
							vertexInd.push_back(vertexTmp[i]);
							normalInd.push_back(normalTmp[i]);
						}
					}
					else{
						std::cout<<"'f' read error: infoNum = 2."<<std::endl;
					}
				}
				else{
					if (fs>>vertexTmp[0] && fs>>c && c == '/' && fs>>textcorTmp[0] && fs>>c && c == '/' && fs>>normalTmp[0] &&
						fs>>vertexTmp[1] && fs>>c && c == '/' && fs>>textcorTmp[1] && fs>>c && c == '/' && fs>>normalTmp[1] &&
						fs>>vertexTmp[2] && fs>>c && c == '/' && fs>>textcorTmp[2] && fs>>c && c == '/' && fs>>normalTmp[2]){
							for(int i = 0; i < 3; i++){
								vertexInd.push_back(vertexTmp[i]);
								textcorInd.push_back(textcorTmp[i]);
								normalInd.push_back(normalTmp[i]);
							}
					}
					else{
						std::cout<<"'f' read error: infoNum = 2."<<std::endl;
					}
				}
			}
		}
		fs.close();
		for(int i = 0; i < vertexInd.size(); i++){
			Vertex temp;
			temp.Position = vertex[vertexInd[i]-1];
			if(infoNum > 1){
				temp.Normal = normal[normalInd[i]-1];
				if(infoNum > 2) temp.TexCoords = textcor[textcorInd[i]-1];
			}
			vertices.push_back(temp);
		}
	}
	else{
		std::cout<<"can not open file properly"<<std::endl;
	}
}

void GeometryEngine::initCubeGeometry()
{
	//vertices with texcorr for a cube
	float verticesCube[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
	//vertices for a cube map
	float verticesSkybox[] = {
		-10.0f,  10.0f, -10.0f,
		-10.0f, -10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,
		10.0f,  10.0f, -10.0f,
		-10.0f,  10.0f, -10.0f,
  
		-10.0f, -10.0f,  10.0f,
		-10.0f, -10.0f, -10.0f,
		-10.0f,  10.0f, -10.0f,
		-10.0f,  10.0f, -10.0f,
		-10.0f,  10.0f,  10.0f,
		-10.0f, -10.0f,  10.0f,
  
		10.0f, -10.0f, -10.0f,
		10.0f, -10.0f,  10.0f,
		10.0f,  10.0f,  10.0f,
		10.0f,  10.0f,  10.0f,
		10.0f,  10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,
   
		-10.0f, -10.0f,  10.0f,
		-10.0f,  10.0f,  10.0f,
		10.0f,  10.0f,  10.0f,
		10.0f,  10.0f,  10.0f,
		10.0f, -10.0f,  10.0f,
		-10.0f, -10.0f,  10.0f,
  
		-10.0f,  10.0f, -10.0f,
		10.0f,  10.0f, -10.0f,
		10.0f,  10.0f,  10.0f,
		10.0f,  10.0f,  10.0f,
		-10.0f,  10.0f,  10.0f,
		-10.0f,  10.0f, -10.0f,
  
		-10.0f, -10.0f, -10.0f,
		-10.0f, -10.0f,  10.0f,
		10.0f, -10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,
		-10.0f, -10.0f,  10.0f,
		10.0f, -10.0f,  10.0f
	};

//! [1]
	/*
    // Transfer vertex data for cube to VBO 0
	glBindVertexArray(vaoIds[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCube), verticesCube, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	*/
	//use load obj
	loadobj("bunny.obj");
	glBindVertexArray(vaoIds[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	//
	glBindVertexArray(vaoIds[1]);
    // Transfer vertex data for skybox to VBO 1
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSkybox), verticesSkybox, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[1]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindVertexArray(0);
//! [1]
}

//! [2]
void GeometryEngine::drawCubeGeometry(QGLShaderProgram *programObj, QGLShaderProgram *programLt, GLuint texture, GLuint textureSkybox)
{
	
	if (!programObj->bind())
	{
		qDebug()<<"fail to use Objshader";
        exit(-1);
	}
	//glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(vaoIds[0]);
	// Draw geometry using indices from VBO 1
	// cube
	// glBindTexture(GL_TEXTURE_CUBE_MAP, textureSkybox);   
	// glDrawArrays(GL_TRIANGLES, 0, 36);
	// obj
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	

	glDepthFunc(GL_LEQUAL);
	if (!programLt->bind())
	{
		qDebug()<<"fail to use ltshader";
        exit(-1); 
	}
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP,textureSkybox);
	glBindVertexArray(vaoIds[1]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthFunc(GL_LESS);
	
	
}


//! [2]

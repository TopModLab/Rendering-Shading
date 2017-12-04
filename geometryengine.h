#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QtOpenGL/QGLFunctions>
#include <QtOpenGL/QGLShaderProgram>
#include <vector>
#include <glm/glm/glm.hpp>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class GeometryEngine : protected QGLFunctions
{
public:
    GeometryEngine();
    virtual ~GeometryEngine();

	std::vector<Vertex> vertices;

    void init();
	void loadobj(std::string filename);
    void drawCubeGeometry(QGLShaderProgram *programObj, QGLShaderProgram *programLt, GLuint texture, GLuint textureSkybox);
	
private:
    void initCubeGeometry();

    GLuint *vboIds, *vaoIds;

};

#endif // GEOMETRYENGINE_H
